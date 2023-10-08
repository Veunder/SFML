#include <SFML/Graphics.hpp>
#include <iostream>


int main() {
    sf::Texture atlas;
    if (!atlas.loadFromFile(R"(C:\Users\misha\CLionProjects\SFML\no_background.png)")) {
        std::cout << "Не удалось открыть файл!\n";
        exit(0);
    }

    auto window = sf::RenderWindow{{600u, 600u}, "CMake SFML Project"};
    window.setFramerateLimit(60);

    sf::Sprite dino;
    dino.setTexture(atlas);
    dino.setTextureRect(sf::IntRect(850, 4, 40, 43));

    sf::Sprite ground1;
    ground1.setTexture(atlas);
    ground1.setTextureRect(sf::IntRect(1, 53, 1200, 15));
    ground1.setPosition(0, 400);

    sf::Sprite ground2;
    ground2.setTexture(atlas);
    ground2.setTextureRect(sf::IntRect(1, 53, 1200, 15));
    ground2.setPosition(ground1.getGlobalBounds().width, 400);

    float ground_speed = -5;

    float player_gravity = 0;

    dino.setPosition(10, ground1.getGlobalBounds().top - 37);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space){
                    player_gravity = -15;
                }
            }
        }

        ground1.move(ground_speed, 0);
        ground2.move(ground_speed, 0);
        if (ground1.getPosition().x + ground1.getGlobalBounds().width < 0) {
            ground1.setPosition(ground2.getPosition().x + ground2.getGlobalBounds().width, ground1.getPosition().y);
        }
        if (ground2.getPosition().x + ground2.getGlobalBounds().width < 0) {
            ground2.setPosition(ground1.getPosition().x + ground1.getGlobalBounds().width, ground1.getPosition().y);
        }

        window.clear(sf::Color::White);

        player_gravity++;
        dino.move(0, player_gravity);
        if (dino.getGlobalBounds().top > ground1.getGlobalBounds().top - 37){
            dino.setPosition(10, ground1.getGlobalBounds().top - 37);
        }

        window.draw(ground1);
        window.draw(ground2);
        window.draw(dino);

        window.display();
    }
}