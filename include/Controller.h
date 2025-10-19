#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Board.h"

class Controller {
public:
    Controller(int windowWidth, int windowHeight, int numSticks, float stickWidth, int timeLimit);
    void run();

    void loadGame(const std::string& filename);

private:
    sf::RenderWindow m_window;
    Game m_game;
};

