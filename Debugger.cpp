#include "Debugger.h"

Debugger::Debugger()
{
    //ctor
}

Debugger::~Debugger()
{
    //dtor
}

void Debugger::handleException(const char errorMessage[],const bool toExit)
{
    if(toExit) rlutil::cls();
    std::cerr<<"Unexpected Error Occured : "<<errorMessage;
    if(toExit)  // if toExit is true
    {
        Utilities::print("Terminating Program ...");
        exit(EXIT_FAILURE); // terminate program
    }
}

