//
// Created by gamma on 2/10/2025.
//


#include <string>
#include <set>
#include <sstream>
#include "product.h"
#include "util.h"

#include "movie.h"

using namespace std;

set<string> Movie::keywords() const {
    set<string> categoryKeywords = parseStringToWords(this->category_);
    categoryKeywords.insert(convToLower(this->genre));

    set<string> nameKeywords = parseStringToWords(this->name_);
    return setUnion(categoryKeywords, nameKeywords);
}


std::string Movie::displayString() const {
    stringstream ss;

    ss << this->name_ << "\nGenre: " << this->genre << " Rating: " << this->rating
        << "\n" << this->price_ << " " << this->qty_ << " left." << endl;

    return ss.str();
}


void Movie::dump(ostream& os) const {
    Product::dump(os);
    os << this->genre << "\n" << this->rating << endl;
}
