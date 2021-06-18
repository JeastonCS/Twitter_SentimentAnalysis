#ifndef SENTIMENTANALYSIS_TEST_H
#define SENTIMENTANALYSIS_TEST_H

#include "DSString.h"
#include "Sentiment.h"

#include <fstream>
#include <map>
#include <vector>
using namespace std;

class Test {
private:
    // input files
    ifstream datafile;
    ifstream targetfile;

    // trained model
    map<DSString, Sentiment> *words {};
    map<unsigned int, int> *sentiments {};

    // accuracy measurement variables
    double percentCorrect;
    vector<int> incorrectIDs_;

    // private helper methods
    void _open_files (char*,char*);
    void _close_files ();

    void _populate_sentiments();
    int _predict_sentiment (DSString);
    bool _correct_prediction (unsigned int,int);


public:
    Test();
    Test(char*, char*, map<DSString, Sentiment> *);

    void test();
    void output_results(char*);
};


#endif //SENTIMENTANALYSIS_TEST_H
