def identity(x): 
    return x  # Identity function

class Heap(object):
    def __init__(self, key=identity, size=2):  # Heap constructor
        self._arr = [None] * size  # Heap stored as a list/array
        self._nItems = 0  # No items in initial heap
        self._key = key  # Function to get key from heap item

    def isEmpty(self):
        return self._nItems == 0  # Test for empty heap

    def isFull(self):
        return self._nItems == len(self._arr)

    def __len__(self):
        return self._nItems  # Number of items

    def peek(self):  # Return item with maximum key
        return None if self.isEmpty() else self._arr[0]

    def parent(self, i):  # Get index of parent in heap tree
        return (i - 1) // 2  # Item i's parent index is half of i - 1

    def leftChild(self, i):  # Get index of left child in heap tree
        return i * 2 + 1  # Item i's left child is at twice i plus 1

    def rightChild(self, i):  # Get index of right child in heap tree
        return i * 2 + 2  # Item i's right child -> twice i plus 2

    def insert(self, item):  # Insert a new item in a heap
        if self.isFull():  # If insertion would go beyond array
            self._growHeap()  # then expand heap array
        self._arr[self._nItems] = item  # Store item at end of array
        self._nItems += 1  # Increase item count
        self._siftUp(self._nItems - 1)  # Sift last item up

    def _growHeap(self):  # Grow the array for the heap
        current = self._arr  # Store the current array
        self._arr = [None] * max(1, 2 * len(self._arr))  # Double array
        for i in range(self._nItems):  # Loop over all current items &
            self._arr[i] = current[i]  # copy them to the new array

    def _siftUp(self, i):  # Sift item i up toward root to preserve
        if i <= 0:  # heap condition. The root node, i = 0,
            return  # cannot go higher, so done.
        item = self._arr[i]  # Store item at cell i
        itemkey = self._key(item)  # and its key
        while 0 < i:  # While i is below the root
            parent = self.parent(i)  # Get the index of its parent node
            if (self._key(self._arr[parent]) <  # If parent's key is
                itemkey):  # less than that of item i,
                self._arr[i] = self._arr[parent]  # copy parent to i
                i = parent  # and continue up tree
            else:  # If parent's key is greater or equal,
                break  # then we have found where item i belongs
        self._arr[i] = item  # Move item i into final position

    def remove(self):  # Remove top item of heap and return it
        if self.isEmpty():  # It's an error if the heap is empty
            raise Exception("Heap underflow")
        root = self._arr[0]  # Store the top item
        self._nItems -= 1  # Decrease item count
        self._arr[0] = self._arr[self._nItems]  # Move last to root
        self._arr[self._nItems] = None  # Clear for garbage collection
        self._siftDown(0)  # Move last item down into position
        return root  # Return top item

    def _siftDown(self, i):  # Sift item i down to preserve heap cond.
        firstleaf = len(self) // 2  # Get index of first leaf
        if i >= firstleaf:  # If item i is at or below leaf level,
            return  # it cannot be moved down
        item = self._arr[i]  # Store item at cell i
        itemkey = self._key(item)  # and its key
        while i < firstleaf:  # While i above leaf level, find children
            left, right = self.leftChild(i), self.rightChild(i)
            maxi = left  # Assume left child has larger key
            if (right < len(self) and  # If both children are present, and
                self._key(self._arr[left]) <  # left child has smaller
                self._key(self._arr[right])):  # key
                maxi = right  # then use right child
            if (itemkey <  # If item i's key is less
                self._key(self._arr[maxi])):  # than max child's key,
                self._arr[i] = self._arr[maxi]  # then move max child up
                i = maxi
            else:  # If item i's key is greater than or equal
                break  # to larger child, then found position
        self._arr[i] = item  # Move item to its final position

    def traverse(self):  # Generator to step through all heap items
        for i in range(len(self)):  # Get each current item index
            yield self._arr[i]  # and yield the item at the index

    def print(self, indentBy=2, indent='', i=0):  # Print heap tree with root on left
        if i >= len(self):  # If item i is not in tree
            return  # don't print it
        next = indent + ' ' * indentBy
        self.print(indentBy,  # Print right subtree of i at next indent
                   next, self.rightChild(i))
        print(indent, self._arr[i])  # Print item i after indent, then
        self.print(indentBy,  # Print left subtree of i at next indent
                   next, self.leftChild(i))