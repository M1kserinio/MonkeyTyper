//
// Created by Mikołaj on 15.05.2024.
//

#pragma once
#include "fmt/core.h"
#include "SFML/Graphics.hpp"
#include "Screen.h"
#include <memory>
#include "Menu.h"
#include "Settings.h"
#include "Game.h"
#include "Difficulty.h"
#include "Button.h"

enum class Windows {
    MENU, GAME, SETTINGS, DIFFICULTY, LOAD_GAME
};


struct App {

private:
    sf::RenderWindow window;
    sf::Font currentFont;
    sf::Color currentTextObj;

    sf::Texture backgroundT;
    sf::Sprite backgroundS;

    std::unique_ptr<Screen> currentS;
    Windows currentWindow;

    auto changeWindows(Windows newWind, Difficulty::MODE = Difficulty::EASY) -> void;
    auto onEvent(sf::Event& event) -> void;



public:
    App();
    auto mainLoop() -> void;
    auto exitGame() -> void;


};



