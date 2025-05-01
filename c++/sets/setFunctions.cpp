#include "setFunctions.h"
#include "set.h"
#include "set.cpp"

using namespace std;
// Returns a set that is the Union of the two sets s1 and s2
Set<char> setUnion(const Set<char>& s1, const Set<char>& s2)
{
	Set<char> result;

	// check whether element from s1 and/or s2 is in result
	// if not, add it to result using insertElement(char element)

	// iterate through set 1
	for (size_t i = 0; i < s1.cardinality(); i++)
	{
		if (!result.isElement(s1[i]))
			result.insertElement(s1[i]);
	}
	// iterate through set 2
	for (size_t i = 0; i < s2.cardinality(); i++)
	{
		if (!result.isElement(s2[i]))
			result.insertElement(s2[i]);
	}

	return result;
}

// Returns a set that is the intersection of the two sets s1 and s2
Set<char> setIntersection(const Set<char>& s1, const Set<char>& s2)
{
	Set<char> result;
	

	for (size_t i = 0; i < s1.cardinality(); i++)
	{
		if (s2.isElement(s1[i]))
			result.insertElement(s1[i]);
	}

	return result;
}

// Returns a set that is the s1 - s2
Set<char> setDiff(const Set<char>& s1, const Set<char>& s2)
{
	// create a set that is a copy of s1
	Set<char> result = s1;

	// loops through s2 to find elements that are in s1 and s2
	for (size_t i = 0; i < s2.cardinality(); i++)
	{
		// if an element from s2 is found in s1, it is removed from the result
		if (s1.isElement(s2[i]))
			result.removeElement(s2[i]);
	}

	return result;
}

// Returns a set that is the symmetric difference of the two sets s1 and s2
Set<char> setSymDiff(const Set<char>& s1, const Set<char>& s2)
{
	Set<char> result;

	// use setUnion and setDiff functions to find the symmetric difference
	result = setUnion(setDiff(s1, s2), setDiff(s2, s1));

	return result;
}

// Returns true if s1 is a subset of s2
bool isSubSet(const Set<char>& s1, const Set<char>& s2)
{
	// pre-check case handling
	if (s1.cardinality() > s2.cardinality())
		return false;

	// loops through s1 to find elements that are not in s2
	for (size_t i = 0; i < s1.cardinality(); i++)
	{
		// if an element from s1 is not found in s2, return false
		if (!s2.isElement(s1[i]))
			return false;
	}
	return true;
}

// Returns true if s1 is a proper subset of s2
bool isProperSubSet(const Set<char>& s1, const Set<char>& s2)
{
	// pre-check case handling
	if (s1.cardinality() >= s2.cardinality())
		return false;
	
	// loops through s1 to find elements that are not in s2
	for (size_t i = 0; i < s1.cardinality(); i++)
	{
		// if an element from s1 is not found in s2, return false
		if (!s2.isElement(s1[i]))
			return false;
	}
	return true;
}

// @Param ps: address of the Power Set
// @Param s: address of the Original Set
// @Param temp: address of the subset that is added to
// @Param len: length of the subset that is to be created
void createPowerSet(Set<Set<char>>& ps, Set<char> t, const Set<char>& s, unsigned int elem)
{
	cout << "recursive call" << endl;
	// base case where we have reached the last item to be added (cannot add anymore)
	if (elem == s.cardinality()-1)
	{
		// insert equal subset in Power Set
		ps.insertElement(s);
		return;
	}

	// recursive case where we add elements to the subset
	// loop through items in s
	for (size_t i = elem; i < s.cardinality(); i++)
	{
		Set<char> temp = t;
		temp.insertElement(s[i]);
		ps.insertElement(temp);
			createPowerSet(ps, temp, s, elem+1);
		
	}
}

// Returns the Power Set of set s as a set of sets
Set<Set<char>> PowerSet(const Set<char>& s)
{
	Set<Set<char>> result;
	// add the empty set to the Power Set
	result.insertElement(Set<char>()); 
	Set<char> temp;
	// call createSubset to create the Power Set
	createPowerSet(result, temp, s, 0);
	return result;
}

// Returns true if the sets in p make up a Partition of set s
bool isPartition(const Set<Set<char>>& p, const Set<char>& s)
{
	// empty sets and equal sets/subsets are not partitions of themselves
	if (p.cardinality() == 0 || p.cardinality() == 1)
	{
		return false;
	}
	// go through each set in p and check if it is mutually disjoint and if the union of all sets in p is equal to s

	// start with the first set in p
	Set<char> unionSet;
	for (size_t i = 0; i < p.cardinality(); i++)
	{
		// check if set is not empty
		if (p[i].cardinality() == 0)
		{
			return false;
		}

		// check if sets are mutually disjoint
		if (setIntersection(p[i], unionSet).cardinality() != 0)
		{	
			return false;
		}
		
		// if so, add the set to the unionSet
		unionSet = setUnion(unionSet, p[i]);
	}

	// checking if the union of all sets in p is equal to s
	if (setSymDiff(s, unionSet).cardinality())
	{
		return false;
	}
	
	return true;
}