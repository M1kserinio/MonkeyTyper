//
// Created by Mikołaj on 25/05/2024.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Screen.h"

struct Difficulty : public Screen {
    std::vector<Button> buttons;
    sf::Font& font;

    sf::Texture backgroundT;
    sf::Sprite backgroundS;


public:
    enum MODE{
        EASY,MEDIUM,HARD
    };

    Difficulty(sf::Font& font);
    auto draw(sf::RenderWindow& window) -> void override;
    auto onEvent(sf::Event& event) -> void override;
    auto update() -> void override;
    auto setFont(const sf::Font& font) -> void override;
    static auto rand(int from, int to) -> int;
    static auto dictionares(MODE mode) -> std::string;
    auto textObjColor(sf::Color color) -> void override;
    static auto getWordSpeed(MODE mode) -> float;
    static auto getWordCreationTime(MODE mode) -> sf::Time;

    auto easyClicked() -> bool;
    auto mediumClicked() -> bool;
    auto hardClicked() -> bool;
    auto backClicked() -> bool;
};


