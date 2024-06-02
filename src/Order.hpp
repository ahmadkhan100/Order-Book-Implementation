#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>

class Order {
public:
    int order_id;
    int quantity;
    double price;
    std::string side;

    Order(int id, int qty, double pr, const std::string& sd);
};

#endif // ORDER_HPP
