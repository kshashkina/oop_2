#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>

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
    virtual ~Product() {}
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
    virtual ~Electronics(){}
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
    virtual ~Books(){}
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
    virtual ~Clothing(){}
};

class ProductConfiguration {
public:
    vector<unique_ptr<Product>> loadProducts(const string& filePath) {
        ifstream file(filePath);
        vector<unique_ptr<Product>> products;
        string line;

        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return products;
        }

        while (getline(file, line)){
            if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments

            stringstream ss(line);
            string type, name, additionalAttr1, additionalAttr2, additionalAttr3;
            double price;
            int quantity, id;
            char delimiter = ',';

            getline(ss, type, delimiter);
            getline(ss, name, delimiter);
            ss >> id >> delimiter;
            ss >> price >> delimiter;
            ss >> quantity >> delimiter;

            if (type == "Electronics") {
                getline(ss, additionalAttr1, delimiter);
                getline(ss, additionalAttr2, delimiter);
                getline(ss, additionalAttr3); // Last element or rest of the line
                products.push_back(make_unique<Electronics>(id, name, price, quantity, additionalAttr1, additionalAttr2, stod(additionalAttr3)));
            } else if (type == "Books") {
                getline(ss, additionalAttr1, delimiter);
                getline(ss, additionalAttr2, delimiter);
                getline(ss, additionalAttr3); // Last element or rest of the line
                products.push_back(make_unique<Books>(id, name, price, quantity, additionalAttr1, additionalAttr2, additionalAttr3));
            } else if (type == "Clothing") {
                getline(ss, additionalAttr1, delimiter);
                getline(ss, additionalAttr2, delimiter);
                getline(ss, additionalAttr3); // Last element or rest of the line
                products.push_back(make_unique<Clothing>(id, name, price, quantity, additionalAttr1, additionalAttr2, additionalAttr3));
            }
        }
        return products;
    }
};


int main() {
    ProductConfiguration productConfig;
    string filePath = "C:\\KSE IT\\oop_2\\text";

    auto products = productConfig.loadProducts(filePath);

    for (const auto& product : products) {
        if (auto electronics = dynamic_cast<Electronics*>(product.get())) {
            cout << "Electronics: " << electronics->getName() << ", Price: " << electronics->getPrice()
                 << ", Quantity: " << electronics->getQuantityInStock()
                 << ", Brand: " << electronics->getBrand()
                 << ", Model: " << electronics->getModel()
                 << ", Power: " << electronics->getPowerConsumption() << "W\n";
        } else if (auto book = dynamic_cast<Books*>(product.get())) {
            cout << "Book: " << book->getName() << ", Price: " << book->getPrice()
                 << ", Quantity: " << book->getQuantityInStock()
                 << ", Author: " << book->getAuthor()
                 << ", Genre: " << book->getGenre()
                 << ", ISBN: " << book->getISBN() << "\n";
        } else if (auto clothing = dynamic_cast<Clothing*>(product.get())) {
            cout << "Clothing: " << clothing->getName() << ", Price: " << clothing->getPrice()
                 << ", Quantity: " << clothing->getQuantityInStock()
                 << ", Size: " << clothing->getSize()
                 << ", Color: " << clothing->getColor()
                 << ", Material: " << clothing->getMaterial() << "\n";
        }
    }

    return 0;
}
