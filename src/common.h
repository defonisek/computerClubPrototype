#ifndef CLUB_COMMON_H
#define CLUB_COMMON_H

#include <optional>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

namespace computerClub{
    using Time = std::string;

	struct Client{
        std::string name;
        std::optional<int> currTable;
        int currID;
    };

	struct Table{
		int revenue;
        std::optional<std::string> currClient;
		Time occupiedTime;
        int tableNumber;
	};

	struct Club{
		int tableAmount;
		int freeTables;
        std::vector<Table> tables;
        std::queue<std::string> clientLine;
        std::unordered_map<std::string, int> clientTableMap;
		Time openingTime;
		Time closingTime;
		int hourlyRate;	
        int latestTime;
    };
}
#endif