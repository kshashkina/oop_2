// Electronics.h
#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Product.h"
#include <string>

class Electronics : public Product {
private:
    std::string brand;
    std::string model;
    std::string powerConsumption;

public:
    Electronics(int id, const std::string& name, double price, int quantity,
                const std::string& brand, const std::string& model, std::string powerConsumption);

    std::string getBrand() const;
    std::string getModel() const;
    std::string getPowerConsumption() const;

    void displayPowerConsumption() const;
    void displayDetails() const override;

    ~Electronics();
};

#endif // ELECTRONICS_H
