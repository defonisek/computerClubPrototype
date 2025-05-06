#include "clubDriver.h"
#include <fstream>
#include <iostream>
#include "processing/clientHandler.h"
#include "parser/parser.h"

using namespace computerClub;

ClubDriver::ClubDriver(){ 
    clientHandler = new ClientHandler();
    parser = new Parser();
    club = {0, 0, {}, {}, {}, "", "", 0, ""};
}

ClubDriver::~ClubDriver(){
    delete clientHandler;
    delete parser;
}

void ClubDriver::process(std::string &filename){
    
}


