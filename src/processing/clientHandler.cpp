#include "../common.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "clientHandler.h"

using namespace computerClub;

int ClientHandler::timeToMinutes(const Time &time){
    return (time[0] - '0') * 600 + (time[1] - '0') * 60 + (time[3] - '0') * 10 + (time[4] - '0');
}

void ClientHandler::handle(const std::vector<std::string> &event, Club &club){
    int eventID = std::stoi(event[1]);
    club.latestTime = timeToMinutes(event[0]);
    try{
        switch(eventID){
            case 1: 
                handleClientArrived(event, club);
                break;
            case 2:
                handleClientSit(event, club);
                break;
            case 3:
                handleClientWait(event, club);
                break;
            case 4:
                handleClientLeft(event, club);
                break;
        }
    }
    catch(const std::exception &e){
        std::cout << event[0] << " " << 13 << " " << e.what() << "\n";
    }
}

void ClientHandler::handleClientArrived(const std::vector<std::string> &event, Club &club){
    const std::string &clientName = event[2];
    if(timeToMinutes(event[0]) < timeToMinutes(club.openingTime) || 
        timeToMinutes(event[0]) > timeToMinutes(club.closingTime)){
            // std::cout << timeToMinutes(event[0]) << " " << timeToMinutes(club.openingTime) << " " << timeToMinutes(club.closingTime) << "\n";
            throw std::runtime_error("NotOpenYet");
    }
    if(club.clientTableMap.count(clientName))
        throw std::runtime_error("YouShallNotPass");
    club.clientTableMap[clientName] = -1;
    club.clientIDMap[clientName] = 1;
}

void ClientHandler::handleClientSit(const std::vector<std::string> &event, Club &club){
    const std::string &clientName = event[2];
    int tableNum = std::stoi(event[3]);
    if(!club.clientTableMap.count(clientName))
        throw std::runtime_error("ClientUnknown");
    Table &table = club.tables[tableNum - 1];
    if(table.currClient.has_value())
        throw std::runtime_error("PlaceIsBusy");
    int prevTable = club.clientTableMap[clientName];
    if(prevTable != -1)
        freeTable(event[0], prevTable, club);
    table.currClient = clientName;
    table.occupiedTime = event[0];
    club.clientTableMap[clientName] = tableNum;
    club.clientIDMap[clientName] = 2;
    club.freeTables--;
}

void ClientHandler::handleClientWait(const std::vector<std::string> &event, Club &club){
    const std::string &clientName = event[2];
    if(club.freeTables > 0)
        throw std::runtime_error("ICanWaitNoLonger!");
    if(club.clientLine.size() > club.tableAmount){
        std::cout << " " << event[0] << " " << 11 << " " << clientName << "\n";
        club.clientIDMap.erase(clientName);
        club.clientTableMap.erase(clientName);
        return;
    }
    club.clientLine.emplace(clientName);
    club.clientIDMap[clientName] = 3;
}

void ClientHandler::handleClientLeft(const std::vector<std::string> &event, Club &club){
    const std::string &clientName = event[2];
    if(!club.clientTableMap.count(clientName))
        throw std::runtime_error("ClientUnknown");
    int tableNum = club.clientTableMap[clientName];
    int currID = club.clientIDMap[clientName];
    if(tableNum == -1 && currID == 3){
        club.clientIDMap.erase(clientName);
        club.clientTableMap.erase(clientName);
        removeFromQueue(clientName, club);
    }
    else if(tableNum == -1 && currID != 3){
        club.clientIDMap.erase(clientName);
        club.clientTableMap.erase(clientName);
    }
    else
        freeTable(event[0], tableNum, club);
}

void ClientHandler::freeTable(const Time &leaveTime, int tableNum, Club &club){
    Table &table = club.tables[tableNum-1];
    int duration = timeToMinutes(leaveTime) - timeToMinutes(table.occupiedTime);
    int hours = (duration + 59) / 60;
    table.revenue += hours * club.hourlyRate;
    table.occupiedTime = addMinutes(table.occupiedTime, duration);
    table.currClient.reset();
    club.freeTables++;
    if(!club.clientLine.empty()){
        std::string nextClient = club.clientLine.front();
        club.clientLine.pop();
        seatClient(leaveTime, nextClient, tableNum, club);
    }
}

void ClientHandler::seatClient(const Time &time, const std::string &clientName, int tableNum, Club &club){
    Table &table = club.tables[tableNum - 1];
    table.currClient = clientName;
    table.occupiedTime = time;
    club.clientTableMap[clientName] = tableNum;
    club.clientIDMap[clientName] = 2;
    club.freeTables--;
    std::cout << time << " " << clientName << " " << 12 << " " << tableNum << "\n";
}

void ClientHandler::removeFromQueue(const std::string &clientName, Club& club){
    std::queue<std::string> newQueue;
    while(!club.clientLine.empty()){
        std::string client = club.clientLine.front();
        club.clientLine.pop();
        if(client != clientName)
            newQueue.push(client);
    }
    club.clientLine = newQueue;
}

Time ClientHandler::addMinutes(const Time &time, int minutes){
    int total = timeToMinutes(time) + minutes;
    int hours = total / 60;
    int mins = total % 60;
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", hours, mins);
    return std::string(buffer);
}