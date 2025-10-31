//
// Created by Mikołaj on 15.05.2024.
//

#include "Button.h"
#include <iostream>

auto Button::draw(sf::RenderWindow &window) -> void {
    window.draw(rectangle);
    window.draw(textObj);
}

Button::Button(float x, float y, std::string &text, sf::Font &font, sf::Color color, float width, float height)
 : x(x), y(y), width(width),height(height),text(text),font(font),isPressed(false),
  rectangle(sf::RectangleShape(sf::Vector2f(width,height))){
    rectangle.setPosition(x, y);
    rectangle.setFillColor(color);

    textObj.setFillColor(sf::Color::Black);
    textObj.setCharacterSize(40);
    textObj.setPosition(x + 30, y + 10); //60 , 10
    textObj.setString(text);
    textObj.setFont(font);
}

auto Button::oneEvent(sf::Event& event)  -> void {
    if(event.type == sf::Event::MouseButtonReleased) {
        if(event.mouseButton.x >= x && event.mouseButton.x <= x + width &&
        event.mouseButton.y >= y && event.mouseButton.y <= y + height) {
            isPressed = true;
        }
    }
}

auto Button::getPressed() -> bool {
    bool copy = isPressed;
    isPressed = false;
    return copy;
}
auto Button::setFont(const sf::Font &font) -> void {
    this->font = font;
    textObj.setFont(font);
}
auto Button::textObjColor(sf::Color color) -> void {
    textObj.setFillColor(color);

}



