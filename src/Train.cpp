
#include "Train.h"

Train::Train() = default;

Train::Train(char *data_name, char *targets_name, map<DSString, Sentiment> *words)
{
    this->words = words;
    this->sentiments = new map<unsigned int, int>;

    _open_files(data_name,targets_name);
}

void
Train::_open_files (char *data_name, char *targets_name)
{
    datafile.open(data_name);
    targetfile.open(targets_name);
    if ( !datafile || !targetfile ) {
        cout << "Count not open training files." << endl;
        exit(1);
    }

    // clear the heading from each file
    datafile.ignore(2048, '\n');
    targetfile.ignore(24,'\n');
}

void
Train::_close_files ()
{
    datafile.close();
    targetfile.close();
}

void
Train::train()
{
    // get data from target file
    _populate_sentiments();

    // get data from tweet data file
    _populate_words();

    // remove neutral words and calculate final sentiment values
    _filter_words();
    
    _close_files();
}

void
Train::_populate_sentiments ()
{
    char buffer[24];

    targetfile.getline(buffer, 24);
    while (!targetfile.eof()) {
        // split line into components
        DSString line = buffer;
        auto target_info = line.toVector(',');

        // gather line data
        unsigned int ID = target_info[2].toInt();
        int sentiment = target_info[1].toInt();

        // put data in map
        sentiments->emplace(ID, sentiment);

        targetfile.getline(buffer, 24);
    }
}

void
Train::_populate_words ()
{
    char buffer[2048];

    datafile.getline(buffer, 2048);
    while (!datafile.eof()) {
        _add_tweet(buffer);

        datafile.getline(buffer, 2048);
    }
}

void
Train::_add_tweet ( char *buffer )
{
    /*--------------- get tweet data ---------------*/
    //tweet variables
    unsigned int ID;
    int sentiment;
    DSString  text;

    // temp variables
    int startIndex, endIndex;
    DSString fileLine = buffer;

    // get tweet ID
    startIndex = fileLine.findChar(',') + 1;
    endIndex = fileLine.findChar(',', startIndex);
    ID = fileLine.substring(startIndex, endIndex ).toInt();

    // get tweet text
    startIndex = fileLine.findChar(',', endIndex+1) + 1;
    text = fileLine.substring(startIndex);
    text.onlyAlphaLCChars();

    // get sentiment (based on tweet ID)
    auto iter = sentiments->find(ID);
    sentiment = (*iter).second;

    /*--------- add tweet data to words map --------*/
    vector<DSString> tweetWords = text.toVector(' ');
    for(int i = 0; i < tweetWords.size(); i++) {

        DSString *word = new DSString(tweetWords.at(i));
        if (word->getLength() > 2) { //get rid of "a", "an", "to", etc.
            auto it = words->find(*word);
            
            // if new word, add to map
            if (it == words->end()){
                Sentiment *sentimentObj = new Sentiment(sentiment);
                words->emplace(*word, *sentimentObj);
            }
            // already in map- increment pos/neg count for that word
            else{
                if (sentiment == 0)
                    words->at(*word).incrementNegCount();
                else
                    words->at(*word).incrementPosCount();
            }
        }
    }
}

void
Train::_filter_words ()
{
    for (auto it = words->begin(); it != words->end();) {
        // remove neutral words
        if (it->second.determineNeutrality()) {
            it = words->erase(it);
        }
        // calculate final sentiment value
        else {
            it->second.calcSentiment();
            ++it;
        }
    }
}
