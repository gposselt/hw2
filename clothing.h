//
// Created by gamma on 2/10/2025.
//

#ifndef CLOTHING_H
#define CLOTHING_H

#include <string>
#include <set>
#include <utility>

#include "product.h"


class Clothing : public Product {
public:
    Clothing(const std::string& category, const std::string& name, double price, int qty, const std::string brand,
             const std::string size)
        : Product(category, name, price, qty), brand(brand), size(size) {
    }

    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

protected:
    std::string brand;
    std::string size;
};


#endif //CLOTHING_H
