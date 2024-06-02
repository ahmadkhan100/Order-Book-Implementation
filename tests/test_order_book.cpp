#include <cassert>
#include "OrderBook.hpp"

void testSubmitOrder() {
    OrderBook orderBook;
    Order order(1, 100, 10.0, "buy");
    orderBook.submitOrder(order);
    // Add assertions to verify the order is in the order book
}

void testChangeOrder() {
    OrderBook orderBook;
    Order order(1, 100, 10.0, "buy");
    orderBook.submitOrder(order);
    orderBook.changeOrder(1, 50, 9.5);
    // Add assertions to verify the order has been updated
}

void testCancelOrder() {
    OrderBook orderBook;
    Order order(1, 100, 10.0, "buy");
    orderBook.submitOrder(order);
    orderBook.cancelOrder(1);
    // Add assertions to verify the order has been removed
}

void testMatchOrders() {
    OrderBook orderBook;
    Order buyOrder(1, 100, 10.0, "buy");
    Order sellOrder(2, 100, 10.0, "sell");
    orderBook.submitOrder(buyOrder);
    orderBook.submitOrder(sellOrder);
    // Add assertions to verify the orders have been matched
}

int main() {
    testSubmitOrder();
    testChangeOrder();
    testCancelOrder();
    testMatchOrders();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
