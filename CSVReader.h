//
// Created by User on 11/04/2025.
//

#ifndef CSVREADER_H
#define CSVREADER_H

#include "OrderBookEntry.h"
#include <vector>

class CSVReader {
public:
    CSVReader();
    // stateless function
    static std::vector<OrderBookEntry> readCSV(std::string csvFileName);
    static std::vector<std::string> tokenize(const std::string& csvLine, char separator);
    static OrderBookEntry stringsToOBE(std::string price,
                                        std::string amount,
                                        std::string timestamp,
                                        std::string product,
                                        OrderBookType type);


private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> tokens);
};

#endif //CSVREADER_H
