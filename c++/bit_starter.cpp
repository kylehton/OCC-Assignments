// bit_starter
// This example shifts a 16 bit binary number to the left 
// effectively multiplying it by 4.  It then prints in binary and decimal

#include <iostream>
#include <bitset>
using namespace std;
unsigned short int myVal = 0b0000000000000001;
unsigned short int shiftedVal;


int main()
{
    // loop that runs twice to show wraparound
    for (int x = 0; x < 2; x++)
    {
        // loop that shifts the value to the left 16 times
        for (int i = 0; i < 15; i++)
        {
            cout << bitset<16>(myVal) << endl; // using bitset we can print the 16 bit value as a binary
            shiftedVal = (myVal << 1); //shift two positions to the left- note that this will multiply the value times 4.

            // check most significant bit using bitwise AND
            if (shiftedVal & 0b1000000000000000)
            {
                cout << bitset<16>(shiftedVal) << endl; // print the last instance of loop
                myVal = 0b0000000000000001; // reset to least significant bit
            }
            else
            {               
                myVal = shiftedVal; // set the value to the shifted value
            }
        }
    }
    return 0;
}