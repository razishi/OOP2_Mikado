#pragma once
#include <cmath>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Globals.h"

class Stick {
public:
    sf::RectangleShape shape;
    sf::Vector2f startPoint;
    sf::Vector2f endPoint;
  
    Stick(sf::Vector2f point1, sf::Vector2f point2, sf::Color color, float width, int seqNum, int score);
    void draw(sf::RenderWindow& window);
    void scheduleFlickering(unsigned delay);
    static bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
    static int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
    static bool doIntersect(Stick a, Stick b);
    void flicker();
    void startFlickering(); 
    void updateFlickering(); 
    int getScoreValue() const { return m_scoreValue; }
    bool isPointOnStick(sf::Vector2f point);
    bool getCanBePicked() const { return m_canBePicked; }
    int getSequenceNumber() const { return m_sequenceNumber; }

private : 

    bool m_canBePicked;
    int m_sequenceNumber;
    int m_scoreValue;

    bool m_isFlickering = false;
    std::chrono::steady_clock::time_point m_flickerStartTime;
    int m_flickerDuration = 1000; 
    int m_flickerFrequency = 200;
    sf::Color m_originalColor;  
    void initializeShape(sf::Vector2f point1, sf::Vector2f point2, float width, sf::Color color);
    float calculateLength(sf::Vector2f direction);
    float calculateRotation(sf::Vector2f direction);


};

