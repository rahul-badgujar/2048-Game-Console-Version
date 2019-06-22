#ifndef GAME_H
#define GAME_H

/***
        This is Class Defination of Game Class.
        All the members of Game Class are static as we are not going to create multiple objects of Class Game.
        It has defined all the basic functionlity of Game.
***/

#include <fstream>      // for file handling purpose, need for High Score Features
#include <string>       // to used std::string and useful functions
#include <iomanip>      // for formating output on console screen
#include <time.h>       // for generating clock time based Random Numbers
#include "Utilities.h"  // to use basic utilty functions in our program
#include "Debugger.h"   // to handle exceptions occured
#include "Player.h"     // to implement Player

class Game
{
    public:
        Game(); // ctor
        virtual ~Game();        // dtor

        static void startGame();        // starts the game, made public so that we can call from main function

    protected:

    private:

        enum class GameState{PLAYING,QUIT};     // enumerator used to indicate state of game
        static GameState gameState;     // object of enumerator
        static bool gameOver;           // flag to indicate Game Over status
        static int panel[4][4];         // GamePlay Panel
        static Player* player;          // pointer to Player type

        static void showGameTitle();    // shows Game Title
        static void showMenu();         // shows Game Menu
        static void gamePlay();         // handles GamePlay
        static void gameLoop();         // continues GamePlay
        static void initGame();         // initialize gam basics
        static void showGamePlayPanel();        // shows the GamePlay Panel
        static char takeGameInput();            // input single character user response
        static void handleGameInput(const char&);      // handles single character input
        static void actionUp();         // perform Action UP in Gameplay
        static void actionDown();       // perform Action DOWN in Gameplay
        static void actionLeft();       // perform Action LEFT in Gameplay
        static void actionRight();      // perform Action RIGHT in Gameplay
        static void fillRandomTile();   // fills random tile after each turn
        static int getEmptyTiles();     // returns total empty tiles in gameplay panel
        static void resetGame();        // resets game for new Play
        static bool checkWin();         // checks panel, if player wins the game
        static bool checkGameOver();    // check Game Over condition in Panel
        static void uploadWinnerData(); // uploads winners data to file
        static void showHighScoreTable();       // shows High Score Table
};

#endif // GAME_H
