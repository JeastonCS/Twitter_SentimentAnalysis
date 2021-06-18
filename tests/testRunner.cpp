#include "catch.hpp"
#include "../src/DSString.h"
#include "../src/Sentiment.h"

TEST_CASE("Testing... DSString class") {
    SECTION("Testing... constructors") {
        DSString string1;

        DSString string2("test");
        REQUIRE(string2.at(0) == 't');
        REQUIRE(string2.at(1) == 'e');
        REQUIRE(string2.at(2) == 's');
        REQUIRE(string2.at(3) == 't');

        DSString string3(string2);
        REQUIRE(string3.at(0) == 't');
        REQUIRE(string3.at(1) == 'e');
        REQUIRE(string3.at(2) == 's');
        REQUIRE(string3.at(3) == 't');
    }
    SECTION("Testing... operator==") {
        DSString string1("test");
        REQUIRE(string1 == "test");

        DSString string2("test");
        REQUIRE(string1 == string2);
    }
    SECTION("Testing... operator=") {
        DSString string1;

        string1 = "test";
        REQUIRE(string1 == "test");

        DSString string2 = string1;
        REQUIRE(string2 == "test");

        string1 = string2 = "TEST";
        REQUIRE(string2 == "TEST");
        REQUIRE(string1 == "TEST");
    }
    SECTION("Testing... operator+") {
        DSString string1("");
        string1 = string1 + "test";
        REQUIRE(string1 == "test");

        DSString string2("test");
        DSString string3 = string1 + string2;

        REQUIRE(string3 == "testtest");
    }
    SECTION("Testing... operator+=") {
        DSString string1;

        string1 += "test";
        REQUIRE(string1 == "test");

        DSString string2("test");
        string1 += string2;
        REQUIRE(string1 == "testtest");
    }
    SECTION("Testing... operator<") {
        DSString string1 = "test";

        DSString string2 = "TEST";
        DSString string3 = "tesT";
        DSString string4 = "uest";
        DSString string5 = "sest";
        DSString string6 = "uaaa";
        DSString string7 = "test ";

        REQUIRE(string2 < string1);
        REQUIRE(string3 < string1);
        REQUIRE(string1 < string4);
        REQUIRE(string5 < string1);
        REQUIRE(string1 < string6);
        REQUIRE(string1 < string7);
    }
    SECTION("Testing... operator>") {
        DSString string1 = "test";

        DSString string2 = "TEST";
        DSString string3 = "tesT";
        DSString string4 = "uest";
        DSString string5 = "sest";
        DSString string6 = "uaaa";
        DSString string7 = "test ";

        REQUIRE(string1 > string2);
        REQUIRE(string1 > string3);
        REQUIRE(string4 > string1);
        REQUIRE(string1 > string5);
        REQUIRE(string6 > string1);
        REQUIRE(string7 > string1);
    }
    SECTION("Testing... substring()") {
        DSString string1;
        string1 = "testJACKtest";

        string1 = string1.substring(4, 8);
        REQUIRE(string1 == "JACK");

        string1 = string1.substring(1);
        REQUIRE(string1 == "ACK");
    }
    SECTION("Testing... findChar()") {
        DSString string1 = "look for the O in this O string";

        int index = string1.findChar('O');
        REQUIRE(index == 13);

        index++;
        index = string1.findChar('O', index);
        REQUIRE(index == 23);
    }
    SECTION("Testing... toInt()") {
        DSString string1 = "12345";

        int stringInt = string1.toInt();
        REQUIRE(stringInt == 12345);
    }
    SECTION("Testing... toVector()") {
        DSString string1 = "this is a   test string ";
        DSString string2 = "    this is another test string";

        vector<DSString> vector1 = string1.toVector(' ');
        vector<DSString> vector2 = string2.toVector(' ');

        REQUIRE(vector1.size() == 5);
        REQUIRE(vector2.size() == 5);

        REQUIRE(vector1.at(0) == "this");
        REQUIRE(vector1.at(1) == "is");
        REQUIRE(vector1.at(2) == "a");
        REQUIRE(vector1.at(3) == "test");
        REQUIRE(vector1.at(4) == "string");

        REQUIRE(vector2.at(0) == "this");
        REQUIRE(vector2.at(1) == "is");
        REQUIRE(vector2.at(2) == "another");
        REQUIRE(vector2.at(3) == "test");
        REQUIRE(vector2.at(4) == "string");
    }
    SECTION("Testing... onlyAlphaLCChars()") {
        DSString string0 = "this is a test";
        DSString string1 = "this is a test.";
        DSString string2 = "THis is a test...";
        DSString string3 = "1 this is a t3est3.";

        string0.onlyAlphaLCChars();
        string1.onlyAlphaLCChars();
        string2.onlyAlphaLCChars();
        string3.onlyAlphaLCChars();

        REQUIRE(string0 == "this is a test");
        REQUIRE(string1 == "this is a test");
        REQUIRE(string2 == "this is a test");
        REQUIRE(string3 == " this is a test");
    }
    SECTION("Testing... get methods(length, value at a certain index)") {
        DSString string1 = "test";

        REQUIRE(string1.getLength() == 4);
        REQUIRE(string1.at(1) == 'e');
    }
}

TEST_CASE("Testing... Sentiment class") {
    SECTION("Testing... constructors") {
        Sentiment sent1;

        Sentiment sent2(0);
        Sentiment sent3(4);
        Sentiment sent4(-1);

        Sentiment sent5(14, 2);
        Sentiment sent6(2, 97);

        //no parameter
        REQUIRE(sent1.getNegCount() == 0);
        REQUIRE(sent1.getPosCount() == 0);
        REQUIRE(sent1.getPosChiSquared() == 0);
        REQUIRE(sent1.getNegChiSquared() == 0);
        REQUIRE(sent1.getSentiment() == -1);

        //one parameter
        REQUIRE(sent2.getNegCount() == 1);
        REQUIRE(sent2.getPosCount() == 0);
        REQUIRE(sent2.getPosChiSquared() == 0);
        REQUIRE(sent2.getNegChiSquared() == 0);
        REQUIRE(sent2.getSentiment() == -1);

        REQUIRE(sent3.getNegCount() == 0);
        REQUIRE(sent3.getPosCount() == 1);

        REQUIRE(sent4.getNegCount() == 0);
        REQUIRE(sent4.getPosCount() == 0);

        //two parameter
        REQUIRE(sent5.getNegCount() == 14);
        REQUIRE(sent5.getPosCount() == 2);
        REQUIRE(sent5.getPosChiSquared() == 0);
        REQUIRE(sent5.getNegChiSquared() == 0);
        REQUIRE(sent5.getSentiment() == -1);

        REQUIRE(sent6.getNegCount() == 2);
        REQUIRE(sent6.getPosCount() == 97);
    }
    SECTION("Testing... determineNeutrality()") {
        Sentiment sent1(2, 2);
        Sentiment sent2(0,1);
        Sentiment sent3(1, 0);
        Sentiment sent4(3, 90);
        Sentiment sent5(15, 6);
        Sentiment sent6(0, 4);

        REQUIRE(sent1.determineNeutrality() == true);
        REQUIRE(sent2.determineNeutrality() == true);
        REQUIRE(sent3.determineNeutrality() == true);
        REQUIRE(sent4.determineNeutrality() == false);
        REQUIRE(sent5.determineNeutrality() == false);
        REQUIRE(sent6.determineNeutrality() == false);
    }
    SECTION("Testing... calcSentiment()") {
        Sentiment sent1(3, 90);
        Sentiment sent2(15, 6);
        Sentiment sent3(50, 200);
        Sentiment sent4(4, 0);
        sent1.determineNeutrality();
        sent2.determineNeutrality();
        sent3.determineNeutrality();
        sent4.determineNeutrality();
        sent1.calcSentiment();
        sent2.calcSentiment();
        sent3.calcSentiment();
        sent4.calcSentiment();

        REQUIRE( (sent1.getSentiment() > -1 && sent1.getSentiment() < 1) );
        REQUIRE( (sent2.getSentiment() > -1 && sent2.getSentiment() < 1) );
        REQUIRE( (sent3.getSentiment() > -1 && sent3.getSentiment() < 1) );
        REQUIRE( (sent4.getSentiment() > -1 && sent4.getSentiment() < 1) );
    }
}