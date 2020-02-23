#include "json.hpp"

using json = nlohmann::json;

// static std::string root_folder = "../static/sprites/";

static json sprites_img_json = json(R"(
  {
    "level_background_img": "static/back.png",
    "flag_img": "static/flag.png",
    "platform_img": "static/platform.png",
    "player_img": "static/player.png",
    "start_button_img": "static/press_f.png"
  }
)"_json);


const int plat_width = 18, plat_height = 25;
const int max_x = 800, max_y = 500;
const int plates_count = 10;
const int max_height = 200;
const float gravity_coefficient = 0.27;
const int jump_coefficient = 8;
const int radiouse = 16;
const float a = 0.08;