//
// Created by User on 13/04/2025.
//

#ifndef WALLET_H
#define WALLET_H
#include <string>
#include <map>

#include "OrderBookEntry.h"


class Wallet {
public:
    Wallet();
    /** insert currency into the wallet */
    void insertCurrency(std::string type, double amount);
    /** remove currency from the wallet */
    bool removeCurrency(std::string type, double amount);
    /** check if the wallet contains sufficient funds for bid/ask */
    bool containsCurrency(std::string type, double amount);

    /** check if the wallet can fulfill order */
    bool canFulfillOrder(OrderBookEntry order);
    /** update the contents of the wallet
     * assumes the order was made by the owner of the wallet
     */
    void processSale(OrderBookEntry& sale);

    /** generate string representation of wallet  */
    std::string toString();

private:
    std::map<std::string, double> currencies;
};



#endif //WALLET_H
