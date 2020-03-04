#include "json.hpp"

using json = nlohmann::json;

static json sprites_img_json = json
(
	R"(
		{
			"level_background_img": "static/back.png",
			"flag_img": "static/flag.png",
			"platform_img": "static/platform.png",
			"player_img": "static/player.png",
			"start_button_img": "static/press_f.png",
			"flag": "static/end_back.png"
		}
	)"_json
);

static json levels_map_json = json
(
	R"(
		{
			"1": "levels/level1.level",
			"2": "levels/level2.level",
			"3": "levels/level3.level",
			"4": "levels/level4.level",
			"5": "levels/level5.level"
		}
	)"_json
);

static json months_json = json(
	R"(
		{
			"Jan": "1",
			"Feb": "2",
			"Mar": "3",
			"Apr": "4",
			"May": "5",
			"Jun": "6",
			"Jul": "7",
			"Aug": "8",
			"Sep": "9",
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