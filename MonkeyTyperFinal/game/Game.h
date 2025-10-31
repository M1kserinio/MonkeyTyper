//
// Created by Mikołaj on 18.05.2024.
//

#pragma once


#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>
#include "Screen.h"
#include "Word.h"
#include "Difficulty.h"
#include "Button.h"
#include "App.h"




struct Game : public Screen{

private:
    std::vector<Word> words;
    std::vector<Button> buttons;
    sf::Font font;
    bool gameOver;
    Difficulty::MODE difficulty;
    float wordSpeed;
    sf::Time wordCreationTime;

    std::vector<std::string> dictionary;
    sf::Clock wordCreationClock;
    sf::Time nextWordCreateTime;
    Word input;
    int wordsSiez;
    int wordCount;
    Word wordCountInfo;
    sf::RectangleShape separatorRect;
    sf::RectangleShape separatorUIScore;
    sf::RectangleShape separatorUIInput;
    sf::Texture backgroundT;
    sf::Sprite backgroundS;

   /* sf::Text wpiszNick;
    sf::Text nickT;
    std::string nickInput;
    bool enterNick;*/ // zostawie to zakomentowane bo probowalem leaderboarda lecz mnie pokonal...





    auto rand(int from, int to) -> int;
    auto randWordY() -> int;
    auto resetWordTimer() -> void;
    auto removeWord(const std::string& text) -> bool;
    auto loadDictionary() -> void;
    auto randWord() -> std::string;


public:
    auto draw(sf::RenderWindow& window) -> void override;
    auto onEvent(sf::Event& event) -> void override;
    auto update() -> void override;

    Game(sf::Font& font, Difficulty::MODE difficulty);
    auto separator(sf::RenderWindow &window) -> void;
    auto setFont(const sf::Font& font) -> void override;
    auto save() -> void;
    static auto load(sf::Font& font) -> std::unique_ptr<Game>;
    auto textObjColor(sf::Color color) -> void override;
    auto setWordTextSize(int size) -> void;
    auto savePlayer() -> void;
    auto menuButtonClicked() -> bool;
    auto modeButtonClicked() -> bool;
    auto exitButtonClicked() -> bool;

};



