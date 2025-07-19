#include <iostream>
using namespace std;

const int LIMIT = 5;

// Part 1
int hashValue(int key, int j, int capacity) 
{
   // note: add j^2 since quadratic, not linear probing
   return ((3 * key) + 3 + (j * j)) % capacity;
}

// Part 2
void insertKey(int table[], const int capacity, int& numElements, const int key) 
{
   int j = 0;
   bool isInserted = false;
   bool hasDuplicate = false;
   int curIndex = 0;
   while ((j < LIMIT) && (!isInserted) && (!hasDuplicate))
   {
      curIndex = hashValue(key, j, capacity);
      // Values for empty (0) or previous deleted (-2)
      if ((table[curIndex] == 0) || (table[curIndex] == -2))
      {
         isInserted = true;
         table[curIndex] = key;
         ++numElements;
      }
      else if (table[curIndex] == key)
      {
         cerr << "Key " << key << " is a duplicate." << endl;
         hasDuplicate = true;
      }
      else
      {
         ++j;
      }
   }
   if ((!isInserted) && (!hasDuplicate))
   {
      cout << "Key " << key << " not inserted. Need to rehash." << endl;
   }
}


// Part 3
bool searchKey(const int table[], const int capacity, const int key)
{
   int j = 0;
   int index = 0;
   while (j < LIMIT)
   {
      index = hashValue(key, j, capacity);
      if (table[index] == 0)
      {
         return false;
      }
      else if (table[index] == key)
      {
         return true;
      }
      else
      {
         ++j;
      }
   }
   return false;
}


// Part 4
void deleteKey(int table[], const int capacity, int& numElements, const int key)
{
   int j = 0;
   int index = 0;
   bool deleted = false;
   while ((!deleted) && (j < LIMIT))
   {
      index = hashValue(key, j, capacity);
      
      if (table[index] == key)
      {
         table[index] = -2;
         --numElements;
         deleted = true;
      }
      else
      {
         ++j;
      }
   }
   if (!deleted)
   {
      cout << "Key " << key << " is not in the table." << endl;
   }
}