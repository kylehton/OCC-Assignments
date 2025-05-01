# deque.py

# Implement a Deque data structure using a Python list

class Deque(object):
    def __init__(self, size):  # Constructor
        self.__maxSize = size  # Size of [circular] array
        self.__que = [None] * size  # Queue stored as a list
        self.__front = 1  # Empty Queue has front 1
        self.__rear = 0  # After rear and
        self.__nItems = 0  # No items in queue

    def insertRight(self, item):  # Insert item at rear of queue
        if self.isFull():  # If not full
            raise Exception("Queue overflow")
        self.__rear += 1  # Rear moves one to the right
        if self.__rear == self.__maxSize:  # Wrap around circular array
            self.__rear = 0
        self.__que[self.__rear] = item  # Store item at rear
        self.__nItems += 1
        return True
    
    def insertLeft(self, item):  # Insert item at front of queue
        if self.isFull():
            raise Exception("Queue overflow")
        self.__front -= 1  # Front moves one to the left
        if self.__front < 0:  # Wrap around circular array
            self.__front = self.__maxSize - 1
        self.__que[self.__front] = item  # Store item at front
        self.__nItems += 1
        return True

    def removeRight(self):  # Remove rear item of queue
        if self.isEmpty():
            raise Exception("Queue underflow")
        rear = self.__que[self.__rear]  # Get the value at rear
        self.__que[self.__rear] = None  # Remove item reference
        self.__rear -= 1  # Rear moves one to the left
        if self.__rear < 0:  # Wrap around circular array
            self.__rear = self.__maxSize - 1
        self.__nItems -= 1
        return rear

    def removeLeft(self):  # Remove left item of queue
        if self.isEmpty():  # And return it, if not empty
            raise Exception("Queue underflow")
        left = self.__que[self.__front]  # Get the value at front/left
        self.__que[self.__front] = None  # Remove item reference
        self.__front += 1  # Front moves one to the right
        if self.__front == self.__maxSize:  # Wrap around circular arr.
            self.__front = 0
        self.__nItems -= 1
        return left
    

    def peekLeft(self):  # Return frontmost item
        return None if self.isEmpty() else self.__que[self.__front]
    
    def peekRight(self):  # Return frontmost item
        return None if self.isEmpty() else self.__que[self.__rear]

    def isEmpty(self):
        return self.__nItems == 0

    def isFull(self):
        return self.__nItems == self.__maxSize

    def __len__(self):
        return self.__nItems

    def __str__(self):  # Convert queue to string
        ans = "["  # Start with left bracket
        for i in range(self.__nItems):  # Loop through current items
            if len(ans) > 1:  # Except next to left bracket,
                ans += ", "  # Separate items with comma
            j = i + self.__front  # Offset from front
            if j >= self.__maxSize:  # Wrap around circular array
                j -= self.__maxSize
            ans += str(self.__que[j])  # Add string form of item
        ans += "]"  # Close with right bracket
        return ans
