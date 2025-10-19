#include "Play.h"
//------------------------------------
// Constructor
Play::Play() : m_window(sf::VideoMode(1300, 800), "Pick Up Sticks Game", sf::Style::Close | sf::Style::Titlebar),
m_menu(m_window.getSize().x, m_window.getSize().y)
{
    CreatMenu();
}

//------------------------------------

    void Play::CreatMenu() {
        sf::RectangleShape Pbackground;
        Pbackground.setSize(sf::Vector2f(1300, 800));
        sf::Texture back_texture;
        back_texture.loadFromFile("background.png");
        Pbackground.setTexture(&back_texture);

        while (m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    m_window.close();

                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    int selectedMenu = m_menu.MenuPressed();
                    if (selectedMenu != -1) {
                        switch (selectedMenu) {
                        case 0: {  // Play
                            m_window.close();  // Close menu window
                            Controller newGameController(windowWidth, windowHeight, numSticks, stickWidth , timeLimit);
                            newGameController.run();
                            break;
                        }
                        case 1: {  // Load Game
                            m_window.close();  // Close menu window
                            Controller loadedGameController(windowWidth, windowHeight, numSticks, stickWidth, timeLimit);
                            loadedGameController.loadGame("game_save.txt");  
                            break;
                        }
                        case 2:  // Exit
                            m_window.close();
                            break;
                        }

                    }
                }
            }

        // Update mouse position for menu highlight
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
        m_menu.update(mousePos);
        // Draw menu and background
        m_window.clear();
        m_window.draw(Pbackground);
        m_menu.draw(m_window);
        m_window.display();
    }
}




