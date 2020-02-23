#include "level.cpp"
#include <iostream>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow app(sf::VideoMode(max_x, max_y), "CTFGame();");
    app.setFramerateLimit(60);

    sf::Music music;
    if (!music.openFromFile("static/all_lvls.ogg"))
        return 1;

    music.setVolume(50.f);
    music.setLoop(true);

    music.play();

    sf::Texture start_button_texture, back_ground;
    back_ground.loadFromFile(sprites_img_json["level_background_img"]);
    start_button_texture.loadFromFile(sprites_img_json["start_button_img"]);

    sf::Sprite start_buton(start_button_texture), background(back_ground);

    while (app.isOpen())
    {
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

    Level level1("levels/level1.txt", app);
    level1.start(app);

    return 0;
}