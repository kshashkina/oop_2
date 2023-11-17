#include <string>
#include <iostream>

using namespace std;

class Product {
protected:
    int productID;
    string name;
    double price;
    int quantityInStock;

public:
    Product(int id, const string& name, double price, int quantity)
            : productID(id), name(name), price(price), quantityInStock(quantity) {}

    int getProductID() const { return productID; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantityInStock() const { return quantityInStock; }

    void setProductID(int id) { productID = id; }
    void setName(const string& newName) { name = newName; }
    void setPrice(double newPrice) { price = newPrice; }
    void setQuantityInStock(int quantity) { quantityInStock = quantity; }

    // Method to calculate total cost
    double calculateTotalCost(int quantity) const {
        return price * quantity;
    }
};

class Electronics : public Product {
private:
    string brand;
    string model;
    double powerConsumption;

public:
    Electronics(int id, const string& name, double price, int quantity,
                const string& brand, const string& model, double powerConsumption)
            : Product(id, name, price, quantity),
              brand(brand), model(model), powerConsumption(powerConsumption) {}

    string getBrand() const { return brand; }
    string getModel() const { return model; }
    double getPowerConsumption() const { return powerConsumption; }

    void displayPowerConsumption() const {
        cout << "Power Consumption: " << powerConsumption << " Watts\n";
    }
};

class Books : public Product {
private:
    string author;
    string genre;
    string ISBN;

public:
    Books(int id, const string& name, double price, int quantity,
          const string& author, const string& genre, const string& ISBN)
            : Product(id, name, price, quantity), author(author), genre(genre), ISBN(ISBN) {}

    string getAuthor() const { return author; }
    string getGenre() const { return genre; }
    string getISBN() const { return ISBN; }

    void displayAuthor() const {
        cout << "Author: " << author << "\n";
    }
};

class Clothing : public Product {
private:
    string size;
    string color;
    string material;

public:
    Clothing(int id, const string& name, double price, int quantity,
             const string& size, const string& color, const string& material)
            : Product(id, name, price, quantity), size(size), color(color), material(material) {}

    string getSize() const { return size; }
    string getColor() const { return color; }
    string getMaterial() const { return material; }

    void displaySize() const {
        cout << "Size: " << size << "\n";
    }
};
