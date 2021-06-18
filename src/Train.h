#ifndef SENTIMENTANALYSIS_TRAIN_H
#define SENTIMENTANALYSIS_TRAIN_H

#include "DSString.h"
#include "Sentiment.h"

#include <fstream>
#include <map>

using namespace std;

class Train {
private:
    // input files
    ifstream datafile;
    ifstream targetfile;

    // training model
    map<DSString, Sentiment> *words {};
    map<unsigned int, int> *sentiments {};

    // private helper methods
    void _open_files (char*,char*);
    void _close_files ();

    void _populate_sentiments ();
    void _populate_words ();
    void _add_tweet (char*);
    void _filter_words ();
    
public:
    // constructors
    Train ();
    Train (char*, char*, map<DSString, Sentiment> *);

    // public interface method
    void train ();
};


#endif //SENTIMENTANALYSIS_TRAIN_H
