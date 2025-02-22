//
// Created by gamma on 2/10/2025.
//

#include "clothing.h"

#include <set>
#include <string>
#include <sstream>

#include "util.h"

using namespace std;

set<string> Clothing::keywords() const {
    set<string> categoryKeywords = parseStringToWords(this->category_);
    set<string> brandKeywords = parseStringToWords(this->brand);
    set<string> nameKeywords = parseStringToWords(this->name_);

    set<string> categoryBrand = setUnion(categoryKeywords, brandKeywords);
    set<string> strings = setUnion(categoryBrand, nameKeywords);

#ifdef DEBUG
    for (auto beg = strings.begin(); beg != strings.end(); beg++) {
        cout << "Keyword: " << *beg << endl;
    }
#endif

    return strings;
}

std::string Clothing::displayString() const {
    stringstream ss;
    ss << this->name_ << "\nSize: " << this->size << " Brand: " << this->brand
        << "\n" << this->price_ << " " << this->qty_ << " left." << endl;

    return ss.str();
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);

    os << this->size << "\n" << this->brand << endl;
}
