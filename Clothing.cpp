// Clothing.cpp
#include "iostream"
#include "Clothing.h"

Clothing::Clothing(int id, const std::string& name, double price, int quantity,
                   const std::string& size, const std::string& color, const std::string& material)
        : Product(id, name, price, quantity), size(size), color(color), material(material) {}

std::string Clothing::getSize() const {
    return size;
}

std::string Clothing::getColor() const {
    return color;
}

std::string Clothing::getMaterial() const {
    return material;
}

void Clothing::displaySize() const {
    std::cout << "Size: " << size << "\n";
}

Clothing::~Clothing() {}
