# Order Book

## Objective
Implement an order book for stock market transactions.

## Core Functions
- Submit Order
- Change Order
- Cancel Order

## Key Concepts
- Memory management
- Process synchronization
- Race conditions

## How to Build and Run
1. Clone the repository
2. Build the project: `make`
3. Run the tests: `./tests/test_order_book`

## Project Structure
order_book/
├── README.md
├── Makefile
├── src/
│   ├── main.cpp
│   ├── Order.hpp
│   ├── OrderBook.hpp
│   ├── Order.cpp
│   ├── OrderBook.cpp
├── tests/
│   ├── test_order_book.cpp
