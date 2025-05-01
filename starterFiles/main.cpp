// Kyle Ton - CS A262 Discrete Structures - 02/09/2025

#include <iostream>
#include <string>
#include <iomanip>

#include "functions.h"

// include functions.cpp to avoid class namespace declaration
// more concise than including 'functions::', since no other
// classes are being used
#include "functions.cpp" 

using namespace std;

int main(){
  
  // prompts to gather distance between wires and time recorded for all 4 vehicles
  double distanceInInches = getInput("Enter the distance between the wires (inches): ");
  double timeCar1 = getInput("Enter time recorded (seconds): ");
  double timeCar2 = getInput("Enter time recorded (seconds): ");
  double timeCar3 = getInput("Enter time recorded (seconds): ");
  double timeCar4 = getInput("Enter time recorded (seconds): ");

  // output table headers with width formatting of 20 chars between each
  cout << "Vehicle" 
  << setw(20) << "Time (seconds)" 
  << setw(20) << "Speed (m/s)" 
  << setw(20) << "Speed (mph)" 
  << endl;

  // output data for car 1
  cout << fixed << setprecision(2) << right 
  << "1" 
  << setw(26) << timeCar1 // Time (seconds)
  << setw(20) << getSpeed(convertDistance(distanceInInches), timeCar1) // Speed (m/s)
  << setw(20) << convertSpeed(getSpeed(convertDistance(distanceInInches), timeCar1)) // Speed (mph)
  << endl;

  // output data for car 2
  cout << fixed << setprecision(2) << right 
  << "2" 
  << setw(26) << timeCar2 // Time (seconds)
  << setw(20) << getSpeed(convertDistance(distanceInInches), timeCar2) // Speed (m/s)
  << setw(20) << convertSpeed(getSpeed(convertDistance(distanceInInches), timeCar2)) // Speed (mph)
  << endl;

  // output data for car 3
  cout << fixed << setprecision(2) << right 
  << "3" 
  << setw(26) << timeCar3 // Time (seconds)
  << setw(20) << getSpeed(convertDistance(distanceInInches), timeCar3) // Speed (m/s)
  << setw(20) << convertSpeed(getSpeed(convertDistance(distanceInInches), timeCar3)) // Speed (mph)
  << endl;

  // output data for car 4
  cout << fixed << setprecision(2) << right 
  << "4" << setw(26) << timeCar4 // Time (seconds)
  << setw(20) << getSpeed(convertDistance(distanceInInches), timeCar4) // Speed (m/s)
  << setw(20) << convertSpeed(getSpeed(convertDistance(distanceInInches), timeCar4)) // Speed (mph)
  << endl;

  return 0;
}
