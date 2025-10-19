#include "Game.h"

Game::Game(int numSticks, float stickWidth, int timeLimit, sf::Vector2u windowSize)
    : m_board(numSticks, stickWidth),
    m_score(0),
    m_numPickedSticks(0),
    m_timeLimit(timeLimit),
    m_windowSize(windowSize),
    m_texture("C:/Windows/Fonts/BRUSHSCI.ttf", "clock.png", "score.png", "help.png", "save.png",
        windowSize.x, windowSize.y),
    m_isWin(false),
    m_isLose(false) {
    m_timer.restart();
    updateRemainingSticksText();
    updatePickableSticksText(); // Initialize pickable sticks text
}


//--------------------------------------------------------------
// Updates the game state by checking win/loss conditions, updating the timer, score, 
//picked sticks, remaining sticks, and pickable sticks text, and sets the lose condition if time runs out.
void Game::update() {
    if (m_isWin || m_isLose) {
        return; // Stop updating if the player has won or lost
    }

    sf::Time elapsed = m_timer.getElapsedTime();
 
    int remainingTime = m_timeLimit - static_cast<int>(elapsed.asSeconds());
    if (remainingTime < 0) remainingTime = 0;

    m_texture.updateTimerText(remainingTime);
    m_texture.updateScoreText(m_score);
    m_texture.updatePickedSticksText(m_numPickedSticks);
    m_texture.updateRemainingSticksText(m_remainingSticks);
    updatePickableSticksText();


    if (remainingTime == 0) {
        m_isLose = true;
    }
}

//--------------------------------------------------------------

void Game::draw(sf::RenderWindow& window) {
    m_board.draw(window);
    m_texture.draw(window, m_isWin, m_isLose);
}



//--------------------------------------------------------------
// Handles mouse click events by checking for win/loss conditions, determining if the click is
//  on a help or save icon, processing stick clicks, updating remaining and pickable sticks text, and setting the
//  win flag if all sticks are picked.

void Game::handleMouseClick(int x, int y) {
    if (m_isWin || m_isLose) {
        return; // Do nothing if the player has already won or lost
    }

    sf::Vector2f clickPoint(x, y);

    if (m_texture.isClickOnHelpIcon(clickPoint)) {
        handleHelpClick();
    }
    else if (m_texture.isClickOnSaveIcon(clickPoint)) {
        handleSaveClick();
    }
    else {
        handleStickClick(clickPoint);
    }

    updateRemainingSticksText();
    updatePickableSticksText(); // Update pickable sticks text

    if (m_board.getSticks().empty()) {
        m_isWin = true; // Set win flag if all sticks are picked up
    }
}

//--------------------------------------------------------------
// Handles help click events by sorting pickable sticks based on score, scheduling their 
// flickering with incremental delays, and updating the pickable sticks text.
void Game::handleHelpClick() {
    std::vector<Stick*> pickableSticks = m_board.getPickableSticks();
    std::sort(pickableSticks.begin(), pickableSticks.end(),
        [](const Stick* a, const Stick* b) { return a->getScoreValue() > b->getScoreValue(); });

    unsigned delay = 0;
    for (Stick* stick : pickableSticks) {
        stick->scheduleFlickering(delay);
        delay += 500; // Increment delay for each subsequent stick
    }

    m_texture.updatePickableSticksText(pickableSticks.size()); // Update pickable sticks text
}

//--------------------------------------------------------------
// Handles stick click events by checking if the click is on any stick, validating if 
//the stick can be picked, updating the score and picked sticks count, and removing the picked stick.
void Game::handleStickClick(const sf::Vector2f& clickPoint) {
    auto& sticks = m_board.getSticks();

    for (size_t i = 0; i < sticks.size(); ++i) {
        if (sticks[i].isPointOnStick(clickPoint)) {
            if (canPickStick(sticks[i], sticks)) {
                m_score += sticks[i].getScoreValue();
                m_numPickedSticks++;
                m_texture.updatePickedSticksText(m_numPickedSticks);
                sticks.erase(sticks.begin() + i);
                break; // Exit the loop after picking a stick
            }
        }
    }
}

//--------------------------------------------------------------
// Determine if a stick can be picked up by checking for intersections with higher-sequence
//  sticks and initiating flickering on any obstructing sticks.
bool Game::canPickStick(const Stick& stick, const std::vector<Stick>& sticks) {
    int currentSeqNum = stick.getSequenceNumber();
    std::vector<Stick*> obstructingSticks;

    for (const auto& otherStick : sticks) {
        if (stick.getSequenceNumber() != otherStick.getSequenceNumber() &&
            Stick::doIntersect(stick, otherStick) &&
            otherStick.getSequenceNumber() > currentSeqNum) {
            obstructingSticks.push_back(const_cast<Stick*>(&otherStick));
        }
    }

    if (!obstructingSticks.empty()) {
        for (Stick* obstructingStick : obstructingSticks) {
            obstructingStick->startFlickering();
        }
        return false;
    }

    return true;
}

//--------------------------------------------------------------
// Updates the remaining sticks count and updates the remaining sticks text display.
void Game::updateRemainingSticksText() {
    m_remainingSticks = m_board.getSticks().size();
    m_texture.updateRemainingSticksText(m_remainingSticks);
}

//--------------------------------------------------------------
// Updates the pickable sticks text display by getting the number of pickable sticks from the board.
void Game::updatePickableSticksText() {
    std::vector<Stick*> pickableSticks = m_board.getPickableSticks();
    m_texture.updatePickableSticksText(pickableSticks.size());
}


//--------------------------------------------------------------
// Handles save click events by creating and writing game state and stick data to a save file.

void Game::handleSaveClick() {
    std::ofstream saveFile("game_save.txt");
    if (!saveFile.is_open()) {
        std::cerr << "Failed to open save file." << std::endl;
        return;
    }

    // Saving game states
    saveFile << "Score: " << m_score << std::endl;
    saveFile << "Time: " << m_timeLimit - static_cast<int>(m_timer.getElapsedTime().asSeconds()) << std::endl;
    saveFile << "Picked: " << m_numPickedSticks << std::endl;
    saveFile << "Remaning: " << m_remainingSticks << std::endl;

    // Saving each stick's data
    for (const Stick& stick : m_board.getSticks()) {
        saveFile << "Stick: " << stick.getSequenceNumber() << " "
            << stick.startPoint.x << " " << stick.startPoint.y << " "
            << stick.endPoint.x << " " << stick.endPoint.y << " "
            << stick.shape.getFillColor().toInteger() << " "
            << stick.getScoreValue() << std::endl;
    }

    saveFile.close();
}


//--------------------------------------------------------------
void Game::setSavedScore(int Score)
{
    m_score = Score; 
}

//--------------------------------------------------------------
void Game::setSavedTimeLimit(int TimeLimit)
{
    m_timeLimit = TimeLimit;
}

//--------------------------------------------------------------
void Game::setSavedPickedSticks(int PickedSticks)
{
    m_numPickedSticks = PickedSticks;
}

//--------------------------------------------------------------
void Game::setSavedremainingSticks(int remainingSticks) {
    m_remainingSticks = remainingSticks;
}

