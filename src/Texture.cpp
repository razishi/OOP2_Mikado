#include "Texture.h"

Texture::Texture(const std::string& fontPath, const std::string& clockImagePath, const std::string& scoreImagePath,
    const std::string& helpImagePath,
    const std::string& saveImagePath, int windowWidth, int windowHeight) {

    loadResources(fontPath, clockImagePath, scoreImagePath, helpImagePath, saveImagePath);
    initializeText();
    initializeSprites(windowWidth, windowHeight);
    updatePickedSticksText(0);
    updateRemainingSticksText(0);
}

//--------------------------------------------------------------
// Loads resources such as fonts and images for the texture.
void Texture::loadResources(const std::string& fontPath, const std::string& clockImagePath, const std::string& scoreImagePath,
    const std::string& helpImagePath,
    const std::string& saveImagePath) {

    if (!m_font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font" << std::endl;
    }
    if (!m_arialFont.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error loading Arial font" << std::endl;
    }
    if (!m_clockTexture.loadFromFile(clockImagePath)) {
        std::cerr << "Error loading clock image" << std::endl;
    }
    if (!m_scoreTexture.loadFromFile(scoreImagePath)) {
        std::cerr << "Error loading score image" << std::endl;
    }
    if (!m_helpTexture.loadFromFile(helpImagePath)) {
        std::cerr << "Error loading help image" << std::endl;
    }
    if (!m_saveTexture.loadFromFile(saveImagePath)) {
        std::cerr << "Error loading save image" << std::endl;
    }
}

//--------------------------------------------------------------
// Initializes text elements with specified fonts, sizes, colors, and positions.
void Texture::initializeText() {
    m_currentTimerText.setFont(m_font);
    m_currentTimerText.setCharacterSize(40);
    m_currentTimerText.setFillColor(sf::Color::Black);

    m_winText.setFont(m_arialFont);
    m_winText.setCharacterSize(60);
    m_winText.setFillColor(sf::Color::Red);
    m_winText.setString("You Win!");
    m_winText.setPosition(400, 400);

    m_loseText.setFont(m_arialFont);
    m_loseText.setCharacterSize(60);
    m_loseText.setFillColor(sf::Color::Red);
    m_loseText.setString("You Lose!");
    m_loseText.setPosition(400, 400);
    m_pickableSticksText.setFont(m_font); // Initialize pickable sticks text
    m_pickableSticksText.setCharacterSize(40);
    m_pickableSticksText.setFillColor(sf::Color::Black);
    m_pickableSticksText.setPosition(10.0f, 110.0f);
}

//--------------------------------------------------------------
// Initializes sprites for clock, score, help, and save icons based on window dimensions.
void Texture::initializeSprites(int windowWidth, int windowHeight) {
    initializeClockSprite(windowWidth, windowHeight);
    initializeScoreSprite(windowWidth, windowHeight);
    initializeHelpSprite(windowWidth, windowHeight);
    initializeSaveSprite(windowWidth, windowHeight);
}

//--------------------------------------------------------------
// Initializes the clock sprite with the clock texture, scale, and position at the top center of the window.
void Texture::initializeClockSprite(int windowWidth, int windowHeight) {
    m_clockSprite.setTexture(m_clockTexture);
    m_clockSprite.setScale(0.3f, 0.2f);
    float clockX = (windowWidth - m_clockSprite.getGlobalBounds().width) / 1 / 2.0f;
    float clockY = 10.0f; // Place it at the top center
    m_clockSprite.setPosition(clockX, clockY);
}

//--------------------------------------------------------------
// Initializes the score sprite with the score texture, scale, and position to the right of the clock sprite.
void Texture::initializeScoreSprite(int windowWidth, int windowHeight) {
    m_scoreSprite.setTexture(m_scoreTexture);
    m_scoreSprite.setScale(0.3f, 0.2f);
    float scoreX = m_clockSprite.getPosition().x + m_clockSprite.getGlobalBounds().width + 150.0f;
    float scoreY = m_clockSprite.getPosition().y;
    m_scoreSprite.setPosition(scoreX, scoreY);
}

//--------------------------------------------------------------
// Initializes the help sprite with the help texture, scale, and position at the bottom right corner of the window.
void Texture::initializeHelpSprite(int windowWidth, int windowHeight) {
    m_helpSprite.setTexture(m_helpTexture);
    m_helpSprite.setScale(0.3f, 0.3f);
    float helpX = windowWidth - m_helpSprite.getGlobalBounds().width - 10.0f;
    float helpY = windowHeight - m_helpSprite.getGlobalBounds().height - 10.0f;
    m_helpSprite.setPosition(helpX, helpY);
}

//--------------------------------------------------------------
// Initializes the save sprite with the save texture, scale, and position at the bottom left corner of the window.
void Texture::initializeSaveSprite(int windowWidth, int windowHeight) {
    m_saveSprite.setTexture(m_saveTexture);
    m_saveSprite.setScale(0.3f, 0.3f);
    float saveX = 10.0f;
    float saveY = windowHeight - m_saveSprite.getGlobalBounds().height - 10.0f;
    m_saveSprite.setPosition(saveX, saveY);
}

//--------------------------------------------------------------
// Updates the timer text with the remaining time and adjusts its position relative to the clock sprite.
void Texture::updateTimerText(int remainingTime) {
    m_currentTimerText.setString(": " + std::to_string(remainingTime));
    m_currentTimerText.setPosition(m_clockSprite.getPosition().x + m_clockSprite.getGlobalBounds().width + 10,
        m_clockSprite.getPosition().y);
}

//--------------------------------------------------------------
// Updates the score text with the current score and adjusts its position relative to the score sprite.
void Texture::updateScoreText(int score) {
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(40);
    m_scoreText.setFillColor(sf::Color::Black);
    m_scoreText.setString(": " + std::to_string(score));
    m_scoreText.setPosition(m_scoreSprite.getPosition().x + m_scoreSprite.getGlobalBounds().width + 10.0f, 10.0f);
}

//--------------------------------------------------------------
// Updates the picked sticks text with the number of picked sticks and sets its position.
void Texture::updatePickedSticksText(int numPickedSticks) 
{
    m_pickedSticksText.setFont(m_font);
    m_pickedSticksText.setCharacterSize(40);
    m_pickedSticksText.setFillColor(sf::Color::Black);
    m_pickedSticksText.setString("Picked up: " + std::to_string(numPickedSticks));
    m_pickedSticksText.setPosition(10.0f, 10.0f);
}

//--------------------------------------------------------------
// Updates the remaining sticks text with the number of remaining sticks and sets its position.
void Texture::updateRemainingSticksText(int remainingSticks) {
    m_remainingSticksText.setFont(m_font);
    m_remainingSticksText.setCharacterSize(40);
    m_remainingSticksText.setFillColor(sf::Color::Black);
    m_remainingSticksText.setString("Remaining: " + std::to_string(remainingSticks));
    m_remainingSticksText.setPosition(10.0f, 60.0f);
}

//--------------------------------------------------------------
void Texture::draw(sf::RenderWindow& window, bool isWin, bool isLose) {
    window.draw(m_clockSprite);
    window.draw(m_scoreSprite);
    window.draw(m_helpSprite);
    window.draw(m_saveSprite);
    window.draw(m_currentTimerText);
    window.draw(m_scoreText);
    window.draw(m_pickedSticksText);
    window.draw(m_remainingSticksText);
    window.draw(m_pickableSticksText);

    if (isWin) {
        window.draw(m_winText);
    }
    else if (isLose) {
        window.draw(m_loseText);
    }
}

//--------------------------------------------------------------
// Updates the pickable sticks text with the number of pickable sticks.
void Texture::updatePickableSticksText(int pickableSticks) {
    m_pickableSticksText.setString("Pickable: " + std::to_string(pickableSticks));
}

//--------------------------------------------------------------
// Checks if the given point is within the bounds of the help icon sprite.
bool Texture::isClickOnHelpIcon(sf::Vector2f point) {
    return m_helpSprite.getGlobalBounds().contains(point);
}

//--------------------------------------------------------------
// Checks if the given point is within the bounds of the save icon sprite.
bool Texture::isClickOnSaveIcon(sf::Vector2f point) {
    return m_saveSprite.getGlobalBounds().contains(point);
}
