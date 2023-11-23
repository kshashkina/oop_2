#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <memory>
#include "Product.h"


class Order {
private:
    static int orderIDCounter;
    int orderID;
    std::string customerName = "";
    double totalCost;
    std::string orderStatus;

public:
    Order();
    ~Order();

    void registerCustomer(const std::string& name);

    void addToCart(std::unique_ptr<Product> product);

    void displayCart() const;

    void showTotalCost() const;

    bool confirmOrder();

    std::vector<std::unique_ptr<Product>> cart;
private:
    void changeOrderStatus(const std::string& newStatus);

    void updateTotalCost();


};

#endif // ORDER_H
