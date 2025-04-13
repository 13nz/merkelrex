//
// Created by User on 11/04/2025.
//

#include "OrderBook.h"

#include <algorithm>
#include <iostream>

#include "CSVReader.h"
#include <map>

OrderBook::OrderBook(std::string filename) {
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts() {
    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;

    for (OrderBookEntry& order : orders) {
        prodMap[order.product] = true;
    }

    // flatten map to a vector of strings
    // iterate over product map
    for (auto const& e : prodMap) {
        // e.first = key
        // push key to products vector
        products.push_back(e.first);
    }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp) {

    std::vector<OrderBookEntry> orders_sub;

    for (OrderBookEntry& order : orders) {
        if (order.orderType == type &&
            order.product == product &&
            order.timestamp == timestamp)
        {
            orders_sub.push_back(order);
        }
    }

    return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders) {
    double max = orders[0].price;

    for (OrderBookEntry& order : orders) {
        if (order.price > max) {
            max = order.price;
        }
    }

    return max;

}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders) {
    double min = orders[0].price;

    for (OrderBookEntry& order : orders) {
        if (order.price < min) {
            min = order.price;
        }
    }

    return min;
}

std::string OrderBook::getEarliestTime() {
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp) {

    std::string next_timestamp = "";
    for (OrderBookEntry& order : orders) {
        if (order.timestamp > timestamp) {
            next_timestamp = order.timestamp;
            break;
        }
    }

    if (next_timestamp == "") {
        next_timestamp = orders[0].timestamp;
    }

    return next_timestamp;
}

void OrderBook::insertOrder(OrderBookEntry& order) {
    orders.push_back(order);

    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) {
    // vector of asks
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    // vector of bids
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    // vector of sales
    std::vector<OrderBookEntry> sales;

    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);

    // sort bids highest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    // loop thru bids and asks
    for (OrderBookEntry& ask : asks) {
        for (OrderBookEntry& bid : bids) {
            if (bid.price >= ask.price)
            {
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::asksale};

                OrderBookType type;

                if (bid.username == "simuser") {
                    type = OrderBookType::bidsale;
                    sale.username = "simuser";
                    sale.orderType = type;
                }

                if (ask.username == "simuser") {
                    type = OrderBookType::asksale;
                    sale.username = "simuser";
                    sale.orderType = type;
                }

                if (bid.amount == ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }
                if (bid.amount > ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }
                if (bid.amount < ask.amount && bid.amount > 0) {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }

    return sales;

}