#ifndef PLAYER_H
#define PLAYER_H

/***
    This is Player Class, it handles all the activities corresponding to Player
***/

#include <cstring>  // for using string functions


class Player
{
    public:
        Player();   // ctor
        virtual ~Player();  // dtor
        unsigned long int getPlayerScore(); // getter for Player Score
        void setPlayerScore(const unsigned long int&); // setter for Player Score
        void addToPlayerScore(const unsigned long int& );  // add to Score
        char* getPlayerName();  // getter for Player Name
        void setPlayerName(const char*);  // setter for Player Name

    protected:

    private:
        char playerName[30];    // character array Player Name, max size of name allowed is 29
        unsigned long int playerScore;  // player score
};

#endif // PLAYER_H
