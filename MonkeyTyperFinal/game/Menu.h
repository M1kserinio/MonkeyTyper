//
// Created by Mikołaj Stępowski on 15/05/2024.
//

#pragma once

#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Screen.h"
#include <vector>

struct Menu : public Screen{
    std::vector<Button> buttons;
    sf::Font& font;

    sf::Texture backgroundT;
    sf::Sprite backgroundS;





public:
    Menu(sf::Font& font);
    auto draw(sf::RenderWindow& window) -> void override;
    auto onEvent(sf::Event& event) -> void override;
    auto update() -> void override;
    auto startGameClicked() -> bool;
    auto loadGameClicked() -> bool;
    auto optionsGameClicked() -> bool;
    auto exitGameClicked() -> bool;

    auto setFont(const sf::Font& font) -> void override;
    auto textObjColor(sf::Color color) -> void override;



};



