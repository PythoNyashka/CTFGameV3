#include "level.cpp"
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow app(sf::VideoMode(max_x, max_y), "CTFGame");
    app.setFramerateLimit(60);

    sf::Texture start_button_texture, back_ground, flag_back_ground;
    back_ground.loadFromFile(sprites_img_json["level_background_img"]);
    start_button_texture.loadFromFile(sprites_img_json["start_button_img"]);
	flag_back_ground.loadFromFile(sprites_img_json["flag"]);

    sf::Sprite start_buton(start_button_texture), background(back_ground), Flag_back(flag_back_ground);

    while (app.isOpen())
    {
		app.clear();
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::F)) {
            break;
        }

        app.draw(background);
        app.draw(start_buton);

        app.display();
    }

	std::vector<Level> levels;

	for (int i = 1; i <= 5; i++)
	{
		std::string s = std::to_string(i);
		levels.push_back(Level(levels_map_json[s], app));
	}

    for (auto level : levels)
		level.start(app);

	while (app.isOpen())
	{
		Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
            break;
        }

		app.draw(Flag_back);
		app.display();
	}

    return 0;
}