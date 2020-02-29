#include "json.hpp"

using json = nlohmann::json;

// static std::string root_folder = "../static/sprites/";

static json sprites_img_json = json
(
	R"(
		{
			"level_background_img": "static/back.png",
			"flag_img": "static/flag.png",
			"platform_img": "static/platform.png",
			"player_img": "static/player.png",
			"start_button_img": "static/press_f.png"
		}
	)"_json
);

static json levels_map_json = json
(
	R"(
		{
			"1": "levels/level1.txt",
			"2": "levels/level2.txt",
			"3": "levels/level3.txt",
			"4": "levels/level4.txt",
			"5": "levels/level5.txt"
		}
	)"_json
);

static json months_json = json(
	R"(
		{
			"Jan": "01",
			"Feb": "02",
			"Mar": "03",
			"Apr": "04",
			"May": "05",
			"Jun": "06",
			"Jul": "07",
			"Aug": "08",
			"Sep": "09",
			"Oct": "10",
			"Now": "11",
			"Dec": "12"
		}
	)"_json
);


const int plat_width = 18, plat_height = 25;
const int max_x = 800, max_y = 500;
const int plates_count = 10;
const int max_height = 200;
const float gravity_coefficient = 0.27;
const int jump_coefficient = 8;
const int radiouse = 16;
const float a = 0.08;
const int flag_width = 40, flag_height = 80;

static const char* server_url = "https://ef04c31d.ngrok.io/";