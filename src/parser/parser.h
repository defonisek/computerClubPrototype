#ifndef CLUB_PARSER_H
#define CLUB_PARSER_H

#include <vector>
#include "../common.h"

namespace computerClub{
    class Parser{
        public:
            bool numLine(std::string &line);

            std::pair<Time, Time> openCloseTime(std::string &line);

            void parseEvent(std::vector<std::string> &line, int tables, int &latestTime); 

        private:
            bool isValidTime(const Time &time);
            bool isValidClient(const std::string &name);
            int timeToMinutes(const Time &time);
    };
}
#endif


