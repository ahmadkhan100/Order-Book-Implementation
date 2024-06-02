#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include <vector>
#include <unordered_map>
#include <map>
#include <mutex>
#include "Order.hpp"

class OrderBook {
public:
    OrderBook();
    void submitOrder(const Order& order);
    void changeOrder(int order_id, int quantity, double price);
    void cancelOrder(int order_id);
    void printOrderBook() const;

private:
    std::map<double, std::vector<Order>> buy_orders;
    std::map<double, std::vector<Order>> sell_orders;
    std::unordered_map<int, Order> order_map;
    mutable std::mutex mtx;

    void matchOrders();
};

#endif // ORDER_BOOK_HPP
