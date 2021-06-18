#include "Driver.h"

Driver::Driver () = default;

void
Driver::run(char *train_data, char *train_target, char *test_data, char *test_target)
{
    // create sentiment map with training data
    Train train(train_data, train_target, &words);
    train.train();

    // calculate sentiment of testing data
    Test test(test_data, test_target, &words);
    test.test();
    // test.output_results("../results.txt");

    // output results
    test.output_results("../results.txt");

    ofstream word_output("../wordmap.txt");
    for(auto it = words.begin(); it != words.end(); ++it)
        word_output << (*it).first << ":\t\t" << (*it).second.getSentiment() << endl;
    word_output.close();
}