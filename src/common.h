#ifndef CLUB_COMMON_H
#define CLUB_COMMON_H

#include <optional>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

namespace computerClub{
    using Time = std::string;

	struct Table{
		int revenue;
        std::optional<std::string> currClient;
		Time occupiedTime;
        int minutes;
        int tableNumber;
	};

	struct Club{
		int tableAmount;
		int freeTables;
        std::vector<Table> tables;
        std::queue<std::string> clientLine;
        std::unordered_map<std::string, int> clientTableMap;
        std::unordered_map<std::string, int> clientIDMap;
		Time openingTime;
		Time closingTime;
		int hourlyRate;	
        int latestTime;
    };
}
#endif