#ifndef SET_FUNC_H
#define SET_FUNC_H

#include "set.h"


Set<char> setUnion(const Set<char>& s1, const Set<char>& s2);         // The union of s1 and s2 -> return

Set<char> setIntersection(const Set<char>& s1, const Set<char>& s2);  // The intersection of s1 and s2 -> return

Set<char> setDiff(const Set<char>& s1, const Set<char>& s2);          // The Difference , s1 - s2 -> return
 
Set<char> setSymDiff(const Set<char>& s1, const Set<char>& s2);       // The symetric Difference of s1 and s2 -> return

bool isSubSet(const Set<char>& s1, const Set<char>& s2);              // True if s1 is a subset of s2

bool isProperSubSet(const Set<char>& s1, const Set<char>& s2);        // True if s1 is a proper subset of s2

Set<Set<char>> PowerSet(const Set<char>& s);                        // The Power Set of s  -> P(s)

bool isPartition(const Set<Set<char>>& p, const Set<char>& s);  // True if the sets in p are a partition of set s

#endif
