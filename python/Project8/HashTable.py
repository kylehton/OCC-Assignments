def simpleHash(key):  # A simple hashing function
    if isinstance(key, int):  # Integers hash to themselves
        return key
    elif isinstance(key, str):  # Strings are hashed by letters
        return sum(
            256 ** i * ord(key[i])  # Multiply the code for each letter by 256^i
            for i in range(len(key))
        )
    elif isinstance(key, (list, tuple)):  # For sequences
        return sum(
            256 ** i * simpleHash(key[i])  # Recursively hash each element
            for i in range(len(key))
        )
    raise Exception(
        'Unable to hash key of type ' + str(type(key))  # Unknown type error
    )

def is_prime(n):  # Check if a number is prime
    if n <= 1:  # Numbers less than or equal to 1 are not prime
        return False
    for i in range(2, int(n**0.5) + 1):  # Check for factors from 2 to the square root of n
        if n % i == 0:  # If n is divisible by any i, it's not prime
            return False
    return True  # If no factors were found, n is prime

def linearProbe(start, key, size):
    for i in range(size):
        yield (start + i) % size

def quadraticProbe(start, key, size):
    for i in range(size):
        yield (start + i**2) % size

def doubleHashProbe(start, key, size):  # Generator to determine probe interval
    yield start % size                  # Yield the first cell index
    step = doubleHashStep(key, size)   # Get the step size for this key
    for i in range(1, size):           # Loop over all remaining cells using
        yield (start + i * step) % size  # step from second hash of key

def doubleHashStep(key, size):  # Determine step size for a given key
    prime = primeBelow(size)    # Find largest prime below array size
    return prime - (simpleHash(key) % prime)  # Step size is based on second hash and is in range [1, prime]

def primeBelow(n):  # Find the largest prime below n
    n -= 1 if n % 2 == 0 else 2  # Start with an odd number below n
    while (3 < n and not is_prime(n)):  # While n is bigger than 3 or is not prime, go to next odd number
        n -= 2
    return n  # Return prime number or 3




class HashTable(object):  # A hash table using open addressing
    def __init__(
        self, 
        size=7,                  # size of the table
        hash=simpleHash,         # a hashing function
        probe=linearProbe,       # the open address probe sequence
        maxLoadFactor=0.5        # the max load factor before growing
    ):
        self.__table = [None] * size        # Allocate empty hash table
        self.__nItems = 0                   # Track the count of items in the table
        self.__hash = hash                  # Store given hash function
        self.__probe = probe                # Store probe sequence generator
        self.__maxLoadFactor = maxLoadFactor

    def __len__(self):                      # The length of the hash table is
        return self.__nItems               # number of cells that have items

    def cells(self):                        # Get the size of the hash table in
        return len(self.__table)           # terms of the number of cells

    def hash(self, key):                    # Use the hashing function to get the
        return self.__hash(key) % self.cells()  # default cell index

    def search(self, key):  # Get the value associated with a key in the hash table, if any
        i = self.__find(key)  # Look for cell index matching key
        return (None if (i is None) or                     # If index not found,
                self.__table[i] is None or                 # item at i is empty or
                self.__table[i][0] != key                  # it has another key, return
                else self.__table[i][1])                   # None, else return item value

    __Deleted = (None, 'Deletion marker')  # Unique value for deletions

    def __find(self, key, deletedOK=False):  # Find the hash table index for a key
        # using open addressing probes. Find deleted cells if asked
        for i in self.__probe(self.hash(key), key, self.cells()):
            if (self.__table[i] is None or                      # If we find an empty cell or
                (self.__table[i] is HashTable.__Deleted and     # a deleted cell when one is sought or
                deletedOK) or
                self.__table[i][0] == key):                     # 1st of tuple matches key,
                return i                                        # then return index
        return None                                             # If probe ends, the key was not found

    def insert(self, key, value):  # Insert or update the value associated with a given key
        i = self.__find(key, deletedOK=True)  # Look for cell index matching key or an empty or deleted cell
        if i is None:  # If the probe sequence fails, then the hash table is full
            raise Exception('Hash table probe sequence failed on insert')

        if (self.__table[i] is None or              # If we found an empty cell, or
            self.__table[i] is HashTable.__Deleted):  # a deleted cell
            self.__table[i] = (key, value)          # then insert the new item there as a key-value pair
            self.__nItems += 1                      # and increment the item count
            if self.loadFactor() > self.__maxLoadFactor:  # When load factor exceeds limit, grow table
                self.__growTable()
            return True  # Return flag to indicate item inserted

        if self.__table[i][0] == key:         # If first of tuple matches key,
            self.__table[i] = (key, value)    # then update item
            return False                      # Return flag to indicate update

    def loadFactor(self):  # Get the load factor for the hash table
        return self.__nItems / len(self.__table)

    def __growTable(self):  # Grow the table to accommodate more items
        oldTable = self.__table  # Save old table
        size = len(oldTable) * 2 + 1  # Make new table at least 2 times bigger and a prime number of cells
        while not is_prime(size):  # Only consider odd sizes
            size += 2
        self.__table = [None] * size  # Allocate new table
        self.__nItems = 0             # Note that it is empty
        for i in range(len(oldTable)):  # Loop through old cells and insert non-deleted items by re-hashing
            if (oldTable[i] and oldTable[i] is not HashTable.__Deleted):
                self.insert(*oldTable[i])  # Call with (key, value) tuple

    def delete(self, key, ignoreMissing=False):  
        # Delete an item identified by its key from the hash table. Raise an exception
        # if not ignoring missing keys

        i = self.__find(key)  # Look for cell index matching key

        if (i is None or 
            self.__table[i] is None or 
            self.__table[i][0] != key):  # If the probe sequence fails or cell i is empty or it's not the item to delete
            if ignoreMissing:           # then item was not found. Ignore it if so directed
                return
            raise Exception(
                'Cannot delete key {} not found in hash table'.format(key))  # Otherwise raise an exception

        self.__table[i] = HashTable.__Deleted  # Mark table cell deleted
        self.__nItems -= 1                     # Reduce count of items

    def traverse(self):
        for i in range(len(self.__table)):
            if self.__table[i] is not None and self.__table[i] is not HashTable.__Deleted:
                yield self.__table[i]
