#include "Product.h"
#include "iostream"


Product::Product(int id, const std::string& name, double price, int quantity)
        : productID(id), name(name), price(price), quantityInStock(quantity) {}

int Product::getProductID() const {
    return productID;
}

std::string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantityInStock() const {
    return quantityInStock;
}

void Product::setProductID(int id) {
    productID = id;
}

void Product::setName(const std::string& newName) {
    name = newName;
}

void Product::setPrice(double newPrice) {
    price = newPrice;
}

void Product::setQuantityInStock(int quantity) {
    quantityInStock = quantity;
}

double Product::calculateTotalCost(int quantity) const {
    return price * quantity;
}

void Product::decreaseStock(int quantity) {
    quantityInStock -= quantity;
}

void Product::display() const {
    std::cout << "Product ID: " << productID << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Price: $" << price << std::endl;
    std::cout << "Quantity in Stock: " << quantityInStock << std::endl;
}


Product::~Product() {}
