//
// Created by User on 11/04/2025.
//

#ifndef ORDERBOOKENTRY_H
#define ORDERBOOKENTRY_H

#pragma once
#include <string>

enum class OrderBookType{bid, ask, sale, unknown};

class OrderBookEntry {
public:
    OrderBookEntry(double _price,
                    double _amount,
                    std::string _timestamp,
                    std::string _product,
                    OrderBookType _orderType);

    static OrderBookType stringToOrderBookType(std::string s);
    static bool compareByTimestamp(OrderBookEntry& entry1, OrderBookEntry& entry2);
    static bool compareByPriceAsc(OrderBookEntry& entry1, OrderBookEntry& entry2);
    static bool compareByPriceDesc(OrderBookEntry& entry1, OrderBookEntry& entry2);

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};

#endif //ORDERBOOKENTRY_H
