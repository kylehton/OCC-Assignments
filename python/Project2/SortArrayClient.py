# Listing 3-5: The SortArrayClient.py program
from SortArray import *
import random
import time

def initArray(size=100, maxValue=100, seed=3.14159):
    """Create an Array of the specified size with a fixed sequence of
    'random' elements"""
    arr = Array(size)  # Create the Array object
    random.seed(seed)  # Set random number generator
                       # to known state, then loop
    for i in range(size):
        arr.insert(random.randrange(maxValue))  # Insert random numbers
    return arr  # Return the filled Array

arr = initArray()
print("Array containing", len(arr), "items:\n", arr)

for test in ['initArray().bubbleSort()', 
            'initArray().selectionSort()',
            'initArray().insertionSort()']:
    elapsed = time.time()
    exec(test, globals(), globals())
    print(test, "took", elapsed, "seconds", flush=True)
    
arr.insertionSort()
print('Sorted array contains:\n', arr)

median = arr.median()
print('Median is', median)