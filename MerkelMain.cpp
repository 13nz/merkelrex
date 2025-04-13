#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include <limits>

#include "CSVReader.h"
#include "OrderBookEntry.h"


MerkelMain::MerkelMain() {
    init();
}



void MerkelMain::init() {

    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    printMenu();

    while (true) {
        input = getUserOption();
        processUserOption(input);
    }
}


void MerkelMain::printMenu() {
    // print hello
    std::cout << "1: Print help" << std::endl;
    // print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // make an offer
    std::cout << "3: Make an ask" << std::endl;
    // make a bid
    std::cout << "4: Make a bid" << std::endl;
    // print wallet
    std::cout << "5: Print wallet" << std::endl;
    // continue
    std::cout << "6: Continue" << std::endl;

    // std::cout << "======================" << std::endl;
    // std::cout << "Select option 1-6" << std::endl;
    // std::cout << "======================" << std::endl;

    std::cout << "Current time: " << currentTime << std::endl;
}

int MerkelMain::getUserOption() {
    int userOption = 0;
    std::string line;
    std::cout << "Type 1-6 " << std::endl;

    std::getline(std::cin, line);

    try {
        userOption = std::stoi(line);
    }
    catch (const std::exception& e) {
        //std::cout << "Invalid input. Please try again." << std::endl;
    }


    std::cout << "You chose: " << userOption << std::endl;

    return userOption;
}

void MerkelMain::printHelp() {
    std::cout << "HELP" << std::endl;
}

void MerkelMain::printMarketStats() {
    for (std::string const product : orderBook.getKnownProducts()) {
        std::cout << "Product: " << product << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, product, currentTime);

        std::cout << "Asks seen: " << entries.size() << std::endl;

        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    }
}

void MerkelMain::enterAsk() {
    std::cout << "Making an ask - enter: product,price,amount" << std::endl;
    std::cout << "eg: ETH/BTC,200,0.5" << std::endl;

    std::string input;

    // ignore up to the maximum possible size of the stream
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenize(input, ',');

    std::cout << "You typed: " << input << std::endl;
    if (tokens.size() != 3) {
        std::cout << "Invalid input" << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
            tokens[1],
            tokens[2],
            currentTime,
            tokens[0],
            OrderBookType::ask);

            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Insufficient funds. " << std::endl;
            }

            orderBook.insertOrder(obe);
        }
        catch (const std::exception& e) {
            std::cout << "MerkelMain::enterAsk - Invalid input" << std::endl;
        }

    }

}

void MerkelMain::enterBid() {
    std::cout << "Making a bid - enter: product,price,amount" << std::endl;
    std::cout << "eg: ETH/BTC,200,0.5" << std::endl;

    std::string input;

    // ignore up to the maximum possible size of the stream
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenize(input, ',');

    std::cout << "You typed: " << input << std::endl;
    if (tokens.size() != 3) {
        std::cout << "Invalid input" << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
            tokens[1],
            tokens[2],
            currentTime,
            tokens[0],
            OrderBookType::bid);

            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Insufficient funds. " << std::endl;
            }

            orderBook.insertOrder(obe);
        }
        catch (const std::exception& e) {
            std::cout << "MerkelMain::enterBid - Invalid input" << std::endl;
        }

    }}

void MerkelMain::printWallet() {
    std::cout << "Your wallet: " << std::endl;

    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::goToNextTimeFrame() {
    std::cout << "Continuing to next time frame. " << std::endl;

    std::vector<OrderBookEntry> sales  = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    currentTime = orderBook.getNextTime(currentTime);

    std::cout << "Current time: " << currentTime << std::endl;
    std::cout << "Sales: " << sales.size() << std::endl;

    for (OrderBookEntry& sale : sales) {
        std::cout << "Sale amount: " << sale.amount << " Price: " << sale.price << std::endl;

        if (sale.username == "simuser") {
            // update wallet
            wallet.processSale(sale);
        }
    }
}

/** process int user option */
void MerkelMain::processUserOption(int userOption) {
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    else if (userOption == 1) {
        printHelp();
    }
    else if (userOption == 2) {
        printMarketStats();
    }
    else if (userOption == 3) {
        enterAsk();
    }
    else if (userOption == 4) {
        enterBid();
    }
    else if (userOption == 5) {
        printWallet();
    }
    else if (userOption == 6) {
        goToNextTimeFrame();
    }
}
