//
// Created by gamma on 2/21/2025.
//


#include "mydatastore.h"

#include <vector>
#include <string>
#include <set>
#include "util.h"
#include "product.h"

using namespace std;

MyDataStore::~MyDataStore() {
    for (Product* p : this->products) {
        delete p;
    }

    for (User* u : this->users) {
        delete u;
    }
}

void MyDataStore::addProduct(Product* p) {
    this->products.push_back(p);

#ifdef DEBUG

#endif

    set<string> productKeywords = p->keywords();

#ifdef DEBUG
    cout << "Product with keywords: ";
#endif

    for (const string& keyword : productKeywords) {
        const std::pair<map<string, vector<Product*>>::iterator, bool> test = this->keywordMap.emplace(
            keyword, vector<Product*>{p});
#ifdef DEBUG
        cout << " " << keyword;
#endif

        if (!test.second) {
            this->keywordMap[keyword].push_back(p);
        }
    }
#ifdef DEBUG
    cout << endl;
#endif
}

void MyDataStore::addUser(User* u) {
    this->users.push_back(u);
}

//recursive and search, roughly twice as fast as the first solution I made
vector<Product*> internalAndSearch(vector<Product*>& matches, const vector<Product*>& candidates,
                                   const string& searchWord);

void andSearch(vector<Product*>& matches, const vector<Product*>& candidates, const vector<string>& searchWords) {
    vector<Product*> searchVec = candidates;

    for (const string& s : searchWords) {
        searchVec = internalAndSearch(matches, searchVec, s);
    }

    for (Product* p : searchVec) {
        matches.push_back(p);
    }
}

vector<Product*> internalAndSearch(vector<Product*>& matches, const vector<Product*>& candidates,
                                   const string& searchWord) {
    vector<Product*> validForSearch;

    for (Product* p : candidates) {
        set<string> keywords = p->keywords();

        if (keywords.find(searchWord) != keywords.end()) {
            validForSearch.push_back(p);
        }
    }

    return validForSearch;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    vector<Product*> matches{};


    for (const string& keyword : terms) {
        map<string, vector<Product*>>::iterator result = this->keywordMap.find(keyword);

        if (result == this->keywordMap.end()) {
            continue;
        }

        vector<Product*> potentialMatches = result->second;
        if (type == 1) {
            //or search, all of them qualify
            matches.insert(matches.end(), potentialMatches.begin(), potentialMatches.end());
        }
        else if (type == 0) {
            //and search, abstracted for pretty code :3
            andSearch(matches, potentialMatches, terms);
        }
    }


    return matches;
}

User* MyDataStore::getUserFromUsername(string username) const {
    for (User* u : this->users) {
        if (convToLower(u->getName()) == convToLower(username)) {
            return u;
        }
    }
    return nullptr;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << endl;
#ifdef DEBUG

    cout << "Writing products!" << endl;

#endif

    for (Product* p : this->products) {
        p->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
#ifdef DEBUG

    cout << "Writing users!" << endl;

#endif

    for (User* u : this->users) {
        u->dump(ofile);
    }
    ofile << "</users>" << endl;
}
