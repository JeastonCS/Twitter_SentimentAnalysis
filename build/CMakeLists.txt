cmake_minimum_required(VERSION 3.14)
project(SentimentAnalysis)
set (EXE_NAME SentimentAnalyzer)

set( srcdir "../src/" )
set( testdir "../tests/" )
set( datadir "../data/" )

set ( input01 ${datadir}dev-train-data-sm.csv ) #dev-train-data-sm.csv dev-train-target-sm.csv
set ( input02 ${datadir}dev-train-target-sm.csv )
set ( input03 ${datadir}dev-test-data.csv ) #dev-test-data.csv dev-test-target.csv
set ( input04 ${datadir}dev-test-target.csv )

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
add_executable( ${EXE_NAME}
                ${testdir}testRunner.cpp
                ${srcdir}main.cpp
                ${srcdir}DSString.h ${srcdir}DSString.cpp
                ${srcdir}Sentiment.h ${srcdir}Sentiment.cpp
                ${srcdir}Train.h ${srcdir}Train.cpp
                ${srcdir}Test.h ${srcdir}Test.cpp
                ${srcdir}Driver.h ${srcdir}Driver.cpp )