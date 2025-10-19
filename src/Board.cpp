#include "Board.h"

Board::Board(int numSticks , float stickWidth) {

    Build(numSticks,  stickWidth);
  
}


//--------------------------------------------------------------
void Board::Build(int numSticks, float stickWidth) {
    srand(static_cast<unsigned>(time(0)));
    static int sequenceNumber = 0;  // Initialize sequence number

    // Window dimensions
    float windowWidth = 800.0f;
    float windowHeight = 600.0f;

    // Margin from the window edges
    float margin = 30.0f;

    // Clock area dimensions
    float clockAreaWidth = 150.0f;  // Adjust based on actual clock sprite width
    float clockAreaHeight = 100.0f; // Adjust based on actual clock sprite height

    // Calculate the available space for sticks (excluding clock area and margin)
    float availableWidth = windowWidth - 2 * margin - clockAreaWidth;
    float availableHeight = windowHeight - 2 * margin - clockAreaHeight;

    for (int i = 0; i < numSticks; ++i) {
        sf::Vector2f point1, point2;
        do {
            // Generate random positions within the available space
            float x1 = margin + clockAreaWidth + static_cast<float>(rand()) / RAND_MAX * availableWidth;
            float y1 = margin + clockAreaHeight + static_cast<float>(rand()) / RAND_MAX * availableHeight;
            float x2 = margin + clockAreaWidth + static_cast<float>(rand()) / RAND_MAX * availableWidth;
            float y2 = margin + clockAreaHeight + static_cast<float>(rand()) / RAND_MAX * availableHeight;

            point1 = sf::Vector2f(x1, y1);
            point2 = sf::Vector2f(x2, y2);
        } while (
            (point1.x < clockAreaWidth || point1.y < clockAreaHeight) ||
            (point2.x < clockAreaWidth || point2.y < clockAreaHeight) ||
            (point2.x > windowWidth - margin || point2.x < margin) ||
            (point2.y > windowHeight - margin || point2.y < margin)
            );
        sf::Color  color;
            int score;
        switch (sequenceNumber % 5)  // calculate the score
        {
        case 0:
              color = sf::Color::Red;
            score = 10;
            break;
        case 1:
            color = sf::Color::Green;
             score = 20;
            break;
        case 2:
              color = sf::Color::Blue;
              score = 15;
            break;
        case 3:
              color = sf::Color::Cyan;
              score = 5;
            break;
        case 4:
              color = sf::Color::Magenta;
            score = 25;
            break;
        default:
            break;
        }
        m_sticks.emplace_back(point1, point2, color, stickWidth, sequenceNumber++, score);
    }

}

//--------------------------------------------------------------

std::vector<Stick>& Board::getSticks() {
    return m_sticks;
}

//--------------------------------------------------------------

void Board::draw(sf::RenderWindow& window) {
    for (auto& stick : m_sticks) {
        
            stick.draw(window);
        
    }
}

//--------------------------------------------------------------
//This function iterates through the m_sticks collection and returns a pointer to the first stick that
//can be picked,  or nullptr if no such stick is found.
Stick* Board::getPickableStick() {
    for (auto& stick : m_sticks) {
        if (stick.getCanBePicked()) {
            return &stick;
        }
    }
    return nullptr; // No pickable stick found
}

//--------------------------------------------------------------
//This function iterates through each stick in m_sticks, checks if it intersects with any other stick with a
//  higher sequence number, and if not, adds it to the pickableSticks vector, which is then returned.
std::vector<Stick*> Board::getPickableSticks() {
    std::vector<Stick*> pickableSticks;
    for (int i = 0; i < m_sticks.size(); ++i) {
        bool isPickable = true;  // Assume stick is pickable until proven otherwise
        int currentSeqNum = m_sticks[i].getSequenceNumber();

        for (const auto& otherStick : m_sticks) {
            if (m_sticks[i].getSequenceNumber() != otherStick.getSequenceNumber() &&
                Stick::doIntersect(m_sticks[i], otherStick) &&
                otherStick.getSequenceNumber() > currentSeqNum) {
                isPickable = false;
                break;  // No need to check further if one intersection disqualifies the stick
            }
        }

        if (isPickable) {

            pickableSticks.push_back(&m_sticks[i]);
        }
    }
    return pickableSticks;
}

//--------------------------------------------------------------

void Board::ClearSticks() {
    m_sticks.clear();
}


