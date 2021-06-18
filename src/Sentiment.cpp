//
// Created by Jack Easton on 1/31/2020.
//

#include "Sentiment.h"

#include <cmath>
#include <iostream>
using namespace std;

//Constructors
Sentiment::Sentiment() {
    negCount_ = 0;
    posCount_ = 0;
    posChiSquared_ = 0;
    negChiSquared_ = 0;
    sentiment_ = -1;
}
Sentiment::Sentiment(int value) {
    if (value == 0) {
        negCount_ = 1;
        posCount_ = 0;
    }
    else if (value == 4){
        posCount_ = 1;
        negCount_ = 0;
    }
    else {
        posCount_ = 0;
        negCount_ = 0;
    }

    posChiSquared_ = 0;
    negChiSquared_ = 0;
    sentiment_ = -1;
}
Sentiment::Sentiment(int neg, int pos) {
    negCount_ = neg;
    posCount_ = pos;

    posChiSquared_ = 0;
    negChiSquared_ = 0;
    sentiment_ = -1;
}

//method body
/* using chi squared distribution, and considering the fact that this data set only has one degree of freedom, a value of less than 3.84 is likely to be neutral*/
bool Sentiment::determineNeutrality() {
    double expectedValue = (negCount_ + posCount_) / 2.0;

    negChiSquared_ = pow(negCount_ - expectedValue, 2) / expectedValue;
    posChiSquared_ = pow(posCount_ - expectedValue, 2) / expectedValue;
    double chiSquared = negChiSquared_ + posChiSquared_;

    return chiSquared < 3.84; //true if neutral word
}

void Sentiment::calcSentiment() {
    if (posCount_ > negCount_)
        sentiment_ =  1 - (1 / posChiSquared_);
    else
        sentiment_ = -1 + (1 / negChiSquared_);
}

void Sentiment::print() {
    cout << "(" << "negative: " << negCount_ << ", positive: " << posCount_ << ")" << endl;
}
