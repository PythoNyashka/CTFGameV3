#include <string>
#include <curl/curl.h>
#undef min
#undef max

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

static void Bring_request(std::string &readBuffer)
{
	CURL *curl;
	static CURLcode res;

	readBuffer = "";

	curl = curl_easy_init();
	if (curl) 
	{
		
		
		curl_easy_setopt(curl, CURLOPT_URL, "http://task5.wbcdev.ru/api.bring?platform_id=0&need_bring=0");

		curl_easy_setopt(curl, CURLOPT_CAINFO, NULL);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
}

static void Flag_request(std::string &readBuffer)
{
	static CURL *curl;
	static CURLcode res;

	readBuffer = "";

	curl = curl_easy_init();
	if (curl) 
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://task5.wbcdev.ru/api.getflag?hash=0");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
}