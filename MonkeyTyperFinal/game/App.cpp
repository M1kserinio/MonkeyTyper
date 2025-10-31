//
// Created by Mikołaj on 15.05.2024.
//

#include "App.h"
#include "Menu.h"
#include "Game.h"
#include "Difficulty.h"
#include "Button.h"


App::App() : window(sf::RenderWindow(sf::VideoMode(800,600), "Monkey")),currentWindow(Windows::MENU) {
    if (!currentFont.loadFromFile("../dodatk/Arial.ttf")) {
        fmt::println("invalid font");
        exit(1);
    }

    window.setFramerateLimit(60);
    currentS = std::make_unique<Menu>(currentFont); //

}


auto App::mainLoop() -> void {

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                exitGame();

            currentS->onEvent(event);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                changeWindows(Windows::MENU);
                break;
            } /*else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1 && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
                currentFont.loadFromFile("../dodatk/Arial.ttf");
            }else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
                currentFont.loadFromFile("../dodatk/Mantey-Black.ttf");

            }else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3
                 && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
                currentFont.loadFromFile("../dodatk/rougeta.ttf");
            }*/

            switch (currentWindow) {

                case Windows::MENU: {
                    Menu* menu = dynamic_cast<Menu*>(currentS.get());
                            if (menu->startGameClicked()) {
                                changeWindows(Windows::DIFFICULTY);

                            } else if(menu->loadGameClicked()) {
                                changeWindows(Windows::LOAD_GAME);
                            } else if (menu->optionsGameClicked()){
                                changeWindows(Windows::SETTINGS);
                            } else if(menu->exitGameClicked()) {
                                exitGame();
                            }
                            break;
                }
                case Windows::DIFFICULTY: {
                    Difficulty* difficulty = dynamic_cast<Difficulty*>(currentS.get());
                    if (difficulty->easyClicked()){
                        changeWindows(Windows::GAME, Difficulty::EASY);

                    }else if (difficulty->mediumClicked()){
                        changeWindows(Windows::GAME, Difficulty::MEDIUM);

                    } else if(difficulty->hardClicked()){
                        changeWindows(Windows::GAME, Difficulty::HARD);

                    } else if(difficulty->backClicked()){
                        changeWindows(Windows::MENU);

                        break;
                    }
                    break;
                }

                case Windows::GAME : {
                    Game* game = dynamic_cast<Game*>(currentS.get());


                    if (game->menuButtonClicked() ) {
                        changeWindows(Windows::MENU);
                    } else if (game->modeButtonClicked()){
                        changeWindows(Windows::DIFFICULTY);

                    } else if(game->exitButtonClicked()){
                        exitGame();
                        break;
                    }
                    break;


                }

                case Windows::SETTINGS : {
                    Settings* settings = dynamic_cast<Settings*>(currentS.get());
                    if (settings->backClicked()) {
                        changeWindows(Windows::MENU);

                    } else if (settings->firstFont()) {
                        currentFont.loadFromFile("../dodatk/Arial.ttf");

                    } else if (settings->secondFont()) {
                        currentFont.loadFromFile("../dodatk/Mantey-Black.ttf");
                       // https://www.1001freefonts.com/mantey.font

                    } else if(settings->thirdFont()) {
                        currentFont.loadFromFile("../dodatk/rougeta.ttf");
                       // https://www.1001freefonts.com/rougeta.font
                    }else if (settings->whiteFont()) {
                        currentTextObj = sf::Color::White;
                        currentS->textObjColor(currentTextObj);


                    } else if (settings->blackFont()) {
                        currentTextObj = sf::Color::Black;
                        currentS->textObjColor(currentTextObj);

                    } else if (settings->purpleFont()){
                        currentTextObj = sf::Color::Magenta;
                        currentS->textObjColor(currentTextObj);

                    }
                    break;
                }


            }
        }
        currentS->update();
        window.clear(sf::Color::Black);

        window.draw(backgroundS);
        currentS->draw(window);


        window.display();
    }
}
auto App::changeWindows(Windows newWind, Difficulty::MODE mode) -> void {
    currentWindow = newWind;
    switch (newWind) {
        case Windows::MENU :
            currentS = std::make_unique<Menu>(currentFont);
            break;
        case Windows::DIFFICULTY :
            currentS = std::make_unique<Difficulty>(currentFont);
            break;

        case Windows::GAME : {
            currentS = std::make_unique<Game>(currentFont,mode);
            break;

        }
        case Windows::SETTINGS:
            currentS = std::make_unique<Settings>(currentFont);
            break;

        case Windows::LOAD_GAME:
            currentS = Game::load(currentFont);
            currentWindow = Windows::GAME;

            break;

    }
    currentS ->textObjColor(currentTextObj);
}


auto App::exitGame() -> void {
    window.close();
}

auto App::onEvent(sf::Event &event) -> void {

}




