#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include "Product.h"
#include "Electronics.h"
#include "Books.h"
#include "Clothing.h"
#include "ProductCatalog.h"
#include "Order.h"

using namespace std;

class Inventory {
private:
    ProductCatalog& productCatalog;
    int lowStockThreshold;

public:
    Inventory(int threshold, ProductCatalog& catalog)
            : lowStockThreshold(threshold), productCatalog(catalog) {}

    void manageStockLevels(int productID, int quantity) {
        auto it = find_if(productCatalog.products.begin(), productCatalog.products.end(), [productID](const auto& product) {
            return product->getProductID() == productID;
        });

        if (it != productCatalog.products.end()) {
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
        for (const auto& product : productCatalog.products) {
            if (product->getQuantityInStock() < lowStockThreshold) {
                cout << "ID: " << product->getProductID() << ", Name: " << product->getName()
                     << ", Current Stock: " << product->getQuantityInStock() << endl;
            }
        }
    }

    void restockProducts() {
        cout << "Products that need restocking:" << endl;
        for (const auto& product : productCatalog.products) {
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


class ShoppingSystem {
private:
    ProductCatalog& productCatalog;
    Order cart;

public:
    ShoppingSystem(ProductCatalog& catalog)
            : productCatalog(catalog) {}

    void displayAllProducts() const {
        productCatalog.viewAllProducts();
    }

    void addToCart(int productID, int quantity) {
        auto product = findProduct(productID);

        if (product) {
            if (quantity > 0 && quantity <= product->getQuantityInStock()) {
                auto productCopy = createProductCopy(product, quantity);
                cart.addToCart(move(productCopy));
                product->setQuantityInStock(product->getQuantityInStock() - quantity);
            } else {
                cout << "Invalid quantity or insufficient stock for product ID " << productID << endl;
            }
        } else {
            cout << "Product with ID " << productID << " not found." << endl;
        }
    }


    void deleteFromCart(int productID, int quantity) {
        auto it = std::find_if(cart.cart.begin(), cart.cart.end(), [productID](const auto& product) {
            return product->getProductID() == productID;
        });

        if (it != cart.cart.end()) {
            int remainingQuantity = (*it)->getQuantityInStock() - quantity;

            if (remainingQuantity <= 0) {
                // If the remaining quantity is zero or negative, remove the product from the cart
                cart.cart.erase(it);
                std::cout << "Product with ID " << productID << " removed from the cart." << std::endl;
            } else {
                // Update the quantity of the product in the cart
                (*it)->setQuantityInStock(remainingQuantity);
                std::cout << "Quantity of product with ID " << productID << " reduced to " << remainingQuantity << " in the cart." << std::endl;
            }
        } else {
            std::cout << "Product with ID " << productID << " not found in the cart." << std::endl;
        }
    }


    void confirmOrder() {
        cart.confirmOrder();
    }

    void displayCart() const {
        cart.displayCart();
    }

    void registration(string customerName) {
        cart.registerCustomer(customerName);
    }

private:
    unique_ptr<Product> findProduct(int productID) const {
        auto it = find_if(productCatalog.products.begin(), productCatalog.products.end(), [productID](const auto& product) {
            return product->getProductID() == productID;
        });

        return (it != productCatalog.products.end()) ? makeProductCopy(*it) : nullptr;
    }

    unique_ptr<Product> makeProductCopy(const unique_ptr<Product>& product) const {
        return make_unique<Product>(product->getProductID(), product->getName(),
                                    product->getPrice(), product->getQuantityInStock());
    }

    unique_ptr<Product> createProductCopy(const unique_ptr<Product>& product, int quantity) const {
        return make_unique<Product>(product->getProductID(), product->getName(),
                                    product->getPrice(), quantity);
    }
};

int main() {
    ConfigReader configReader;
    std::vector<std::unique_ptr<Product>> products = configReader.loadProducts("C:\\KSE IT\\oop_2\\text");
    ProductCatalog productCatalog(std::move(products));
    Inventory inventory(15, productCatalog);
    ShoppingSystem shoppingSystem(productCatalog);

    std::string userType;
    std::cout << "Welcome to the Shopping System!\n";

    // Choose user type (admin or user)
    std::cout << "Enter user type ('admin' or 'user'): ";
    std::getline(std::cin, userType);

    if (userType == "admin") {
        // Admin scenario
        std::string adminCommand;
        while (true) {
            std::cout << "\nEnter an admin command (type 'help' for a list of commands): ";
            std::getline(std::cin, adminCommand);

            if (adminCommand == "exit") {
                break;
            } else if (adminCommand == "help") {
                std::cout << "Admin commands:\n"
                             "- display: Display all products\n"
                             "- add: Add a product to the catalog\n"
                             "- update: Update product information\n"
                             "- remove: Remove a product from the catalog\n"
                             "- inventory: Manage inventory\n"
                             "- restock: Restock products\n"
                             "- exit: Exit the program\n";
            } else if (adminCommand == "display") {
                productCatalog.viewAllProducts();
            } else if (adminCommand == "add") {
                // Admin can add a new product to the catalog
                int category;
                std::cout << "Enter product category (1 for Electronics, 2 for Books, 3 for Clothing): ";
                std::cin >> category;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

                std::cout << "Enter product details separated by commas (ID, Name, Price, Quantity, Var1, Var2, Var3): ";
                string productDetails;
                getline(cin, productDetails);
                stringstream ss(productDetails);
                vector<string> tokens;
                string token;
                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }

                unique_ptr<Product> newProduct;
                if (category == 1) {
                    // Assuming the tokens are correctly formatted for Electronics
                    int id = stoi(tokens[0]);
                    double price = stod(tokens[2]);
                    int quantity = stoi(tokens[3]);
                    newProduct = make_unique<Electronics>(id, tokens[1], price, quantity, tokens[4], tokens[5], tokens[6]);
                } else if (category == 2) {
                    // Assuming the tokens are correctly formatted for Books
                    int id = stoi(tokens[0]);
                    double price = stod(tokens[2]);
                    int quantity = stoi(tokens[3]);
                    newProduct = make_unique<Books>(id, tokens[1], price, quantity, tokens[4], tokens[5], tokens[6]);
                } else if (category == 3) {
                    // Assuming the tokens are correctly formatted for Clothing
                    int id = stoi(tokens[0]);
                    double price = stod(tokens[2]);
                    int quantity = stoi(tokens[3]);
                    newProduct = make_unique<Clothing>(id, tokens[1], price, quantity, tokens[4], tokens[5], tokens[6]);
                } else {
                    std::cout << "Invalid category.\n";
                    continue;
                }

                productCatalog.addProduct(std::move(newProduct));
            }
            else if (adminCommand == "update") {
                int productID, quantity;
                std::string newName;
                double newPrice;

                std::cout << "Enter product ID, new name, new price, and new quantity: ";
                std::cin >> productID >> newName >> newPrice >> quantity;
                std::cin.ignore();

                productCatalog.updateProduct(productID, newName, newPrice, quantity);
            } else if (adminCommand == "remove") {
                int productID;
                std::cout << "Enter product ID to remove: ";
                std::cin >> productID;
                std::cin.ignore();

                productCatalog.removeProduct(productID);
            } else if (adminCommand == "inventory") {
                int productID, quantity;
                std::cout << "Enter product ID and quantity to manage stock levels: ";
                std::cin >> productID >> quantity;
                std::cin.ignore();

                inventory.manageStockLevels(productID, quantity);
            }
            else if (adminCommand == "restock"){
                inventory.restockProducts();
            }else {
                    std::cout << "Invalid command. Type 'help' for a list of commands.\n";
                }
            }

    } else if (userType == "user") {
        // User scenario
        std::string userCommand;
        std::string username;
        std::cout << "Enter your username for registration: ";
        std::getline(std::cin, username);
        shoppingSystem.registration(username);

        while (true) {
            std::cout << "\nEnter a user command (type 'help' for a list of commands): ";
            std::getline(std::cin, userCommand);

            if (userCommand == "exit") {
                break;
            } else if (userCommand == "help") {
                std::cout << "User commands:\n"
                             "- display: Display all products\n"
                             "- add: Add a product to the cart\n"
                             "- delete: Delete a product from the cart\n"
                             "- cart: Display the cart\n"
                             "- confirm: Confirm the order\n"
                             "- exit: Exit the program\n";
            } else if (userCommand == "display") {
                shoppingSystem.displayAllProducts();
            } else if (userCommand == "add") {
                int productID, quantity;
                std::cout << "Enter product ID and quantity to add to the cart: ";
                std::cin >> productID >> quantity;
                std::cin.ignore();
                shoppingSystem.addToCart(productID, quantity);
            } else if (userCommand == "delete") {
                int productID, quantity;
                std::cout << "Enter product ID and quantity to delete from the cart: ";
                std::cin >> productID >> quantity;
                std::cin.ignore();
                shoppingSystem.deleteFromCart(productID, quantity);
            } else if (userCommand == "cart") {
                shoppingSystem.displayCart();
            } else if (userCommand == "confirm") {
                shoppingSystem.confirmOrder();
            } else {
                std::cout << "Invalid command. Type 'help' for a list of commands.\n";
            }
        }
    } else {
        std::cout << "Invalid user type. Exiting the program.\n";
    }

    std::cout << "Exiting the Shopping System. Goodbye!\n";

    return 0;
}


