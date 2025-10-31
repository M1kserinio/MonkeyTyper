//
// Created by Mikołaj on 15.05.2024.
//

#pragma once

#include <fmt/core.h>
#include <SFML/Graphics.hpp>

struct Button {
private:
    float x;
    float y;
    float width;
    float height;
    bool isPressed;
    sf::RectangleShape rectangle;
    sf::Text textObj;
    std::string text;
    sf::Font& font;


public:
    auto draw(sf::RenderWindow &window) -> void;
    auto oneEvent(sf::Event& event) -> void;
    auto getPressed() -> bool;
    Button(float x, float y, std::string &text, sf::Font &font,sf::Color color,float width,float height);
    auto setFont(const sf::Font& font)-> void;
    auto textObjColor(sf::Color color) -> void;


};


