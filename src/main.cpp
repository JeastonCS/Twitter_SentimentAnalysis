#define CATCH_CONFIG_RUNNER
#include "../tests/catch.hpp"

#include "Driver.h"

int main(int argc, char** argv) {
    /*----- run tests -----*/
    if(argc == 1) {
        return Catch::Session().run();
    }
    
    /*----- run sentiment analysis -----*/
    Driver d;
    d.run( argv[1], argv[2], argv[3], argv[4] );

    

    return 0;
}
