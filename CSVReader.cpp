#include "CSVReader.h"
#include <iostream>
#include <fstream>


CSVReader::CSVReader() {

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName) {
    std::vector<OrderBookEntry> entries;

    std::fstream csvFile{csvFileName};
    std::string line;

    if (csvFile.is_open()) {
        while (std::getline(csvFile, line)) {
            try {
                OrderBookEntry obe = stringsToOBE(tokenize(line, ','));
                entries.push_back(obe);
            }
            catch (const std::exception& e) {
                std::cout << "CSVReader::readCSV: Bad data. " << std::endl;
            }

        } // end of while
    }

    std::cout  << "CSVReader::readCSV read: " << entries.size() << " entries." << std::endl;

    return entries;
}

std::vector<std::string> CSVReader::tokenize(const std::string &csvLine, char separator) {
    std::vector<std::string> tokens;
    signed int start, end;
    start = csvLine.find_first_not_of(separator, 0);

    do {
        std::string token;
        end = csvLine.find_first_of(separator, start);

        if (start == csvLine.length() || start == end) {
            break;
        }

        if (end >= 0) {
            token = csvLine.substr(start, end - start);
        }
        else {
            token = csvLine.substr(start, csvLine.length() - start);
        }

        tokens.push_back(token);
        start = end + 1;
    }
    while (end != std::string::npos);

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) {
    double price, amount;
    if (tokens.size() != 5) {
        std::cout << "Bad line" << std::endl;
        throw std::exception();
    }
    // we have 5 tokens
    // std::stod > converts string to double
    try {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (std::exception& e) {
        std::cout << "Exception. " << std::endl;
        throw e.what();
    }

    OrderBookEntry obe { price,
                        amount,
                        tokens[0],
                        tokens[1],
                        OrderBookEntry::stringToOrderBookType(tokens[2])
    };

    return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::string price_string,
                                        std::string amount_string,
                                        std::string timestamp,
                                        std::string product,
                                        OrderBookType type)
{
    double price, amount;

    try {
        price = std::stod(price_string);
        amount = std::stod(amount_string);
    }
    catch (std::exception& e) {
        std::cout << "CSVReader::stringsToOBE - Bad float: " << price << std::endl;
        std::cout << "CSVReader::stringsToOBE - Bad float: " << amount << std::endl;
        throw e.what();
    }

    OrderBookEntry obe {price,
                        amount,
                        timestamp,
                        product,
                        type
    };

    return obe;
}


