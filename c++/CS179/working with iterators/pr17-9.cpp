#include <iostream>
#include <vector>
#include "Product.h"
using namespace std;

int main() {
    // Create a vector to hold Products.
    vector<Product> products;

    // Add Products to the vector.
    products.emplace_back("T-Shirt", 20);
    products.emplace_back("Calendar", 25);
    products.emplace_back("Coffee Mug", 30);

    // Use an iterator to display the vector contents.

    auto ite = products.begin() + 2; // iterator starting at index 2 (position 3)

    products.emplace(ite, "Matcha", 5); // adding a new product at position 3, moving everything else down 1


    for (auto it = products.end()-1; it != products.begin()-1; it--) {
        cout << "Product: " << it->getName() << endl
             << "Units: " << it->getUnits() << endl;
    }

    /*
    Should print:

    Product: Coffee Mug
    Units: 30
    Product: Matcha
    Units: 5
    Product: Calendar
    Units: 25 
    Product: T-Shirt
    Units: 20
    */

    return 0;
}
