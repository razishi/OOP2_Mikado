#pragma once
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Stick.h"

class Board {
public:
    Board(int numSticks, float stickWidth);
    void draw(sf::RenderWindow& window);
    void Build(int numSticks,  float stickWidth);
    std::vector<Stick>& getSticks();
    Stick* getPickableStick();
    std::vector<Stick*> getPickableSticks();
    void ClearSticks();

private:
    std::vector<Stick> m_sticks;



};

