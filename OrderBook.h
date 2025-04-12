//
// Created by User on 11/04/2025.
//

#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"


class OrderBook {
public:
    /** Construct, reading CSV data file */
    OrderBook(std::string filename);
    /** return vector of all known products in the dataset */
    std::vector<std::string> getKnownProducts();
    /** return vector of Orders according to the passed filters */
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);
    /** get high price */
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    /** get low price */
    static double getLowPrice(std::vector<OrderBookEntry>& orders);

    // assuming orders are sorted by timestamp
    /** get earliest time in orderbook */
    std::string getEarliestTime();
    /** returns next time after the sent time in the orderbook
     *  if there is no next timestamp wraps around to the start
     */
    std::string getNextTime(std::string timestamp);

    /** inserts order to order book, order passed by reference */
    void insertOrder(OrderBookEntry& order);

    /** match asks to bids */
    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

private:
    std::vector<OrderBookEntry> orders;
};



#endif //ORDERBOOK_H
