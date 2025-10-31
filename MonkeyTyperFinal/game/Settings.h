
//
// Created by Mikołaj on 24.05.2024.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Button.h"
#include <vector>

struct Settings : public Screen{
private:
    sf::Font& font;
    std::vector<Button> buttons;



public:
    Settings(sf::Font& font);
    auto draw(sf::RenderWindow& window) -> void override;
    auto onEvent(sf::Event& event) -> void override;
    auto update() -> void override;
    auto backClicked() -> bool;
    auto firstFont() -> bool;
    auto secondFont() -> bool;
    auto thirdFont() -> bool;

    auto setFont(const sf::Font& font) -> void override;
    auto whiteFont()-> bool ;
    auto blackFont()-> bool;
    auto purpleFont() -> bool;
    auto textObjColor(sf::Color color) -> void override;


};



