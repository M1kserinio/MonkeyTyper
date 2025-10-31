//
// Created by Mikołaj on 15/05/2024.
//

#include "Menu.h"

Menu::Menu(sf::Font &font) : font(font) {



    if (!backgroundT.loadFromFile("../dodatk/MenuBoss.jpeg")){
        fmt::println("image error");
        exit(3);
    }
    backgroundS.setPosition(300,120);
    backgroundS.setTexture(backgroundT);


    std::string startText = "Start";
    std::string loadGameText = "Load Game";
    std::string settingsText = "Settings";
    std::string exitText = "Exit";



    buttons.emplace_back(300,150,startText,font, sf::Color::Blue,200,70);
    buttons.emplace_back(500,500,loadGameText,font,sf::Color::Red,260,80); // uzywam emplace_back bo bezposrednio konstruuje element
    buttons.emplace_back(300,250,settingsText,font,sf::Color::Blue,200,70);  // kiedys sie tak nauczylem i przy tym zostalem zamiast pushbackowac
    buttons.emplace_back(300,350,exitText,font,sf::Color::Blue,200,70);



}

auto Menu::draw(sf::RenderWindow &window) -> void {
    window.draw(backgroundS);


    for (auto& button : buttons) {
        button.draw(window);
    }

    sf::Text header("Monkey Typer",font,50);
    header.setPosition(240.0f,50.f);

    window.draw(header);




}
auto Menu::onEvent(sf::Event &event) -> void {
    for( auto& button : buttons){
        button.oneEvent(event);
    }

}


auto Menu::update() -> void {}


auto Menu::setFont(const sf::Font &font) -> void {
    this->font = font;
    for(auto& button : buttons){
        button.setFont(font);
    }
}


auto Menu::loadGameClicked() -> bool {
    return buttons[1].getPressed();
}

auto Menu::textObjColor(sf::Color color) -> void {
    for(auto& button : buttons){
        button.textObjColor(color);
    }

}

auto Menu::startGameClicked() -> bool {
    return buttons[0].getPressed();
}
auto Menu::optionsGameClicked() -> bool {
    return buttons[2].getPressed();
}

auto Menu::exitGameClicked() -> bool {
    return buttons[3].getPressed();
}
