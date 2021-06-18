#ifndef DRIVER_H
#define DRIVER_H

#include "DSString.h"
#include "Sentiment.h"
#include "Train.h"
#include "Test.h"

#include <map>
using namespace std;

class Driver
{
private:
    map<DSString,Sentiment> words;

public:
    Driver();

    // public interface method
    void run (char*,char*,char*,char*);
};

#endif //DRIVER_H
