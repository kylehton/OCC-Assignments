#include <iostream>
#include <cmath>
using namespace std;

int numChickens(int startChickens, int numYears)
    {
        const double DEATH_RATE = 0.25;
        // each year, 1 chicken -> 10 chicks * 0.5 -> 5 chicks (chicks are then counted as chickens?)
        // 1/4 chickens die every year (rounded down, use integer div)
        int totalChickens = startChickens;
        for (int i = 0; i < numYears; i++)
        {
            // Calculate new chicks (10 per chicken) and keep half
            int newChicks = totalChickens * 10 / 2;
            
            // Calculate deaths (1/4 of current chickens, rounded down)
            int deaths = totalChickens / 4; // Integer division automatically rounds down
            
            // current + new chicks - deaths
            //totalChickens = totalChickens + newChicks - deaths;
            totalChickens += int(totalChickens * 10 / 2) - int(totalChickens * DEATH_RATE);
        }
        return totalChickens;
    };

int main() {

    cout << "3 chickens after 6 years: " << numChickens(3, 6) << endl;

}