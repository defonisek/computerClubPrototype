#ifndef CLUB_CLIENTHANDLER_H
#define CLUB_CLIENTHANDLER_H

#include "../common.h"

namespace computerClub{
    class ClientHandler{
        public:
            ClientHandler(){};
            void handle(std::vector<std::string> &event){};
            void setClub(Club club){club_ = club;};
        private:
            Club club_;
    };
}
#endif

