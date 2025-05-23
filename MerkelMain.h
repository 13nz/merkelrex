//
// Created by User on 11/04/2025.
//

#ifndef MERKELMAIN_H
#define MERKELMAIN_H
#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain {
public:
    MerkelMain();

    /** call this to start the sim */
    void init();

private:
    void printMenu();
    int getUserOption();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void goToNextTimeFrame();
    void processUserOption(int userOption);

    std::string currentTime;

    OrderBook orderBook{"20200317.csv"};
    // OrderBook orderBook{"test.csv"};

    Wallet wallet;
};

#endif //MERKELMAIN_H
