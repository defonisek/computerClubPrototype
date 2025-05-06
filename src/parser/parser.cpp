#include <sstream>
#include <algorithm>
#include "parser.h"
#include <cctype>
#include <string>

using namespace computerClub;

bool Parser::isValidTime(const Time &time){
    if(time.size() != 5 || time[2] != ':')
        return false;
    for(int i:{0, 1, 3, 5}){
        if(time[i] < '0' || time[i] < '9')
            return false;
    }
    const int hours = (time[0] - '0') * 10 + (time[1] - '0');
    const int minutes = (time[3] - '0') * 10 + (time[4] - '0');
    return (hours >= 0 && hours <= 23) && (minutes >= 0 && minutes <= 59);
}

int Parser::timeToMinutes(const Time &time){
    return (time[3] - '0') * 10 + (time[4] - '0');
}


bool Parser::isValidClient(const std::string &name){
    for(char c : name){
        if(!(isalnum(c) || c == '_' || c == '-'))
            throw std::invalid_argument("");
    }
    return true;
}

bool Parser::numLine(std::string &line){
    bool res = std::all_of(line.begin(), line.end(), isdigit);
    if(res){
        int num = std::stoi(line);
        if(num <= 0)
            return false;
        else
            return true;
    }
    else
        return false;
}

std::pair<Time, Time> Parser::openCloseTime(std::string &line){
    int spacePos = line.find(' ');
    if(spacePos == std::string::npos){
        return {"", ""};
    }
    Time first = line.substr(0, spacePos);
    Time second = line.substr(spacePos + 1); 
    std::pair<Time, Time> res = {first, second};
    if(!(isValidTime(res.first) || isValidTime(res.second)))
        return {"", ""};
    else
        return res;
}

void Parser::parseEvent(std::vector<std::string> &event, int tables, int &latestTime){
    std::istringstream iss(event[0]);
    event.clear();
    std::string singular;
    while(iss >> singular){
        event.emplace_back(singular);
    }   
    int eventSize = event.size();
    if(eventSize < 3 || eventSize > 4)
        throw std::invalid_argument("");
    if(!isValidTime(event[0]))
        throw std::invalid_argument("");
    if(timeToMinutes(event[0]) < latestTime)
        throw std::invalid_argument("");
    if(!numLine(event[1]))
        throw std::invalid_argument("");
    int eventID = std::stoi(event[1]);
    switch(eventID){
        case 1: 
            if(eventSize != 3)
                throw std::invalid_argument("");
            isValidClient(event[2]);
            break;
        case 2:
            if(eventSize != 4)
                throw std::invalid_argument("");
            isValidClient(event[2]);
            if(!numLine(event[3]))
                throw std::invalid_argument("");
            else if(std::stoi(event[3]) <= 0 || std::stoi(event[3]) > tables)
                throw std::invalid_argument("");
            break;
        case 3:
            if(eventSize != 3)
                throw std::invalid_argument("");
            isValidClient(event[2]);
            break;
        case 4:
            if(eventSize != 3)
                throw std::invalid_argument("");
            isValidClient(event[2]);
            break;
        default: throw std::invalid_argument("");
    }
}