#ifndef PRODUCTCATALOG_H
#define PRODUCTCATALOG_H

#include <vector>
#include <memory>
#include "Product.h"

class ProductCatalog {
public:
    ProductCatalog(std::vector<std::unique_ptr<Product>> &&existingProducts);

    std::vector<std::unique_ptr<Product>> products;

    void addProduct(std::unique_ptr<Product> product);

    void updateProduct(int productID, const std::string &newName, double newPrice, int newQuantity);

    void removeProduct(int productID);

    void viewAllProducts() const;


#endif // PRODUCTCATALOG_H
};