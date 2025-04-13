#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double _price,
                    double _amount,
                    std::string _timestamp,
                    std::string _product,
                    OrderBookType _orderType,
                    std::string _username
                    )
:   price(_price),
    amount(_amount),
    timestamp(_timestamp),
    product(_product),
    orderType(_orderType),
    username(_username)
{}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s) {
    return s == "bid" ? OrderBookType::bid : s == "ask" ? OrderBookType::ask : OrderBookType::unknown;
}

bool OrderBookEntry::compareByTimestamp(OrderBookEntry &entry1, OrderBookEntry &entry2) {
    return entry1.timestamp < entry2.timestamp;
}
bool OrderBookEntry::compareByPriceAsc(OrderBookEntry &entry1, OrderBookEntry &entry2) {
    return entry1.price < entry2.price;
}
bool OrderBookEntry::compareByPriceDesc(OrderBookEntry &entry1, OrderBookEntry &entry2) {
    return entry1.price > entry2.price;
}

