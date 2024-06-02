#include "Order.hpp"

Order::Order(int id, int qty, double pr, const std::string& sd)
    : order_id(id), quantity(qty), price(pr), side(sd) {}
