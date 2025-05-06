#ifndef CLUB_CLIENTHANDLER_H
#define CLUB_CLIENTHANDLER_H

#include "../common.h"

namespace computerClub{
    struct GeneratedEvent{
        Time time;
        std::string clientOrMessage;
        int eventId;
        std::string additionalParam;
    };

    class ClientHandler{
        public:
            void handle(std::vector<std::string> &event, Club &club);
    };
}
#endif

