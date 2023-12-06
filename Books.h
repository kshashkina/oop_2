// Books.h
#ifndef BOOKS_H
#define BOOKS_H

#include "Product.h"
#include <string>

class Books : public Product {
private:
    std::string author;
    std::string genre;
    std::string ISBN;

public:
    Books(int id, const std::string& name, double price, int quantity,
          const std::string& author, const std::string& genre, const std::string& ISBN);

    std::string getAuthor() const;
    std::string getGenre() const;
    std::string getISBN() const;

    void displayAuthor() const;
    void displayDetails() const override;

    ~Books();
};

#endif // BOOKS_H
