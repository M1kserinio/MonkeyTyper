//
// Created by Mikołaj on 25/05/2024.
//

#include "Difficulty.h"


Difficulty::Difficulty(sf::Font &font) : font(font) {

    if (!backgroundT.loadFromFile("../dodatk/DiffMalpa.jpeg")){
        fmt::println("image error");
        exit(3);
        //https://stock.adobe.com/pl/images/funny-monkey-with-sunglasses-in-a-suit-on-a-black-background/678280868
        //tak, wzialem miesiac probny zeby miec licenjce
    }
    backgroundS.setPosition(-150,250);
    backgroundS.setTexture(backgroundT);

    std::string easyText = "Easy";
    std::string mediumText = "Medium";
    std::string hardText = "Hard";
    std::string backText = "Back";

    buttons.emplace_back(300,150,easyText,font, sf::Color::Green,200,70);
    buttons.emplace_back(300,250,mediumText,font,sf::Color::Yellow,200,70);
    buttons.emplace_back(300,350,hardText,font, sf::Color::Red,200,70);
    buttons.emplace_back(600,500,backText,font,sf::Color::Blue,200,70);


}

auto Difficulty::draw(sf::RenderWindow &window) -> void {

    window.draw(backgroundS);

    for(auto& button : buttons) {
        button.draw(window);
    }

    sf::Text header("Game Mode",font,50);
    header.setPosition(260.0f,50.f);
    window.draw(header);
}
auto Difficulty::onEvent(sf::Event &event) -> void {
    for(auto& button : buttons){
        button.oneEvent(event);
    }
}


auto Difficulty::update() -> void {

}
auto Difficulty::rand(int from, int to) -> int {
    return from + std::rand() % (to-from + 1);
}



auto Difficulty::getWordSpeed(Difficulty::MODE mode) -> float {
    switch (mode) {
        case MODE::EASY: {
            return 0.9f;

        }
        case MODE::MEDIUM: {
            return 1.5f;
            //fmt::println("1.1f");
        }

        case MODE::HARD: {
            return 1.7f;

        }
            break;

    }

}


auto Difficulty::getWordCreationTime(Difficulty::MODE mode) -> sf::Time {
    switch (mode) {
        case MODE::EASY:
            return sf::seconds(1.5f);
            //  return sf::seconds(rand(1,2));  <-- chcialem zrobic by tworzyly sie losowo pomidzy jakas iloscia sekund
            //ale zbyt dlugo trwalo wiec odpuscilem

        case MODE::MEDIUM:
            return sf::seconds(1.3f);

            //return sf::seconds(rand(1,2));//3.0 -4.0 - easy
        case MODE::HARD:
            return sf::seconds(1.5f);

    }
}
auto Difficulty::setFont(const sf::Font &font) -> void {
    this->font = font;
    for(auto& button : buttons){
        button.setFont(font);
    }
}


auto Difficulty::dictionares(Difficulty::MODE mode) -> std::string {
    switch (mode) {
        case MODE::EASY : {
            return "../dodatk/easyWords.txt";
        }
        case MODE::MEDIUM: {
            return  "../dodatk/mediumWordds.txt";
        }
        case MODE::HARD : {
            return "../dodatk/Words.txt";
        }
            break;
        
    }
}

auto Difficulty::textObjColor(sf::Color color) -> void {
    for(auto& button : buttons){
        button.textObjColor(color);
    }

}
auto Difficulty::easyClicked() -> bool {
    return buttons[0].getPressed(); // juz nie naprawei bo pisze to przed odeslaniem do Pana pracy ale zdaje sobie sprawe
                                    // ze mozna bylo zminimalizowac te czesci z guzikami
}
auto Difficulty::mediumClicked() -> bool {
    return buttons[1].getPressed();
}
auto Difficulty::hardClicked() -> bool {
    return buttons[2].getPressed();
}
auto Difficulty::backClicked() -> bool {
    return buttons[3].getPressed();
}
