//
// Created by Jack Easton on 1/31/2020.
//

#ifndef SENTIMENTANALYSIS_SENTIMENT_H
#define SENTIMENTANALYSIS_SENTIMENT_H


class Sentiment {
private:
    int negCount_;
    int posCount_;
    double posChiSquared_;
    double negChiSquared_;
    double sentiment_;
public:
    //Constructors
    Sentiment();
    Sentiment(int); //0 or 4 to increment pos- or negCount;
    Sentiment(int, int); //values for negCount and/or posCount;

    bool determineNeutrality();
    void calcSentiment();
    void print();

    void incrementNegCount(){ negCount_++; }
    void incrementPosCount(){ posCount_++; }

    //getters
    double getSentiment() { return sentiment_; }
    int getNegCount() { return negCount_; }
    int getPosCount() { return posCount_; }
    int getPosChiSquared() { return posChiSquared_; }
    int getNegChiSquared() { return negChiSquared_; }
};


#endif //SENTIMENTANALYSIS_SENTIMENT_H
