#include "ProductCatalog.h"
#include "Electronics.h"
#include "Clothing.h"
#include "Books.h"
#include <algorithm>
#include <iostream>

ProductCatalog::ProductCatalog(std::vector<std::unique_ptr<Product>>&& existingProducts)
        : products(std::move(existingProducts)) {}

void ProductCatalog::addProduct(std::unique_ptr<Product> product) {
    products.push_back(std::move(product));
}

void ProductCatalog::updateProduct(int productID, const std::string& newName, double newPrice, int newQuantity) {
    auto it = std::find_if(products.begin(), products.end(), [productID](const auto& product) {
        return product->getProductID() == productID;
    });

    if (it != products.end()) {
        (*it)->setName(newName);
        (*it)->setPrice(newPrice);
        (*it)->setQuantityInStock(newQuantity);
    } else {
        std::cout << "Product with ID " << productID << " not found." << std::endl;
    }
}

void ProductCatalog::removeProduct(int productID) {
    auto it = std::remove_if(products.begin(), products.end(), [productID](const auto& product) {
        return product->getProductID() == productID;
    });

    if (it != products.end()) {
        products.erase(it, products.end());
        std::cout << "Product with ID " << productID << " removed successfully." << std::endl;
    } else {
        std::cout << "Product with ID " << productID << " not found." << std::endl;
    }
}

void ProductCatalog::viewAllProducts() const {
    std::cout << "Product Catalog:" << std::endl;
    for (const auto& product : products) {
        if (auto elec = dynamic_cast<Electronics*>(product.get())) {
            elec->displayDetails();
        }
        else if (auto cloth = dynamic_cast<Clothing*>(product.get())) {
            cloth->displayDetails();
        }
        else if (auto book = dynamic_cast<Books*>(product.get())) {
            book->displayDetails();
        }
        else {
            product->displayDetails();
        }
        std::cout << std::endl;
    }
}

