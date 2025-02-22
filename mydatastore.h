//
// Created by gamma on 2/21/2025.
//

#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>

#include "datastore.h"

#include <vector>


class MyDataStore : public DataStore{

public:

    ~MyDataStore() override;

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p) override;

    /**
     * Adds a user to the data store
     */
    void addUser(User* u) override;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile) override;

    User* getUserFromUsername(std::string username) const;


    std::vector<Product*> products;
    std::vector<User*> users;

    std::map<std::string, std::vector<Product*>> keywordMap;

};



#endif //MYDATASTORE_H
