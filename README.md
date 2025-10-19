In this exercise, we will build a simple pick-up sticks game using SFML. 
The player is presented with a board on which colored sticks are scattered, 
and they must pick them up one by one. A stick can only be picked up if there are 
no other sticks on top of it. If the player tries to pick up a stick that cannot be 
picked up, the action will not be performed. The game ends when the board is cleared 
or when time runs out. Each stick rewards the player with a different number of points.


**************Files**************

1-Board.h :
it includes the class and the functions of the class Board

2-Controller.h:
it includes the class and the functions of the class Controller


3-Game.h:
it includes the class and the functions of the class Game

4-Menu.cpp:
it includes the class and the functions of the class Menu

5-play.h:
it includes the class and the functions of the class play

6-Stick.h:
it includes the class and the functions of the class Stick

7-Texture.h:
it includes the class and the functions of the class Texture

8-Board.cpp:
The Board class manages a collection of sticks, initializes their positions and 
attributes, and provides methods to draw them and determine which sticks are pickable.

9-Controller.cpp:
The Controller class initializes the game window and game state, handles user input, 
updates and renders the game, and provides functionality to load a saved game state from a file.

10-Game.cpp:
The Game class manages the core game logic, including updating game states, drawing game 
elements, handling user interactions (such as mouse clicks), and providing functions to save the
 game state to a file.

11-main.cpp:
The main function creates an instance of the Play class.

12-Menu.cpp:
The Menu class creates a graphical menu with selectable items for a game, 
handles user interactions to update the menu state, and draws the menu on the window.

13-Play.cpp:
The Play class initializes and displays the main menu for the game "Pick Up Sticks"
 and handles user interactions to either start a new game, load a saved game, or exit the
 application.

14-stick.cpp:
The Stick class represents a drawable stick with functionality for color flickering,
 collision detection, and point containment, using the SFML library for graphical rendering.

15-Texture.cpp:
The Texture class manages graphical textures and text elements for a game interface, 
handling loading, initialization, and updating of sprites and text, as well as providing 
methods for detecting clicks on specific icons.

**************Technicalities and data structure**************
- STL 
-SFML
- Vectors

**************Algorithms**************
Segment Intersection Check

**************Design**************
Menu - This class creates a menu that has 3 options to choose from: play, help, or exit.
Board - Build stick.

**************Bugs**************
NONE
