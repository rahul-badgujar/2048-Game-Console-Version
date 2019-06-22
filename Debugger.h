#ifndef DEBUGGER_H
#define DEBUGGER_H
#include <iostream>
#include <string>
#include "Utilities.h"

class Debugger
{
    public:
        Debugger();
        virtual ~Debugger();

        static void handleException(const char message[], const bool toExit=false);  // print exception in program

    protected:

    private:
};

#endif // DEBUGGER_H
