#include "Controller.h"

Controller::Controller(int windowWidth, int windowHeight, int numSticks, float stickWidth, int timeLimit)
    : m_window(sf::VideoMode(windowWidth, windowHeight), "Pick Up Sticks Game"),
    m_game(numSticks, stickWidth, timeLimit, m_window.getSize()) { 
    m_window.setFramerateLimit(60);
    m_window.clear(sf::Color(200, 200, 200)); 
    m_window.display();
}

//--------------------------------------------------------------
// run the game
void Controller::run() {
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                    m_game.handleMouseClick(mousePos.x, mousePos.y);
                }
            }
        }

        m_game.update();

        m_window.clear(sf::Color(200, 200, 200)); // Clear window 

        m_game.draw(m_window);

        m_window.display();
    }
}


//--------------------------------------------------------------
// Loads game state from a file, updating the board, score, time limit, picked sticks,
//  and remaining sticks, then starts the game.
void Controller::loadGame(const std::string& filename) {
    std::ifstream loadFile(filename);
    if (!loadFile.is_open()) {
        std::cerr << "Failed to open load file: " << filename << std::endl;
        return;
    }

    m_game.getBoard().ClearSticks();
    std::string line;
    while (getline(loadFile, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;


        if (key == "Stick:") {
            float startX, startY, endX, endY;
            int seqNum, scoreValue;
            unsigned int colorInt;
            iss >> seqNum >> startX >> startY >> endX >> endY >> colorInt >> scoreValue;

            sf::Vector2f startPoint(startX, startY), endPoint(endX, endY);
            sf::Color color(colorInt);
            Stick newStick(startPoint, endPoint, color, stickWidth, seqNum, scoreValue);
            m_game.getBoard().getSticks().push_back(newStick);
        }
        else if (key == "Score:") {
            int ScoreUpdate;
            iss >> ScoreUpdate;
            m_game.setSavedScore(ScoreUpdate);
        }
        else if (key == "Time:") {
            int TimeLimitUpdate;
            iss >> TimeLimitUpdate;
            m_game.setSavedTimeLimit(TimeLimitUpdate);

        }
        else if (key == "Picked:")
        {
            int PickedSticks;
            iss >> PickedSticks;
            m_game.setSavedPickedSticks(PickedSticks);
        }
        else if (key == "Remaning:")
        {
            int remainingSticks;
            iss >> remainingSticks;
            m_game.setSavedremainingSticks(remainingSticks);
        }
       
    
    }

    loadFile.close();
    run(); // Start game with loaded state
}


