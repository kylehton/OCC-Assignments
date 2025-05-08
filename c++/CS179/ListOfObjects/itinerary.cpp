// itinerary.cpp : using the STL list
// // Imagine you are visiting France and have an intinerary for your visit
#include <iostream>
#include <list>
#include <algorithm>
#include "City.cpp"

using namespace std;
    int main()
    {
        string city = "unknown"; // used for user input

        // set up a list of strings
        list<City> my_it;
        my_it.push_back(City("Paris", "Eiffel Tower"));
        my_it.push_back(City("Lyon", "Basilica of Notre-Dame de Fourvière"));
        my_it.push_back(City("Marseilles", "Calanques National Park"));
        my_it.push_back(City("Toulouse", "Cité de l'Espace"));
        my_it.push_back(City("Bordeaux", "La Cité du Vin"));
        my_it.push_back(City("Nice", "Promenade des Anglais"));
        my_it.push_back(City("Strasbourg", "Strasbourg Cathedral"));
        my_it.push_back(City("Lille", "Palais des Beaux-Arts"));
        my_it.push_back(City("Nantes", "Les Machines de l'île"));
        my_it.push_back(City("Montpellier", "Place de la Comédie"));

        // an iterator to point to a location
        auto marker = my_it.begin();
        cout << "\nMy Itinerary:\n\n";

        for (auto it = my_it.begin(); it != my_it.end(); it++) {
            cout << it->getCityName() << endl;
        }

        // You want to add another city before Marseilles, set our marker to find Marseilles
        marker = find_if(my_it.begin(), my_it.end(), [](const City& c) { 
            return c.getCityName() == "Marseilles"; 
        });
        
        // Get a new city from the user
        cout << "\nYou have time to add another city before Marseilles, What city would you like to add? ";
        cin >> city;        
        cout << "What would you like to see in " << city << "? ";
        string attraction;
        cin >> attraction;


        // insert the city
        my_it.insert(marker, City(city, attraction));

        // print out the new itinerary.
        cout << "\nMy new Itinerary:\n\n";
        for (auto it = my_it.begin(); it != my_it.end(); it++) {
            cout << it->getCityName() << endl;
        }

        cout << "Starting your trip...\n";
        // iterate through the list and display the details of each city
        for (auto it = my_it.begin(); it != my_it.end(); it++) {
            it->displayCityDetails();
        }
        cout << "Your trip is over.\n";
        cout << "Thank you for using the itinerary program.\n";
        return 0;
    }