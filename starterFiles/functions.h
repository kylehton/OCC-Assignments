// Do not modify this file

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>


// Asks user for input using prompt
// until user enters positive number
double getInput(const std::string& prompt);

// converts inches to meters
double convertDistance(double inches);

// converts meters/second to miles/hour
double convertSpeed(double metersPerSec);

// determines velocity (meters/second) using the distance (in meters)
// and time (in seconds)
// velocity assumed to be constant
double getSpeed(double distance, double seconds);


#endif
