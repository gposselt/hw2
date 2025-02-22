//
// Created by gamma on 2/10/2025.
//

#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"

class Movie : public Product {
public:
    Movie(const std::string category, const std::string name, double price, int qty, const std::string genre,
          const std::string rating) : Product(category, name, price, qty), genre(genre), rating(rating) {
    }

    std::set<std::string> keywords() const override;

    std::string displayString() const override;
    void dump(std::ostream& os) const override;

protected:
    std::string genre{};
    std::string rating{};
};


#endif //MOVIE_H
