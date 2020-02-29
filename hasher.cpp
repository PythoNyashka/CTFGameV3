#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/channels.h>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "cryptopp/md5.h"

#include <string>

using namespace CryptoPP;


static std::string Get_hash(std::string month)
{
	std::string message = month + "CTFGame();";

	std::string hashed_messange;
	Weak::MD5 md5;

	HashFilter filter(md5, new HexEncoder(new StringSink(hashed_messange)));

	ChannelSwitch encryptor;
	encryptor.AddDefaultRoute(filter);

	StringSource ss(message, true, new Redirector(encryptor));

	return hashed_messange;
}