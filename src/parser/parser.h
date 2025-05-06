#ifndef CLUB_PARSER_H
#define CLUB_PARSER_H

#include <vector>
#include "../common.h"

namespace computerClub{
    class Parser{
        public:
            bool numLine(std::string &line);

            std::pair<std::string, std::string> openCloseTime(std::string &line);

            std::vector<std::string> parseEvent(std::string &line);

    };
}
#endif


