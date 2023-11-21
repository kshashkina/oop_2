#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

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
    string powerConsumption;

public:
    Electronics(int id, const string& name, double price, int quantity,
                const string& brand, const string& model, string powerConsumption)
            : Product(id, name, price, quantity),
              brand(brand), model(model), powerConsumption(powerConsumption) {}

    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getPowerConsumption() const { return powerConsumption; }

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

class Order {
private:
    int orderID;
    string customer;
    vector<unique_ptr<Product>> products;
    double totalCost;
    string orderStatus;

public:
    Order(int id, const string& customer)
            : orderID(id), customer(customer), totalCost(0.0), orderStatus("Pending") {}

    void addProduct(unique_ptr<Product> product) {
        products.push_back(move(product));
    }

    void calculateTotalCost() {
        totalCost = 0.0;
        for (const auto& product : products) {
            totalCost += product->calculateTotalCost(product->getQuantityInStock());
        }
    }

    void changeOrderStatus(const string& newStatus) {
        orderStatus = newStatus;
    }

    ~Order() {}
};

class ProductCatalog {
private:
    vector<unique_ptr<Product>> products;

public:
    ProductCatalog(vector<unique_ptr<Product>>&& existingProducts)
            : products(move(existingProducts)) {}

    void addProduct(unique_ptr<Product> product) {
        products.push_back(move(product));
    }

    void updateProduct(int productID, const string& newName, double newPrice, int newQuantity) {
        auto it = find_if(products.begin(), products.end(), [productID](const auto& product) {
            return product->getProductID() == productID;
        });

        if (it != products.end()) {
            (*it)->setName(newName);
            (*it)->setPrice(newPrice);
            (*it)->setQuantityInStock(newQuantity);
        } else {
            cout << "Product with ID " << productID << " not found." << endl;
        }
    }

    void removeProduct(int productID) {
        auto it = remove_if(products.begin(), products.end(), [productID](const auto& product) {
            return product->getProductID() == productID;
        });

        if (it != products.end()) {
            products.erase(it, products.end());
            cout << "Product with ID " << productID << " removed successfully." << endl;
        } else {
            cout << "Product with ID " << productID << " not found." << endl;
        }
    }

    void viewAllProducts() const {
        cout << "Product Catalog:" << endl;
        for (const auto& product : products) {
            cout << "ID: " << product->getProductID() << ", Name: " << product->getName()
                 << ", Price: " << product->getPrice() << ", Quantity: " << product->getQuantityInStock() << endl;
        }
    }
};

class Inventory {
private:
    vector<unique_ptr<Product>> products;
    int lowStockThreshold;

public:
    Inventory(int threshold, vector<unique_ptr<Product>>&& existingProducts)
            : lowStockThreshold(threshold), products(move(existingProducts)) {}

    void manageStockLevels(int productID, int quantity) {
        auto it = find_if(products.begin(), products.end(), [productID](const auto& product) {
            return product->getProductID() == productID;
        });

        if (it != products.end()) {
            (*it)->setQuantityInStock((*it)->getQuantityInStock() + quantity);

            // Notify if the stock is low
            if ((*it)->getQuantityInStock() < lowStockThreshold) {
                cout << "Low stock alert for product ID " << productID << endl;
            }
        } else {
            cout << "Product with ID " << productID << " not found." << endl;
        }
    }

    void notifyLowStockProducts() const {
        cout << "Low stock products:" << endl;
        for (const auto& product : products) {
            if (product->getQuantityInStock() < lowStockThreshold) {
                cout << "ID: " << product->getProductID() << ", Name: " << product->getName()
                     << ", Current Stock: " << product->getQuantityInStock() << endl;
            }
        }
    }

    void restockProducts() {
        cout << "Products that need restocking:" << endl;
        for (const auto& product : products) {
            if (product->getQuantityInStock() < lowStockThreshold) {
                int quantityToRestock = lowStockThreshold - product->getQuantityInStock();
                manageStockLevels(product->getProductID(), quantityToRestock);
                cout << "Restocked product ID " << product->getProductID() << " by " << quantityToRestock << " units." << endl;
            }
        }
    }
};


class ConfigReader {
public:
    vector<unique_ptr<Product>> loadProducts(string filePath) {
        ifstream file(filePath);
        vector<unique_ptr<Product>> products;
        string line;

        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return products;
        }

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> tokens;

            while (ss.good()) {
                string token;
                getline(ss, token, ',');
                tokens.push_back(token);
            }

            if (tokens.empty()) {
                continue; // Skip empty lines
            }

            string category = tokens[0];

            if (category == "Electronics") {
                auto electronics = readElectronics(tokens);
                if (electronics) {
                    products.push_back(move(electronics));
                }
            } else if (category == "Books") {
                auto books = readBooks(tokens);
                if (books) {
                    products.push_back(move(books));
                }
            } else if (category == "Clothing") {
                auto clothing = readClothing(tokens);
                if (clothing) {
                    products.push_back(move(clothing));
                }
            }
        }

        file.close();
        return products;
    }

private:
    int productIDCounter = 1;

    unique_ptr<Electronics> readElectronics(const vector<string>& tokens) {
        int id = productIDCounter++;
        string name = tokens[1];
        double price = stod(tokens[2]);
        int quantity = stoi(tokens[3]);
        string brand = tokens[4];
        string model = tokens[5];
        string powerConsumption = tokens[6];

        return make_unique<Electronics>(id, name, price, quantity, brand, model, powerConsumption);
    }

    unique_ptr<Books> readBooks(const vector<string>& tokens) {

        int id = productIDCounter++;
        string name = tokens[1];
        double price = stod(tokens[2]);
        int quantity = stoi(tokens[3]);
        string author = tokens[4];
        string genre = tokens[5];
        string ISBN = tokens[6];

        return make_unique<Books>(id, name, price, quantity, author, genre, ISBN);
    }

    unique_ptr<Clothing> readClothing(const vector<string>& tokens) {
        int id = productIDCounter++;
        string name = tokens[1];
        double price = stod(tokens[2]);
        int quantity = stoi(tokens[3]);
        string size = tokens[4];
        string color = tokens[5];
        string material = tokens[6];

        return make_unique<Clothing>(id, name, price, quantity, size, color, material);
    }
};





int main() {
    ConfigReader configReader;
    vector<unique_ptr<Product>> products = configReader.loadProducts("C:\\KSE IT\\oop_2\\text");
    ProductCatalog productCatalog(move(products));

    productCatalog.viewAllProducts();

    return 0;
}
