# Implement a sortable Array data structure

class Array(object):
    def __init__(self, initialSize):  # Constructor
        self._a = [None] * initialSize  # The array stored as a list
        self._nItems = 0  # No items in array initially
        
    def __len__(self):  # Special def for len() func
        return self._nItems  # Return number of items
        
    def get(self, n):  # Return the value at index n
        if 0 <= n and n < self._nItems:  # Check if n is in bounds, and
            return self._a[n]  # only return item if in bounds
            
    def set(self, n, value):  # Set the value at index n
        if 0 <= n and n < self._nItems:  # Check if n is in bounds, and
            self._a[n] = value  # only set item if in bounds
            
    def swap(self, j, k):  # Swap the values at 2 indices
        if (0 <= j and j < self._nItems and  # Check if indices are in
            0 <= k and k < self._nItems):  # bounds, before processing
            self._a[j], self._a[k] = self._a[k], self._a[j]
            
    def insert(self, item):  # Insert item at end
        if self._nItems >= len(self._a):  # If array is full,
            raise Exception("Array overflow")  # raise exception
        self._a[self._nItems] = item  # Item goes at current end
        self._nItems += 1  # Increment number of items
        
    def find(self, item):  # Find index for item
        for j in range(self._nItems):  # Among current items
            if self._a[j] == item:  # If found,
                return j  # then return index to element
        return -1  # Not found -> return -1
        
    def search(self, item):  # Search for item
        return self.get(self.find(item))  # and return item if found
        
    def delete(self, item):  # Delete first occurrence
        for j in range(self._nItems):  # of an item
            if self._a[j] == item:  # Found item
                self._nItems -= 1  # One fewer at end
                for k in range(j, self._nItems):  # Move items from
                    self._a[k] = self._a[k+1]  # right over 1
                return True  # Made it here, so couldn't find the item
        return False
        
    def traverse(self, function=print):  # Traverse all items
        for j in range(self._nItems):  # and apply a function
            function(self._a[j])
            
    def __str__(self):  # Special def for str() func
        ans = "["  # Surround with square brackets
        for i in range(self._nItems):  # Loop through items
            if len(ans) > 1:  # Except next to left bracket,
                ans += ", "  # separate items with comma
            ans += str(self._a[i])  # Add string form of item
        ans += "]"  # Close with right bracket
        return ans
        
    def bubbleSort(self):  # Sort comparing adjacent vals
        for last in range(self._nItems-1, 0, -1):  # and bubble largest to end
            for inner in range(last):  # Inner loop goes up to last
                if self._a[inner] > self._a[inner+1]:  # If elem less
                    self.swap(inner, inner+1)  # than adjacent value, swap
                    
    def selectionSort(self):  # Sort by selecting min and
        for outer in range(self._nItems-1):  # swapping min to leftmost
            min = outer  # Assume min is leftmost
            for inner in range(outer+1, self._nItems):  # Hunt to right
                if self._a[inner] < self._a[min]:  # If we find new min
                    min = inner  # update the min index
            # _a[min] is smallest among _a[outer]..._a[nItems-1]
            self.swap(outer, min)  # Swap leftmost and min
            
    def insertionSort(self):  # Sort by repeated inserts
        for outer in range(1, self._nItems):  # Mark one element
            temp = self._a[outer]  # Store marked item in temp
            inner = outer  # Inner loop starts at mark
            while inner > 0 and temp < self._a[inner-1]:  # If marked item
                self._a[inner] = self._a[inner-1]  # smaller than
                inner -= 1  # Shift item to right
            self._a[inner] = temp  # Move marked item to 'hole'

    def median(self):
        """Return the median value of the Array"""
        if self._nItems == 0: # checks whether the array has anything in it
            return ("Array is empty")
        else:
            return self.get(self._nItems // 2) # returns the middle value of the array


