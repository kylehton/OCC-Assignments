#include <iostream>

#include "functions.h"
#include "functions.cpp"

using namespace std;


// This file contains sample tests to test your functions. These tests
// are not exhaustive; you should supplement with your own tests
int main(){
  // getInput
  cout << "getInput" << endl;
  double res = getInput("Enter -3, -6, 5.5: ");
  cout << "Expected 5.5" << endl;
  cout << "Actual: " << res << endl;
  cout << endl << endl;

  // convertDistance
  cout << "10 inches should be 0.25 meters" << endl;
  cout << "\t--> Actual : " << convertDistance(10) << endl;

  cout << "36.5 inches should be 0.9125 meters" << endl;
  cout << "\t--> Actual : " << convertDistance(36.5) << endl;

    
  // convertSpeed
  cout << "100 meters/second should be 223.7 mph" << endl;
  cout << "\t--> Actual : " << convertSpeed(100) << endl;

  cout << "20.4 meters/second should be 45.63 mph" << endl;
  cout << "\t--> Actual : " << convertSpeed(20.4) << endl;
  
  
  // getSpeed
  cout << "Moving 1 m in 1 second should be 1.0 m/s" << endl;
  cout << "\t--> Actual: " << getSpeed(1, 1) << endl;

  cout << "Moving 30 m in 15 seconds should be 2.0 m/s" << endl;
  cout << "\t--> Actual: " << getSpeed(30, 15) << endl;

  cout << "Moving 922.5 m in 20.5 seconds should be 45 m/s" << endl;
  cout << "\t--> Actual: " << getSpeed(922.5, 20.5) << endl;
    
  return 0;
}
