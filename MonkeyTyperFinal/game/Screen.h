//
// Created by Mikołaj on 15.05.2024.
//

#pragma once

#include "fmt/core.h"
#include "SFML/Graphics.hpp"

struct Screen {
public:
    virtual auto draw(sf::RenderWindow & window) -> void = 0;
    virtual auto onEvent(sf::Event& event) -> void = 0;
    virtual auto update() -> void = 0;
    virtual ~Screen() = default;
    virtual auto setFont(const sf::Font& font) -> void = 0;
    virtual auto textObjColor(sf::Color color) -> void = 0;


};



