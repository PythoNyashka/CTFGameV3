#include <vector>
#include <fstream>
#include <thread>
#include <iostream>

#include "point.cpp"
#include "config.cpp"
#include "requester.cpp"

#include <SFML/Graphics.hpp>
#include <curl/curl.h>

using namespace sf;
class Level
{
private:
    point start_pose;
	point flag_pose;

    std::vector<point> plates;
    Sprite sBackground, sPlat, sPers, sFlag;
    Texture back_ground, plate, player, flag_img;

	std::string level_file;

	std::string readBuffer;
	bool Is_working;

	static bool cmp(point a, point b)
	{
		return a.x < b.x;
	}

	void generate_plates_position(std::string lev)
	{
		plates = std::vector<point>();

		std::ifstream fin;
        fin.open(lev);

        int x = 0, y = 50;

        std::string str;
        for (; getline(fin, str);)
        {
            for (auto col : str)
            {
                if (col == '-')
                {
                    point pf;
                    pf.x = x;
                    pf.y = y;

                    plates.push_back(pf);
                }
                x += plat_width;
            }
            y += plat_height;
            x = 0;
        }
		fin.close();

		std::sort(plates.begin(), plates.end(), cmp);
	}

    void generate_level(std::string lev)
    {
        generate_plates_position(lev);

		start_pose.x = plates[0].x + 25;
		start_pose.y = plates[0].y - 25;

		flag_pose.x = plates[plates.size() - 1].x + 25 - flag_width / 2;
		flag_pose.y = plates[plates.size() - 1].y - 25 - flag_height / 2;
    }

public:

	void reset()
	{
		request(readBuffer);
		std::cout << readBuffer << "\n";
		Is_working = false;
	}

    Level(std::string lev, RenderWindow& app)
    {
        app.setFramerateLimit(60);

        back_ground.loadFromFile(sprites_img_json["level_background_img"]);
        plate.loadFromFile(sprites_img_json["platform_img"]);
        player.loadFromFile(sprites_img_json["player_img"]);
        flag_img.loadFromFile(sprites_img_json["flag_img"]);

        sBackground = Sprite(back_ground);
        sPlat = Sprite(plate);
        sPers = Sprite(player);
        sFlag = Sprite(flag_img);

		level_file = lev;
        generate_level(level_file);

		sFlag.setPosition(flag_pose.x, flag_pose.y);
    }

    void start(RenderWindow& app)
    {
        float x = start_pose.x, y = start_pose.y;
        float dx = 0, dy = 0;
        float delta_r = 0, delta_l = 0;

        bool was_pressed = true;
        bool is_forw_pressed = false;
        bool is_back_pressed = false;

		reset();

        while (app.isOpen())
        {
            //colse condition
            Event e;
            while (app.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    app.close();
            }

			if (!Is_working
			/*&& level_file != levels_map_json["1"]
			&& level_file != levels_map_json["2"]*/)
			{
				Is_working = true;
				std::thread([=]()
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(3000));
					reset();
				}).detach();
			}

			if (readBuffer == "bring")
			{
				generate_plates_position(level_file + "1");
			}

            //go to start position
            if (y > max_y || x > max_x || x < 0)
            {
                x = start_pose.x;
                y = start_pose.y;
                delta_l = delta_r = 1;
            }

			if (x + radiouse > flag_pose.x && x + radiouse < flag_pose.x + flag_width &&
			y + radiouse  > flag_pose.y && y + radiouse  < flag_pose.y + flag_height)
			{
				break;
			}

            //right mooving
            if (Keyboard::isKeyPressed(Keyboard::Right))
                x += delta_r;
            else //breaking
            {
                if (delta_r > 1)
                {
                    delta_r -= a;
                    x += delta_r;
                }
                else if (delta_r < 1)
                    delta_r = 1;
            }

            //left mooving
            if (Keyboard::isKeyPressed(Keyboard::Left))
                x -= delta_l;
            else //breaking
            {
                if (delta_l > 1)
                {
                    delta_l -= a;
                    x -= delta_l;
                }
                else if (delta_l < 1)
                    delta_l = 1;
            }

            was_pressed = Keyboard::isKeyPressed(Keyboard::Up);

            dy += gravity_coefficient;
            y += dy;

            for (int i = 0; i < plates.size(); i++)
            {
                if ((x + radiouse + 2 >= plates[i].x) && (x + radiouse - 2 <= plates[i].x + 80)
                    && (y + 2 * radiouse > plates[i].y) && (y + 2 * radiouse <= plates[i].y + 25)
                    && (dy > 0))
                {
                    y = plates[i].y - 2 * radiouse + 4;

                    if (Keyboard::isKeyPressed(Keyboard::Right))
                    {
                        delta_r += a;
                        x += delta_r;
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Left))
                    {
                        delta_l += a;
                        x -= delta_l;
                    }

                    if (was_pressed)
                    {
                        dy = -jump_coefficient;
                        was_pressed = false;
                    }
                    else
                        dy = -gravity_coefficient;
                }
            }

            sPers.setPosition(x, y);

            app.draw(sBackground);
			app.draw(sFlag);
            app.draw(sPers);
            for (int i = 0; i < plates.size(); i++)
            {
                sPlat.setPosition(plates[i].x, plates[i].y);
                app.draw(sPlat);
            }

            app.display();
        }
    }
};
