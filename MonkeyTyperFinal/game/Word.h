//
// Created by Mikołaj on 16.05.2024.
//

#pragma once

#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Difficulty.h"

struct Word {
private:
    float x;
    float y;
    sf::Text textObj;
    std::string text;
    float speed;
    sf::Font* font;
    int roundCount;
    int textSize;
    sf::Color actualColor;

public:

    auto draw(sf::RenderWindow &window) -> void;
    auto onEvent(sf::Event& event) -> void;
    auto update(float s) -> void;
    Word(float x, float y, const std::string &text, sf::Font *font,float speed);
    Word(float x, float y, const std::string &text, int roundCount, sf::Font *font,float speed);
    Word(float x, float y, sf::Font *font,float speed);
    const std::string& get() const;
    auto set(const std::string & text) -> void;
    auto append(char chr) -> void;
    auto getRoundCount() const -> int;
    auto popCharacter()  -> void; //
    auto xColor() -> void;
    auto getPosition() const -> sf::Vector2f;
    auto position(float x, float y) -> void;
    auto serialize(std::ofstream& out) -> void;
    static auto deserialize(std::ifstream& in, sf::Font& font) -> Word;
    auto setTextSize(int size) -> void;

    auto setColor(const sf::Color &color) -> void;
    auto resetColor() -> void;

};
