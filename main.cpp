#include <iostream>
#include "src/common.h"

using namespace computerClub;

int main(int argc, char* argv[]){
    if(argc < 2) {
        std::cerr << "Incorrect number of arguments provided.\n";
        return 1;
    }
    std::string filename = argv[1];
    
}