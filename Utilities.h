#ifndef UTILITIES_H
#define UTILITIES_H

#include "rlutil.h"
#include "Debugger.h"


class Utilities
{
    public:
        Utilities();
        virtual ~Utilities();

        // function print to print the message to console with other attributes
        static void print(const std::string &info,const bool lineEnd=true,const int color=Utilities::defaultTextColor,const int delay=Utilities::defaultDelay);
        static const int defaultDelay=30;       // default delay of printing
        static const int defaultTextColor=rlutil::COLORS::WHITE;   // default text color, WHITE
        static int getRandomNumber(const int leftLimit,const int rightLimit);   // function to get a random number within range

    protected:

    private:
};

#endif // UTILITIES_H
