#include "OrderBook.hpp"

int main() {
    OrderBook orderBook;

    Order order1(1, 100, 10.0, "buy");
    Order order2(2, 150, 10.0, "sell");

    orderBook.submitOrder(order1);
    orderBook.submitOrder(order2);

    orderBook.printOrderBook();

    orderBook.changeOrder(1, 50, 9.5);
    orderBook.cancelOrder(2);

    orderBook.printOrderBook();

    return 0;
}
