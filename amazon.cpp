#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <queue>

#include "product.h"
#include "db_parser.h"
#include "mydatastore.h"
#include "product_parser.h"
#include "util.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    map<User*, vector<Product*>> CartMap;

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if (cmd == "ADD") {

                string username;
                int hitNumber;

                ss >> username;
                ss >> hitNumber;

                if (!ss) {
                    cout << "Invalid request" << endl;
                    continue;
                }

                User* u = ds.getUserFromUsername(username);

                if (!u) {
                    cout << "Invalid request" << endl;
                    continue;
                }

                std::pair<map<User*, vector<Product*>>::iterator, bool> cartPair = CartMap.emplace(u, vector<Product*>{});
                map<User*, vector<Product*>>::iterator cart = cartPair.first;

                cart->second.push_back(hits[hitNumber - 1]);

            }else if (cmd == "VIEWCART") {
                string username;

                ss >> username;

                if (!ss) {
                    cout << "Invalid username" << endl;
                    continue;
                }

                User* u = ds.getUserFromUsername(username);

                if (!u) {
                    cout << "Invalid username" << endl;
                    continue;
                }

                pair<map<User*, vector<Product*>>::iterator, bool> cartPair = CartMap.emplace(u, vector<Product*>{});
                map<User*, vector<Product*>>::iterator cart = cartPair.first;


                int index = 1;
                for(vector<Product*>::iterator it = cart->second.begin(); it != cart->second.end(); ++it) {
                    cout << "Item " << setw(3) << index << endl;
                    cout << (*it)->displayString() << endl;
                    cout << endl;
                    index++;
                }

                // displayProducts(cart->second);


            }else if (cmd == "BUYCART") {
                string username;

                ss >> username;

                if (!ss) {
                    cout << "Invalid username" << endl;
                    continue;
                }

                User* u = ds.getUserFromUsername(username);

                if (!u) {
                    cout << "Invalid username" << endl;
                    continue;
                }

                vector<Product*> cart = CartMap.emplace(u, vector<Product*>{}).first->second;

                vector<Product*> newCart;


                for (vector<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) {
                    Product* p = *it;

                    if (p->getQty() > 0 && u->getBalance() >= p->getPrice()){
                        p->subtractQty(1);
                        u->deductAmount(p->getPrice());
                    }else {
                        newCart.push_back(*it);
                    }
                }

                CartMap[u] = newCart;






            }
#ifdef DEBUG
            //list all the products
            else if (cmd == "LISTPRODUCTS") {
                displayProducts(ds.products);
            }
#endif




            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
