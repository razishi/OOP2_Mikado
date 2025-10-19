#include "Stick.h"

// Constructor
Stick::Stick(sf::Vector2f point1, sf::Vector2f point2, sf::Color color, float width, int seqNum, int score)
    : startPoint(point1), endPoint(point2), m_canBePicked(true), m_sequenceNumber(seqNum), m_scoreValue(score) {
    initializeShape(point1, point2, width, color);
}

//--------------------------------------------------------------
// Initializes the stick shape with specified points, width, and color, setting size,
//  origin, position, rotation, and fill color, and stores the original color.

void Stick::initializeShape(sf::Vector2f point1, sf::Vector2f point2, float width, sf::Color color) {
    sf::Vector2f direction = point2 - point1;
    float length = calculateLength(direction);
    shape.setSize(sf::Vector2f(length, width));
    shape.setOrigin(0, width / 2);
    shape.setPosition(point1);
    shape.setRotation(calculateRotation(direction));
    shape.setFillColor(color);
    m_originalColor = shape.getFillColor(); // Store the original color
}
//--------------------------------------------------------------

float Stick::calculateLength(sf::Vector2f direction) {
    return sqrt(pow(direction.x, 2) + pow(direction.y, 2));
}
//--------------------------------------------------------------

float Stick::calculateRotation(sf::Vector2f direction) {
    return atan2(direction.y, direction.x) * 180 / M_PI;
}

//--------------------------------------------------------------
// Determines if two sticks intersect by calculating orientations and checking segment intersections.
bool Stick::doIntersect(Stick a, Stick b) {
    sf::Vector2f p1 = a.startPoint;
    sf::Vector2f q1 = a.endPoint;
    sf::Vector2f p2 = b.startPoint;
    sf::Vector2f q2 = b.endPoint;

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

//--------------------------------------------------------------
void Stick::flicker() {
    shape.setFillColor(sf::Color::Yellow);
    shape.setFillColor(m_originalColor);
}

//--------------------------------------------------------------
// Checks if point q lies on segment pr.

bool Stick::onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r) {
    return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
}

//--------------------------------------------------------------
// Determines the orientation of three points (p, q, r) by calculating their cross product.
int Stick::orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r) {
    float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

//--------------------------------------------------------------
// Initiates flickering for the stick by setting flickering state, storing original color, recording
//  start time, and setting fill color to yellow.
void Stick::startFlickering() {
    m_isFlickering = true;
    m_originalColor = shape.getFillColor();
    m_flickerStartTime = std::chrono::steady_clock::now();
    shape.setFillColor(sf::Color::Yellow);
}

//--------------------------------------------------------------
// Update the flickering state of the stick, toggling its 
// color based on elapsed time and flicker frequency.
void Stick::updateFlickering() {
    if (!m_isFlickering) return;

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_flickerStartTime).count();

    if (elapsed > m_flickerDuration) {
        m_isFlickering = false;
        shape.setFillColor(m_originalColor);
        return;
    }

    int phase = (elapsed / m_flickerFrequency) % 2;
    shape.setFillColor(phase == 0 ? sf::Color::Yellow : m_originalColor);
}

//--------------------------------------------------------------
// Check if a given point lies on the stick by transforming the point to the stick's local coordinate
//  system and verifying it lies within the stick's bounds.
bool Stick::isPointOnStick(sf::Vector2f point) {
    sf::Transform transform;
    transform.rotate(-shape.getRotation(), startPoint);
    sf::Vector2f localPoint = transform.transformPoint(point);

    float dx = endPoint.x - startPoint.x;
    float dy = endPoint.y - startPoint.y;
    float length = sqrt(dx * dx + dy * dy);

    return localPoint.x >= startPoint.x && localPoint.x <= startPoint.x + length &&
        localPoint.y >= startPoint.y - (shape.getSize().y / 2) && localPoint.y <= startPoint.y + (shape.getSize().y / 2);
}

//--------------------------------------------------------------
void Stick::draw(sf::RenderWindow& window) {
    updateFlickering();
    window.draw(shape);
}

//--------------------------------------------------------------
// Schedules flickering for the stick with a specified delay by launching a detached thread that sleeps 
// for the delay duration before initiating flickering.
void Stick::scheduleFlickering(unsigned delay) {
    std::thread([this, delay]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        startFlickering();
        }).detach();
}
