
#include "Game.h"   // to include Game Class

/****
    This is main.cpp file which is entry point of our program.
    It just calls the static function of class Game to start the Game.
    As all members of Class Games are static so we dont need to create object to Run Game.

    About rlutil.h header file
    - This programs uses external header file rlutil which allow us to perform various useful tasks,
      like Coloring the Text, Moving Cursor anywhere in console screen, Time Delay etc.
    - All the functions used in Code following rlutil namespace e.g, rlutil::changeColor(), belongs to rlutil header file.
    - Please refer to rlutil header file before reading the further Code for better understanding of Code.
***/

int main()
{
    Game::startGame();  // start the game
    return EXIT_SUCCESS;  // return 0 to OS which indicates succesfull execution of program
}
