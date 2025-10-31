//
// Created by Mikołaj on 16.05.2024.
//

#include <iostream>
#include "Word.h"

Word::Word(float x, float y, const std::string &text, sf::Font *font,float speed) : x(x), y(y), text(text), font(font),
roundCount(2),speed(speed){ //roundCount odpowiada u mnie za mechanike konca gry gdy slowo dwa razy przez ekran to przehrana
    textObj.setFont(*font);
    textObj.setCharacterSize(18); // 10 12
    textObj.setPosition(x, y);
    textObj.setString(text);
}

Word::Word(float x, float y, sf::Font *font,float speed) : Word(x, y, "", font,speed) {

}

    Word::Word(float x, float y, const std::string &text, int roundCount, sf::Font *font,float speed)
    : Word(x, y, text, font,speed) {
    this->roundCount = roundCount;
}


auto Word::draw(sf::RenderWindow &window) -> void {
    window.draw(textObj);
}

auto Word::onEvent(sf::Event& event) -> void  {

}
auto Word::xColor() -> void {
    if (x < 200) {
        actualColor = sf::Color::Green;
    } else if (x < 500) { //450
        actualColor = sf::Color::Yellow;
    } else {
        actualColor = sf::Color::Red;
    }
    textObj.setFillColor(actualColor);
}


auto Word::update(float s) -> void  {
    x += s;
   /* fmt::println("Word speed: {}", d);*/
    textObj.setPosition(x, y);
    if(x > 800 && roundCount > 0) {
        roundCount--;
        x = 10;
    }

    xColor();
}

auto Word::set(const std::string &text) -> void  {
    this->text = text;
    textObj.setString(this->text);
}

auto Word::append(char chr) -> void  {
    text += chr;
    textObj.setString(text);
}

const std::string &Word::get() const {
    return text;
}

auto Word::getRoundCount() const -> int {
    return roundCount;
}

auto Word::popCharacter() -> void  {
    if(text.size() > 0) {
        text = text.substr(0, text.size() - 1);
        textObj.setString(text);
    }
}
auto Word::getPosition() const -> sf::Vector2f {
    return sf::Vector2f(x,y);
}

auto Word::position(float x, float y) -> void {
    this->x = x;
    this->y = y;
}

auto Word::serialize(std::ofstream &out) -> void {
   out << text << " " << x << " " << y << " " << roundCount;
}

auto Word::deserialize(std::ifstream& in, sf::Font& font) -> Word {
    std::string text;
    float x, y;
    int roundCount,speed;
    in >> text >> x >> y >> roundCount;
    return Word(x, y, text, roundCount,  &font,speed);
}

auto Word::setTextSize(int size) -> void  {
    textSize = size;
    textObj.setCharacterSize(textSize); // jkaby sie Pan zastanawial jezeli to wogole czyta to potrzebne do zmiany
}                                          //size podczas gry za pomoca skrotow klawiszowych

auto Word::setColor(const sf::Color &color) -> void {
    textObj.setFillColor(color);
}

auto Word::resetColor() -> void {
    textObj.setFillColor(actualColor);
}

