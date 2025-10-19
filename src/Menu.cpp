#include "Menu.h"
#include <iostream>

// Menu constructor initializes menu items with specified font, size, and positions.
Menu::Menu(float width, float height)
{
    if (!m_font.loadFromFile("C:/Windows/Fonts/BRUSHSCI.ttf")) {
        std::cout << "No font is here" << std::endl;
    }

    for (int i = 0; i < MAXMAINMENU; ++i)
    {
        m_menu[i].setFont(m_font);
        m_menu[i].setFillColor(sf::Color::White);
        m_menu[i].setCharacterSize(70);

        switch (i)
        {
        case 0:
            m_menu[i].setString("Play");
            m_menu[i].setPosition(575, 150);
            break;
        case 1:
            m_menu[i].setString("Load");
            m_menu[i].setPosition(575, 300);
            break;
        case 2:
            m_menu[i].setString("EXIT");
            m_menu[i].setPosition(575, 450);
            break;
        }
    }
    m_MenuSelected = -1;
}

//--------------------------------------------------------------
Menu::~Menu()
{
    // Destructor
}

//--------------------------------------------------------------

void Menu::draw(sf::RenderWindow& window) const
{
    for (size_t i = 0; i < MAXMAINMENU; ++i)
    {
        window.draw(m_menu[i]);
    }
}

//--------------------------------------------------------------
// Updates menu items based on mouse position, highlighting the item if hovered over.
void Menu::update(sf::Vector2f mousePos)
{
    bool itemSelected = false;
    for (int i = 0; i < MAXMAINMENU; ++i)
    {
        if (m_menu[i].getGlobalBounds().contains(mousePos))
        {
            m_menu[i].setFillColor(sf::Color::Blue);
            m_MenuSelected = i;
            itemSelected = true;
        }
        else
        {
            m_menu[i].setFillColor(sf::Color::White);
        }
    }
    if (!itemSelected)
    {
        m_MenuSelected = -1;
    }
}

//--------------------------------------------------------------

int Menu::MenuPressed() const
{
    return m_MenuSelected;
}

