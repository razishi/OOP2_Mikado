#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Texture {
public:
    Texture(const std::string& fontPath, const std::string& clockImagePath, const std::string& scoreImagePath,
        const std::string& helpImagePath, const std::string& saveImagePath, int windowWidth, int windowHeight);
    void updateTimerText(int remainingTime);
    void updateScoreText(int score);
    void updatePickedSticksText(int numPickedSticks);
    void updateRemainingSticksText(int remainingSticks);
    void draw(sf::RenderWindow& window, bool isWin, bool isLose);
    bool isClickOnHelpIcon(sf::Vector2f point);
    void updatePickableSticksText(int pickableSticks);
    bool isClickOnSaveIcon(sf::Vector2f point);

private:
    void loadResources(const std::string& fontPath, const std::string& clockImagePath, const std::string& scoreImagePath,
   const std::string& helpImagePath, const std::string& saveImagePath);
    void initializeText();
    void initializeSprites(int windowWidth, int windowHeight);
    void initializeScoreSprite(int windowWidth, int windowHeight);
    void initializeHelpSprite(int windowWidth, int windowHeight);
    void initializeSaveSprite(int windowWidth, int windowHeight);
    void initializeClockSprite(int windowWidth, int windowHeight);

    // Font and text elements
    sf::Font m_font;
    sf::Font m_arialFont;
    sf::Text m_currentTimerText;
    sf::Text m_scoreText;
    sf::Text m_pickedSticksText;
    sf::Text m_remainingSticksText;
    sf::Text m_winText;
    sf::Text m_loseText;
    sf::Text m_pickableSticksText;

    // Textures and sprites
    sf::Texture m_clockTexture;
    sf::Texture m_scoreTexture;
    sf::Texture m_helpTexture;
    sf::Texture m_saveTexture;

    sf::Sprite m_clockSprite;
    sf::Sprite m_scoreSprite;
    sf::Sprite m_helpSprite;
    sf::Sprite m_saveSprite;
};

