#include <iostream>
#include <cmath>
#include <vector>
#include "set.h"
#include "set.cpp"
#include "setFunctions.h"

using namespace std;

int main()
{
	vector<char> v{'s','f','h','i','a','h'};
	Set<char> s1{ 's','f','g','h','h','i','a', 'b' };
	Set<char> s2{ 'e','d','a','g','b','h','i','a','h' };
	Set<char> s3{ 'a','b','c','d','e','f' };
	Set<char> s4{ 'a','b','c' };
	Set<char> s5{ 'd','e','f','g' };

	Set<char> s6{ 'a','b','c','d','e' };

	Set<Set<char>> ss{ s4,s5 };  // Set of Sets s4 and s5

	cout << boolalpha;   // makes the printing of a boolean print true or false instead of 1 or 0

	cout << "\nThe power set P(s4)\n";
    Set<Set<char>> ps4 = PowerSet(s4);
	cout << ps4 << endl;
	cout << "Expected Cardinality of P(s4): " << pow(2, s4.cardinality()) << endl;
	cout << "Result Cardinality of P(s4): " << ps4.cardinality() << endl;
	


	cout << "\nThe power set P(s6)\n";
    Set<Set<char>> ps6 = PowerSet(s6);
	cout << ps6 << endl;
    	cout << "Expected Cardinality of P(s6): " << pow(2, s6.cardinality()) << endl;
	cout << "Result Cardinality of P(s6): " << ps6.cardinality() << endl;



	return 0;
}