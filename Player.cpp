#include "Player.h"

Player::Player()
{
    //ctor
    strcpy(playerName,"NA");
    playerScore=0;
}

Player::~Player()
{
    //dtor
}

unsigned long int Player::getPlayerScore()
{
    return playerScore;
}
void Player::setPlayerScore(const unsigned long int& score)
{
    playerScore=score;
}
void Player::addToPlayerScore(const unsigned long int& addScore)
{
    playerScore+=addScore;
}
char* Player::getPlayerName()
{
    return playerName;
}
void Player::setPlayerName(const char* name)
{
    strcpy(playerName,name);
}
