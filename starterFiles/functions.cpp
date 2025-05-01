// Put your name here
#include "functions.h"

#include <iostream>
#include <iomanip>

using namespace std;

// Const global variables for conversion through mutliplying against
// pre-conversion unit (left-most unit in variable name)
const double INCH_TO_METER = 0.025; // 1 inch = 0.025 meters
const double METER_IN_MILE = 1/1609.0; // 1 meter = 1/1609 miles
const double SEC_IN_HOUR = 3600.0; // 3600 second = 1/ hour

    // gets input for time in seconds as a string, then returns it as a double
    double getInput(const std::string& prompt)
    {
        double input; // variable to store input (double for seconds and partials)

        // prints the original iteration of prompt and input
        cout << prompt; 
        cin >> input;

        // while loop to ensure input is positive
        while (input <= 0)
        {
            cout << prompt;
            cin >> input;
        }
        return input;
    }

    // converts inches to meters
    double convertDistance(double inches)
    {
        //multiply inches by conversion factor to get meters
        return (inches * INCH_TO_METER);
    }

    // converts meters/second to miles/hour
    double convertSpeed(double metersPerSec)
    {
        //multiply by meters->mile conversion factor to get miles/second
        // then by sec->hour conversion factor to get miles/hour
        return (metersPerSec * SEC_IN_HOUR * METER_IN_MILE);
    }

    // determines velocity (meters/second) using the distance (in meters)
    // and time (in seconds)
    // velocity assumed to be constant
    double getSpeed(double distance, double seconds)
    {
        //divide distance by time to get velocity
        return (distance / seconds);
    }

