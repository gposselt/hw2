//
// Created by gamma on 2/10/2025.
//

#ifndef BOOK_H
#define BOOK_H

#include <string>

#include "product.h"

class Book : public Product {
public:
    Book(const std::string& category, const std::string& name, double price, int qty, const std::string ISBN,
         const std::string author)
        : Product(category, name, price, qty), isbn(ISBN), author(author) {
    }

    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

protected:
    std::string isbn;
    std::string author;
};


#endif //BOOK_H
