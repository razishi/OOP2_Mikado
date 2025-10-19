#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Texture.h"
#include <algorithm> 
#include <iostream>
#include <sstream>
#include <fstream>


class Game {
public:
    Game(int numSticks, float stickWidth, int timeLimit, sf::Vector2u windowSize);
    void update();
    void draw(sf::RenderWindow& window);
    void setSavedScore(int Score);
    void setSavedTimeLimit(int TimeLimit);
    void setSavedPickedSticks(int PickedSticks);
    void setSavedremainingSticks(int remainingSticks);

    void handleMouseClick(int x, int y);
    sf::Vector2u m_windowSize;
    Texture m_texture;
    sf::Clock m_timer;
    Board m_board;
    Board& getBoard() { return m_board; }

private:
    void handleHelpClick();
    void handleSaveClick();
    void handleStickClick(const sf::Vector2f& clickPoint);
    bool canPickStick(const Stick& stick, const std::vector<Stick>& sticks);
    void updateRemainingSticksText();
    void updatePickableSticksText();


    int m_score;
    bool m_isWin;
    bool m_isLose;
    int m_timeLimit;
    int m_remainingSticks;
    int m_numPickedSticks;

};

