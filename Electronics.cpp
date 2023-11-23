// Electronics.cpp
#include "Electronics.h"
#include "iostream"


Electronics::Electronics(int id, const std::string& name, double price, int quantity,
                         const std::string& brand, const std::string& model, std::string powerConsumption)
        : Product(id, name, price, quantity), brand(brand), model(model), powerConsumption(powerConsumption) {}

std::string Electronics::getBrand() const {
    return brand;
}

std::string Electronics::getModel() const {
    return model;
}

std::string Electronics::getPowerConsumption() const {
    return powerConsumption;
}

void Electronics::displayPowerConsumption() const {
    std::cout << "Power Consumption: " << powerConsumption << " Watts\n";
}

Electronics::~Electronics() {}
