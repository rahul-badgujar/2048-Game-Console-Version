#include "Utilities.h"

Utilities::Utilities()
{
    //ctor
}

Utilities::~Utilities()
{
    //dtor
}

void Utilities::print(const std::string &info,const bool lineEnd,const int color,const int delay)
{
    // Printing using these function gives a nice effect
    rlutil::setColor(color);    // set color of text
	for(unsigned int i=0;i<info.size();i++)
	{
		rlutil::msleep(delay);  // wait for next character to be printed
		std::cout<<info[i];     // display the character
	}
	rlutil::msleep(delay*5);    // delay x5 time after line printed
	if(lineEnd)  std::cout<<std::endl;  // if lineEnd is true, move to next line
	rlutil::setColor(Utilities::defaultTextColor);  // reset the default color of text
}
int Utilities::getRandomNumber(const int leftLimit,const int rightLimit)
{
    return (rand()%(rightLimit-leftLimit+1)+leftLimit); // return random integer within range
}


