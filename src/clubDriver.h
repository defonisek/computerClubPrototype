#ifndef CLUB_CLUBDRIVER_H
#define CLUB_CLUBDRIVER_H

#include <string>
#include "common.h"
#include "processing/clientHandler.h"
#include "parser/parser.h"

namespace computerClub{
    class ClubDriver {
        public:
            ClubDriver();

            virtual ~ClubDriver();

            void process(std::string &filename);

        private:
            ClientHandler *clientHandler;
            Parser *parser;
            Club club;
    };
}

#endif