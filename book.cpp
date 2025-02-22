//
// Created by gamma on 2/10/2025.
//

#include "book.h"

#include <set>
#include <sstream>
#include "util.h"

using namespace std;

set<string> Book::keywords() const {
    set<string> categoryKeywords = parseStringToWords(this->category_);
    set<string> authorWords = parseStringToWords(this->author);
    authorWords.insert(this->isbn);

    set<string> nameKeywords = parseStringToWords(this->name_);

    set<string> categoryBrand = setUnion(categoryKeywords, authorWords);
    return setUnion(categoryBrand, nameKeywords);
}

std::string Book::displayString() const {
    stringstream ss;

    ss << this->name_ << "\nAuthor: " << this->author << " ISBN: " << this->isbn
        << "\n" << this->price_ << " " << this->qty_ << " left." << endl;

    return ss.str();

}

void Book::dump(std::ostream& os) const {
    Product::dump(os);
    os << this->isbn << "\n" << this->author << std::endl;
}
