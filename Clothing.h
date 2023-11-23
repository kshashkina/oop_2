// Clothing.h
#ifndef CLOTHING_H
#define CLOTHING_H

#include "Product.h"
#include <string>

class Clothing : public Product {
private:
    std::string size;
    std::string color;
    std::string material;

public:
    Clothing(int id, const std::string& name, double price, int quantity,
             const std::string& size, const std::string& color, const std::string& material);

    std::string getSize() const;
    std::string getColor() const;
    std::string getMaterial() const;

    void displaySize() const;

    ~Clothing();
};

#endif // CLOTHING_H
