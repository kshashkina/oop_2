// Product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
protected:
    int productID;
    std::string name;
    double price;
    int quantityInStock;

public:
    Product(int id, const std::string& name, double price, int quantity);

    int getProductID() const;
    std::string getName() const;
    double getPrice() const;
    int getQuantityInStock() const;

    void setProductID(int id);
    void setName(const std::string& newName);
    void setPrice(double newPrice);
    void setQuantityInStock(int quantity);

    double calculateTotalCost(int quantity) const;
    void decreaseStock(int quantity);
    virtual void displayDetails() const = 0;
    void display() const;


    ~Product();
};

#endif // PRODUCT_H
