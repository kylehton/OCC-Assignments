#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

class Product {
private:
    string name;
    int units;

public:
    // Constructor
    Product(string n, int u) {
        name = n;
        units = u;
    }

    // Setters
    void setName(string n) {
        name = n;
    }

    void setUnits(int u) {
        units = u;
    }

    // Getters
    string getName() const {
        return name;
    }

    int getUnits() const {
        return units;
    }
};

#endif
