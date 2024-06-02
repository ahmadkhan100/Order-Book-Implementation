#include "OrderBook.hpp"
#include <iostream>
#include <algorithm>

OrderBook::OrderBook() {}

void OrderBook::submitOrder(const Order& order) {
    std::lock_guard<std::mutex> lock(mtx);
    if (order.side == "buy") {
        buy_orders[order.price].push_back(order);
    } else {
        sell_orders[order.price].push_back(order);
    }
    order_map[order.order_id] = order;
    matchOrders();
}

void OrderBook::changeOrder(int order_id, int quantity, double price) {
    std::lock_guard<std::mutex> lock(mtx);
    if (order_map.find(order_id) != order_map.end()) {
        Order& order = order_map[order_id];
        if (quantity > 0) {
            order.quantity = quantity;
        }
        if (price > 0) {
            if (order.side == "buy") {
                auto& orders = buy_orders[order.price];
                orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
                order.price = price;
                buy_orders[price].push_back(order);
            } else {
                auto& orders = sell_orders[order.price];
                orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
                order.price = price;
                sell_orders[price].push_back(order);
            }
        }
        matchOrders();
    }
}

void OrderBook::cancelOrder(int order_id) {
    std::lock_guard<std::mutex> lock(mtx);
    if (order_map.find(order_id) != order_map.end()) {
        Order order = order_map[order_id];
        if (order.side == "buy") {
            auto& orders = buy_orders[order.price];
            orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
        } else {
            auto& orders = sell_orders[order.price];
            orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
        }
        order_map.erase(order_id);
    }
}

void OrderBook::matchOrders() {
    auto buy_it = buy_orders.rbegin();
    auto sell_it = sell_orders.begin();
    while (buy_it != buy_orders.rend() && sell_it != sell_orders.end() && buy_it->first >= sell_it->first) {
        Order& buy_order = buy_it->second.front();
        Order& sell_order = sell_it->second.front();
        int matched_quantity = std::min(buy_order.quantity, sell_order.quantity);

        buy_order.quantity -= matched_quantity;
        sell_order.quantity -= matched_quantity;

        if (buy_order.quantity == 0) {
            buy_it->second.erase(buy_it->second.begin());
            if (buy_it->second.empty()) {
                buy_it = std::make_reverse_iterator(buy_orders.erase(std::next(buy_it).base()));
            } else {
                ++buy_it;
            }
        }

        if (sell_order.quantity == 0) {
            sell_it->second.erase(sell_it->second.begin());
            if (sell_it->second.empty()) {
                sell_it = sell_orders.erase(sell_it);
            } else {
                ++sell_it;
            }
        }
    }
}

void OrderBook::printOrderBook() const {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Buy Orders:" << std::endl;
    for (auto it = buy_orders.rbegin(); it != buy_orders.rend(); ++it) {
        for (const auto& order : it->second) {
            std::cout << "Order ID: " << order.order_id << ", Quantity: " << order.quantity << ", Price: " << order.price << std::endl;
        }
    }
    std::cout << "\nSell Orders:" << std::endl;
    for (const auto& [price, orders] : sell_orders) {
        for (const auto& order : orders) {
            std::cout << "Order ID: " << order.order_id << ", Quantity: " << order.quantity << ", Price: " << order.price << std::endl;
        }
    }
}
