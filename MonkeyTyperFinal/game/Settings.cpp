
// Created by Mikołaj on 24.05.2024.
//

#include "Settings.h"

Settings::Settings(sf::Font &font) : font(font) {
    std::string backButton = "Back";

    std::string Arial = "Arial";
    std::string Mantey = "Wide";
    std::string Thin = "Thin";
    std::string white = "White"; // roznica 100
    std::string black = "Black";
    std::string purple = "Purple";

    buttons.emplace_back(600,500, backButton,font, sf::Color::Red,270,70);

    buttons.emplace_back(60,100,Arial,font,sf::Color::Cyan,200,70);
    buttons.emplace_back(280,100, Mantey, font, sf::Color::Cyan,200,70);
    buttons.emplace_back(500,100,Thin,font,sf::Color::Cyan,200,70);


    buttons.emplace_back(60,270,white,font,sf::Color::Cyan,200,70);
    buttons.emplace_back(280,270,black,font,sf::Color::Cyan,200,70);
    buttons.emplace_back(500,270,purple,font,sf::Color::Cyan,200,70);



}
void Settings::draw(sf::RenderWindow &window)  {


    for(auto& button : buttons){
        button.draw(window);
    }
    sf::Text fontsHeader("Fonts",font,50);
    fontsHeader.setPosition(330,30);
    window.draw(fontsHeader);

    sf::Text colorHeader("Font Color", font, 50);
    colorHeader.setPosition(270,200);
    window.draw(colorHeader);

    sf::Text esc("ESC - back to menu",font,30);
    esc.setPosition(40,400);
    window.draw(esc);

    sf::Text enter("ENTER - enter words",font,30);
    enter.setPosition(400,400);
    window.draw(enter);

    sf::Text sizes("LSHIFT + num9/num0 - smaller/bigger words (ingame)",font,30);
    sizes.setPosition(40,450);
    window.draw(sizes);

    sf::Text backspace("BACKSPACE - remove letter",font,30);
    backspace.setPosition(40,500);
    window.draw(backspace);

    sf::Text fullWorderase("LSHIFT + BACKSPACE - full word remove",font,30);
    fullWorderase.setPosition(40,350);
    window.draw(fullWorderase);


}
auto Settings::onEvent(sf::Event &event) -> void{
    for(auto& button : buttons) {
        button.oneEvent(event);

    }

}
auto Settings::update() -> void {


}

auto Settings::setFont(const sf::Font &font) -> void {
    this->font = font;
    for(auto& button : buttons){
        button.setFont(font);
    }
}
auto Settings::whiteFont() -> bool {
    return buttons[4].getPressed();
}
auto Settings::blackFont() -> bool {
    return buttons[5].getPressed();
}
auto Settings::purpleFont() -> bool {

    return buttons[6].getPressed();
}

auto Settings::textObjColor(sf::Color color) -> void {
    for(auto& button : buttons){
        button.textObjColor(color);
    }

}

auto Settings::backClicked() -> bool {
    return buttons[0].getPressed();
}

auto Settings::firstFont() -> bool {
    return buttons[1].getPressed();
}
auto Settings::secondFont() -> bool {
    return buttons[2].getPressed();
}
auto Settings::thirdFont() -> bool {
    return buttons[3].getPressed();
}



