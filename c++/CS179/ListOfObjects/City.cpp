#include <iostream>
#include <string>

using namespace std;

class City {

    private:
        string cityName;
        string cityAttraction;

    public:
        City(string name, string attraction) : cityName(name), cityAttraction(attraction) {}

        string getCityName() const {
            return cityName;
        }

        string getCityAttraction() const {
            return cityAttraction;
        }

        void displayCityDetails() const {
            cout << "WELCOME TO " << cityName << "\n" << "I HOPE YOU ENJOY THE " << cityAttraction << "!\n" << endl;
        }

};