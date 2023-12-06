// Books.cpp
#include "Books.h"
#include "iostream"

Books::Books(int id, const std::string& name, double price, int quantity,
             const std::string& author, const std::string& genre, const std::string& ISBN)
        : Product(id, name, price, quantity), author(author), genre(genre), ISBN(ISBN) {}

std::string Books::getAuthor() const {
    return author;
}

std::string Books::getGenre() const {
    return genre;
}

std::string Books::getISBN() const {
    return ISBN;
}

void Books::displayAuthor() const {
    std::cout << "Author: " << author << "\n";
}

void Books::displayDetails() const {
    Product::display();
    std::cout << "Author: " << author << std::endl;
    std::cout << "Genre: " << genre << std::endl;
    std::cout << "ISBN: " << ISBN << std::endl;
}


Books::~Books() {}
