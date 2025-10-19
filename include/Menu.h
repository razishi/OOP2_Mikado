#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Menu
{
public:
    Menu(float width, float height);
    ~Menu();
    void draw(sf::RenderWindow& window) const;
    void update(sf::Vector2f mousePos);
    int MenuPressed() const;

private:
    int m_MenuSelected;
    sf::Font m_font;
    sf::Text m_menu[MAXMAINMENU];
};

