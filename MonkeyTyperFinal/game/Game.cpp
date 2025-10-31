//
// Created by Mikołaj on 18.05.2024.
//

#include "Game.h"

#define SAVE "save.txt"


auto Game::draw(sf::RenderWindow &window) -> void {

    window.draw(backgroundS);

    for(auto& word : words) {
        word.xColor();

        if (input.get().size() > 0 && word.get().substr(0, input.get().size()) == input.get()) {
            word.setColor(sf::Color::Magenta);
        }

        word.draw(window);
        word.resetColor();
    }
    input.setTextSize(22);
    input.draw(window);
    wordCountInfo.setTextSize(25);
    wordCountInfo.draw(window);
    sf::Text score("SCORE:",font,25);
    score.setPosition(630,530); //230 ,30
    sf::Text info("If the same word crosses \nthe screen twice, you lose!",font,20);
    info.setPosition(340,530);

    window.draw(info);
    window.draw(score);

    window.draw(separatorRect);
    window.draw(separatorUIScore);
    window.draw(separatorUIInput);

    if (gameOver) {
        fmt::println("game overr");
        for(auto& button: buttons){
            button.draw(window);
        }
        sf::Text gameoverText("GAME OVER ;( \nSCORE: " + std::to_string(wordCount),font,50);
        gameoverText.setFillColor(sf::Color::Red);
        gameoverText.setPosition(100,30);
        window.draw(gameoverText);

    }

}


auto Game::onEvent(sf::Event &event) -> void {
    if (gameOver) {
        for (auto &button: buttons) {
            button.oneEvent(event);
        }
        return;

    }

    switch (event.type) {
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    input.set("");
                    return;
                } else if (event.key.code == sf::Keyboard::Num9) {
                    setWordTextSize(18);
                } else if (event.key.code == sf::Keyboard::Num0) {
                    setWordTextSize(25);
                }
            } else {
                if (event.key.code == sf::Keyboard::Enter) {
                    for (auto &word: words) {
                        if (word.get() == input.get()) {
                            if (removeWord(input.get())) {
                                input.set("");
                                wordCount++;
                                wordCountInfo.set(std::to_string(wordCount));
                            }
                        }
                    }
                } else if (event.key.code == sf::Keyboard::BackSpace) {
                    input.popCharacter();
                }
            }
            break;

        case sf::Event::TextEntered:
            if (event.text.unicode >= 'a' && event.text.unicode <= 'z') {
                input.append(static_cast<char>(event.text.unicode));
            }
            break;

        default:
            break;
    }
}


Game::Game(sf::Font &font, Difficulty::MODE difficulty) : font(font), gameOver(false),
input(Word(10,530,&font,Difficulty::getWordSpeed(difficulty))), wordCount(0), wordCountInfo(Word(735,530,&font,1.0f)),
wordSpeed(Difficulty::getWordSpeed(difficulty)),
wordCreationTime(Difficulty::getWordCreationTime(difficulty)),difficulty(difficulty),wordsSiez(18)
{
    if (!backgroundT.loadFromFile("../dodatk/GameBack.jpeg")){
        fmt::println("image error");
        exit(3); //https://unsplash.com/photos/a-black-sky-with-a-lot-of-stars-CEtIM994vaI
    }
    backgroundS.setPosition(0,0);
    backgroundS.setTexture(backgroundT);

    std::srand(time(nullptr)); // takie ala zawsze "losowe" ziarno, jak np. w minecraft, uzaleznione od obecnego czasu
    wordCountInfo.set("0");     //podobnie robilem kiedys przy tetrisie
    loadDictionary();
    words.emplace_back(10,randWordY(),randWord(),&font,wordSpeed);
    resetWordTimer();

    separatorRect.setSize(sf::Vector2f(800,20) );
    separatorRect.setPosition(0,480);
    separatorRect.setFillColor(sf::Color::Blue);

    separatorUIScore.setSize(sf::Vector2f(10,100)); // 20,90
    separatorUIScore.setPosition(600,500);
    separatorUIScore.setFillColor(sf::Color::Blue);

    separatorUIInput.setSize(sf::Vector2f(10,100));
    separatorUIInput.setPosition(310,500);
    separatorUIInput.setFillColor(sf::Color::Blue);

    std::string text = "Menu";
    std::string text1 = "Mode";
    std::string tex2 = "Exit";



    buttons.emplace_back(100,170,text,font,sf::Color::Blue,200,70);
    buttons.emplace_back(100,270,text1,font,sf::Color::Blue,200,70);
    buttons.emplace_back(100,370,tex2,font,sf::Color::Blue,200,70);



}


auto Game::rand(int from, int to) -> int {
    return from + std::rand() % (to-from + 1);
}

auto Game::update() -> void {
    if (gameOver) {
        words.clear();
        if (!backgroundT.loadFromFile("../dodatk/biggie.jpg")){
            fmt::println("image gameOver errpr");
            exit(3);
        }
        backgroundS.setPosition(300,100);
        backgroundS.setTexture(backgroundT);
        input.set("GAME OVER");
        wordCountInfo.set("0");

        return;
    }

    for(auto& word : words) {

        word.update(wordSpeed);

        word.setTextSize(wordsSiez);

        if (word.getRoundCount() == 0) {
            gameOver = true;
        }
    }
    if (wordCreationClock.getElapsedTime() >= nextWordCreateTime){
        words.emplace_back(10,randWordY(),randWord(),&font,wordSpeed);
        resetWordTimer();
        save();
    }

}
auto Game::randWordY() -> int {

    return 10 + rand(0,390); //* 25;
}


auto Game::resetWordTimer() -> void {
    wordCreationClock.restart();

    nextWordCreateTime = wordCreationTime;

}


auto Game::removeWord(const std::string &text) -> bool {
    auto it = std::remove_if(words.begin(), words.end(), [&text](const Word& w) -> bool {
        return text == w.get();
    });
    if(it != words.end()) {
        words.erase(it);
        return true;
    } else return false;
//    std::vector<Word> wordsEntered;
//    bool found = false;
//    for(auto& w : words) {
//        if (w.get() != text){          // <- bylem zdziwiony ze pythonowy styl jest za wolny na gierke i mega opoznineie
//            found = true;              // bylo wiec musialem uzyc zwyklego it i erase
//        }
//    }
//    if (found) {
//        words.clear();
//        words.swap(wordsEntered);
//    }

}


auto Game::loadDictionary() -> void {
    std::string dictionaryFile = Difficulty::dictionares(difficulty);
    std::ifstream fileIn(dictionaryFile);
    if (!fileIn.is_open()) {
        fmt::println("dictionary not working!!!!!");
        exit(2);
    }
    while (!fileIn.eof()) {
        std::string word;
        fileIn >> word;
        dictionary.push_back(word);
    }
    fileIn.close();
}


auto Game::randWord() -> std::string {
    return dictionary[rand(0,dictionary.size() -1)];
}


auto Game::setFont(const sf::Font &font) -> void {
    this->font = font;
    for(auto& button : buttons){
        button.setFont(font);
    }
}





auto Game::save() -> void {
    auto out = std::ofstream (SAVE);
    if(!out.is_open()) {
        fmt::println("nie mozna zpaisac gry");
        exit(4);
    }
    out << wordCount << std::endl;
    out << difficulty << std::endl;
    out << wordSpeed << std::endl;
    for(auto& word : words) {
        word.serialize(out);
    }
    out.close();
}

auto Game::load(sf::Font& font) -> std::unique_ptr<Game> {
    std::ifstream in(SAVE);
    if(!in.is_open()) {
        fmt::println("nie mozna zaladowac gry");
        exit(5);
    }

    int wordCount;
    int difficulty;
    float wordSpeed;
    in >> wordCount >> difficulty >> wordSpeed;
    auto game = std::make_unique<Game>(font, (Difficulty::MODE)difficulty); // musialem tworzyc nowa na unique by
    game->wordCount = wordCount;                                               //wczytywanie jakkolwiek dzialalo
    game->wordSpeed = wordSpeed;
    while(!in.eof()) {
        game->words.push_back(Word::deserialize(in, font));
    }

    return game;
}
auto Game::setWordTextSize(int size) -> void {
    wordsSiez = size;
    for (auto &word : words) {
        word.setTextSize(wordsSiez);
    }
}

auto Game::textObjColor(sf::Color color) -> void {
    for(auto& button : buttons){
        button.textObjColor(color);
    }

}

auto Game::menuButtonClicked() -> bool {
    return buttons[0].getPressed();
}

auto Game::modeButtonClicked() -> bool {
    return buttons[1].getPressed();
}
auto Game::exitButtonClicked() -> bool {
    return buttons[2].getPressed();
}



