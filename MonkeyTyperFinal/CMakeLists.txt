cmake_minimum_required(VERSION 3.27)
project(MonkeyProject)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

Include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG
        2.6.1)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY
        https://github.com/fmtlib/fmt
        GIT_TAG
        10.2.1)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(fmt)


add_executable(MonkeyProject main.cpp
        game/App.cpp
        game/App.h
        game/Screen.cpp
        game/Screen.h
        game/Menu.cpp
        game/Menu.h
        game/Button.cpp
        game/Button.h
        game/Game.cpp
        game/Game.h
        game/Word.cpp
        game/Word.h
        game/Settings.cpp
        game/Settings.h
        game/Difficulty.cpp
        game/Difficulty.h
)
target_link_libraries(MonkeyProject fmt sfml-graphics)
