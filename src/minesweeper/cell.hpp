#pragma once
#include <SFML/Graphics.hpp>

class Cell
{
    private:
        sf::Sprite sprite;
        sf::Texture texture;

    public:
        Cell();

        void change(int8_t index);
        void draw(sf::RenderWindow &window, sf::Vector2i position, sf::Vector2i offset);
};

