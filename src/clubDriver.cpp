#include "clubDriver.h"
#include <fstream>
#include <iostream>
#include "processing/clientHandler.h"
#include "parser/parser.h"

using namespace computerClub;

ClubDriver::ClubDriver(){ 
    clientHandler = new ClientHandler();
    parser = new Parser();
    club = {0, 0, {}, {}, {}, {}, "", "", 0, 0};
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
        if(parser->numLine(line))
            club.tableAmount = std::stoi(line);
        else
            throw std::invalid_argument("");
        if(!std::getline(file, line))
            throw std::invalid_argument("");
        std::pair<std::string, std::string> openCloseT = parser->openCloseTime(line);
        if(openCloseT.first == "")
            throw std::invalid_argument("");
        club.openingTime = openCloseT.first;
        club.closingTime = openCloseT.second;
        if(!std::getline(file, line))
            throw std::invalid_argument("");
        if(parser->numLine(line))
            club.hourlyRate = std::stoi(line);
        else
            throw std::invalid_argument("");
    }
    catch(...){
        std::cerr << "ERR: Not enough or incorrect data in the provided file (check first 3 lines).";
        return;
    }
    std::cout << club.openingTime << "\n";
    club.tables.reserve(club.tableAmount);
    for(int i=0;i<club.tableAmount;++i){
        club.tables.emplace_back(Table{0, std::nullopt, "", 0, i});
    }
    club.freeTables = club.tableAmount;
    std::vector<std::string> event;
    while(std::getline(file, line)){
        std::cout << line << "\n";
        event.emplace_back(line);
        try{
            parser->parseEvent(event, club.tableAmount, club.latestTime);
        }
        catch(...){
            return;
        }
        clientHandler->handle(event, club);
        event.clear();
    }
    clientHandler->endOfDay(club);
    std::cout << club.closingTime << "\n";
    for(const auto &table : club.tables){
        std::cout << table.tableNumber + 1 << " " << table.revenue << " " << clientHandler->minutesToTime(table.minutes) << "\n";
    }
}