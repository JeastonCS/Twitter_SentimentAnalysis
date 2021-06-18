#include "DSString.h"

#include <cctype>
#include <cmath>
#include <cstring>
#include <vector>

//-------------------- constructors/destructor --------------------//
DSString::DSString() {
    data_ = new char[1];
    data_[0] = '\0';
}
DSString::DSString(const char *startingData) {
    data_ = new char[strlen(startingData) + 1];
    strcpy(data_, startingData);
}
DSString::DSString(const DSString &startingString) {
    data_ = new char[strlen(startingString.data_) + 1];
    strcpy(data_, startingString.data_);
}
DSString::~DSString() {
    delete [] data_;
}

//-------------------- overloaded operators with char* --------------------//
bool DSString::operator==(const char *rhs) const {
    return strcmp(this->data_, rhs) == 0;
}
DSString &DSString::operator=(const char *rhs) {
    delete [] data_;
    data_ = nullptr;

    const int length = strlen(rhs);

    data_ = new char[length + 1];
    strcpy(data_, rhs);
    data_[length] = '\0';

    return *this;
}
DSString DSString::operator+(const char *rhs) {
    char *temp = new char[strlen(this->data_) + strlen(rhs) + 1];

    strcpy(temp, this->data_);
    strcat(temp, rhs);

    DSString sumString;
    sumString = temp;
    delete [] temp;

    return sumString;
}
void DSString::operator+=(const char *rhs) {
    *this = *this + rhs;
}
void DSString::operator+=(char c) {
    int length = strlen(data_);

    char *temp = new char[length + 2]; //1 for null terminator, 1 for new char
    strcpy(temp, data_);
    temp[length] = c;
    temp[length + 1] = '\0';

    delete [] data_;
    data_ = temp;
}

//-------------------- overloaded operators with DSString --------------------//
bool DSString::operator==(const DSString &rhs) const {
    return *this == rhs.data_;
}
DSString &DSString::operator=(const DSString &rhs) {
    *this = rhs.data_;
    return *this;
}
DSString DSString::operator+(const DSString &rhs) {
    return *this + rhs.data_;
}
void DSString::operator+=(const DSString &rhs) {
    *this = *this + rhs;
}
bool DSString::operator<(const DSString &rhs) const {
    return strcmp(data_, rhs.data_) < 0;
}
bool DSString::operator>(const DSString &rhs) const {
    return strcmp(data_, rhs.data_) > 0;
}
ostream &operator<<(ostream &os, const DSString &dsString) {
    os << dsString.data_;
    return os;
}

//-------------------- Misc Methods --------------------//
DSString& DSString::substring(int startIndex) {
    return substring(startIndex, strlen(data_));
}

DSString& DSString::substring(int startIndex, int endIndex) {
    int length = endIndex - startIndex;
    char* temp = new char[length + 1];

    for(int i = 0; i < length; i++)
        temp[i] = data_[i + startIndex];
    temp[length] = '\0';

    DSString *sub = new DSString(temp);
    delete [] temp;
    return *sub;
}
int DSString::findChar(char character, int startIndex) {
    int len = strlen(data_);
    for(int i = startIndex; i < len; i++) {
        if(data_[i] == character)
            return i;
    }
    return -1;
}
vector<DSString> DSString::toVector(char delimeter) {
    vector<DSString> words;
    int length = strlen(data_);

    DSString temp = "";

    bool onDelim = true;
    for (int i = 0; i < length; i++) {
        if(data_[i] == delimeter) {
            if(onDelim == false) {
                words.push_back(temp);
                temp = "";
            }
            onDelim = true;
        }
        else {
            temp += data_[i];
            onDelim = false;
        }
    }
    if( !(temp == "") ) {
        temp += '\0';
        words.push_back(temp);
    }

    return words;
}
void DSString::onlyAlphaLCChars() {
    int length = strlen(data_);

    char *temp = new char[length + 1];
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (isalpha(data_[i]) || data_[i] == ' ') {
            if (isupper(data_[i]))
                temp[j] = tolower(data_[i]);
            else
                temp[j] = data_[i];
            j++;
        }
    }
    temp[j] = '\0';

    delete [] data_;
    data_ = temp;
}

char DSString::at(int index) {
    if (index < strlen(data_))
        return data_[index];
    else {
        cout << "invalid index" << endl;
        return 0;
    }
}
