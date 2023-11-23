#include "Order.h"
#include "ProductCatalog.h"

int Order::orderIDCounter = 0;

Order::Order()
        : orderID(++orderIDCounter), totalCost(0.0), orderStatus("Pending") {}

Order::~Order() {}

void Order::registerCustomer(const std::string& name) {
    customerName = name;
    std::cout << "Customer " << name << " registered." << std::endl;
}

void Order::addToCart(std::unique_ptr<Product> product) {
    if (customerName == "") {
        std::cout << "You are not registered. To add products, you should register first." << std::endl;
    } else {
        std::cout << "Added " << product->getName() << " to the cart." << std::endl;
        cart.push_back(std::move(product));
        updateTotalCost();
    }
}

void Order::displayCart() const {
    std::cout << "Cart for " << customerName << ":" << std::endl;
    for (const auto& product : cart) {
        std::cout << "Product ID: " << product->getProductID() << ", Name: " << product->getName()
                  << ", Quantity: " << product->getQuantityInStock() << ", Total Cost: "
                  << product->calculateTotalCost(product->getQuantityInStock()) << std::endl;
    }
    showTotalCost();
}

void Order::showTotalCost() const {
    std::cout << "Total Cost of Cart: " << totalCost << std::endl;
}

bool Order::confirmOrder() {
    if (cart.empty()) {
        std::cout << "Nothing in the cart. Cannot confirm the order." << std::endl;
        return false;
    }

    std::cout << "Confirming order for " << customerName << std::endl;
    changeOrderStatus("Confirmed");
    std::cout << "Order confirmed. Order ID: " << orderID << std::endl;

    cart.clear();
    totalCost = 0.0;
    return true;
}

void Order::changeOrderStatus(const std::string& newStatus) {
    orderStatus = newStatus;
}

void Order::updateTotalCost() {
    totalCost = 0.0;
    for (const auto& product : cart) {
        totalCost += product->calculateTotalCost(product->getQuantityInStock());
    }
}
