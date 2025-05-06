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
            void handle(const std::vector<std::string> &event, Club &club);
        private:
            int timeToMinutes(const Time &time);
            void handleClientArrived(const std::vector<std::string> &event, Club &club);
            void handleClientSit(const std::vector<std::string> &event, Club &club);
            void handleClientWait(const std::vector<std::string> &event, Club &club);
            void handleClientLeft(const std::vector<std::string> &event, Club &club);
            void removeFromQueue(const std::string &clientName, Club& club);
            void freeTable(const Time &leaveTime, int tableNum, Club &club);
            Time addMinutes(const Time &time, int minutes);
            void seatClient(const Time &time, const std::string &clientName, int tableNum, Club &club);
    };
}
#endif

