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
    std::ifstream file(filename);
    std::string line;
    try{
        if(!std::getline(file, line))
            throw std::invalid_argument("");
        club.tableAmount = parser->numLine(line);
        if(!std::getline(file, line))
            throw std::invalid_argument("");
        std::pair<std::string, std::string> openCloseT = parser->openCloseTime(line);
        club.openingTime = openCloseT.first;
        club.closingTime = openCloseT.second;
        if(!std::getline(file, line))
            throw std::invalid_argument("");
        club.hourlyRate = parser->numLine(line);
    }
    catch(...){
        std::cerr << "ERR: Not enough data in the provided file.";
    }
    std::cout << club.openingTime;
    club.tables.reserve(club.tableAmount);
    for(int i=0;i<club.tableAmount;++i){
        club.tables.emplace_back(Table{0, std::nullopt, "", i});
    }
    club.freeTables = club.tableAmount;
    clientHandler->setClub(club);
    std::vector<std::string> event;
    while(std::getline(file, line)){
        std::cout << line << "\n";
        event = parser->parseEvent(line);
        clientHandler->handle(event);
    }
    std::cout << club.closingTime;
}


