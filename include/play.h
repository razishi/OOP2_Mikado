#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Controller.h"
#include <iostream>
#include "Globals.h"


class Play
{
public:
    void  CreatMenu();
   
    Play();

private:

    sf::RenderWindow m_window;
    Menu m_menu;
};
