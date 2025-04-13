cmake_minimum_required(VERSION 3.30)
project(CurrencyExchange)

set(CMAKE_CXX_STANDARD 17)

add_executable(CurrencyExchange main.cpp
        OrderBookEntry.h
        OrderBookEntry.cpp
        MerkelMain.h
        MerkelMain.cpp
        CSVReader.cpp
        CSVReader.h
        OrderBook.cpp
        OrderBook.h
        Wallet.cpp
        Wallet.h)
