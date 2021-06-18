#include "Test.h"
#include "DSString.h"
#include "Sentiment.h"

#include <map>
#include <fstream>
#include <iomanip>
using namespace std;

Test::Test() = default;

Test::Test(char *data, char *target, map<DSString, Sentiment> *words)
{
    percentCorrect = 0;

    this->words = words;
    sentiments = new map<unsigned int, int>;

    _open_files(data, target);
}

void
Test::_open_files (char *data, char *target)
{
    datafile.open(data);
    targetfile.open(target);
    if ( !datafile || !targetfile ) {
        cout << "Could not open testing files." << endl;
        exit(1);
    }

    // clear the heading from each file
    datafile.ignore(2048, '\n');
    targetfile.ignore(24,'\n');
}

void
Test::_close_files ()
{
    datafile.close();
    targetfile.close();
}

void
Test::test()
{
    // get data from target file
    _populate_sentiments();

    // tweet variables
    unsigned int ID;
    DSString text;

    // temporary variables
    char buffer[2048];
    DSString fileLine;

    int startIndex, endIndex;
    int prediction;

    int num_correct = 0, num_tweets = 0;

    // process testing tweets
    datafile.getline(buffer, 2048);
    while ( !datafile.eof() ) {
        fileLine = buffer;

        // get tweet ID
        startIndex = fileLine.findChar(',') + 1;
        endIndex = fileLine.findChar(',', startIndex);
        ID = fileLine.substring(startIndex, endIndex ).toInt();

        // get tweet text
        startIndex = fileLine.findChar(',', endIndex+1) + 1;
        text = fileLine.substring(startIndex);
        text.onlyAlphaLCChars();

        // make prediction and check it
        prediction = _predict_sentiment(text);
        if ( _correct_prediction(ID, prediction) ) {
            num_correct++;
        }
        else {
            incorrectIDs_.push_back(ID);
        }

        num_tweets++;
        datafile.getline(buffer, 2048);
    }

    _close_files();

    // initialize accuracy rating
    percentCorrect = static_cast<double>(num_correct) / num_tweets;
}

void
Test::_populate_sentiments ()
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

int
Test::_predict_sentiment (DSString tweet)
{
    // get separate words from current line
    vector<DSString> tweetWords = tweet.toVector(' ');

    double line_sum = 0;

    // loop over each word in current tweet
    auto it = words->begin();
    for(const DSString &word : tweetWords) {
        // add this word's sentiment to sum
        it = words->find(word);
        if ( it != words->end() ) {
            line_sum += it->second.getSentiment();
        }
    }

    // determine final sentiment classification
    // sum = [0,1] --> positive
    // sum = [-1,0) --> negative
    if(line_sum < 0)
        return 0;
    else
        return 4;
}

bool
Test::_correct_prediction (unsigned int ID, int prediction)
{
    // find the correct sentiment
    auto it = sentiments->find(ID);
    int actual_sentiment = (*it).second;

    // compare correct sentiment to prediction
    return actual_sentiment == prediction;
}

void
Test::output_results (char *outfile_name)
{
    ofstream resultfile(outfile_name);

    // output the accuracy of this test
    resultfile << fixed << setprecision(3) << percentCorrect << endl;

    // output the IDs of the incorrectly identified tweets
    for(int id : incorrectIDs_) {
        resultfile << id << endl;
    }

    resultfile.close();

    // print accuracy to console
    cout << percentCorrect << endl;
}
