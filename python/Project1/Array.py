class Array(object):

    def __init__(self, initialSize):
        self.__a = [None] * initialSize
        self.__nItems = 0

    def __len__(self):
        return self.__nItems
    
    def get(self, n):
        if 0 <= n and n < self.__nItems:
            return self.__a[n]
        
    def set(self, n, value):
        if 0 <= n and n < self.__nItems:
            self.__a[n] = value

    def insert(self, item):
        self.__a[self.__nItems] = item
        self.__nItems += 1

    def find(self, item):
        for j in range(self.__nItems):
            if self.__a[j] == item:
                return j
        return -1
    
    def search(self, item):
        return self.get(self.find(item))
    
    def delete(self, item):
        for j in range(self.__nItems):
            if self.__a[j] == item:
                for k in range(j, self.__nItems - 1):
                    self.__a[k] = self.__a[k + 1]

                # textbook made an error placing this above the nested for loop
                self.__nItems -= 1
                return True
        return False
    
    def traverse(self,function=print):
        for j in range(self.__nItems):
            function(self.__a[j])


    def removeDupes(self):
        # creates new array for storage of unique values
        newArr = Array(len(self))
        # loops through the array and inserts unique values
        for i in range(len(self)):
            # checks for duplicate values before inserting
            if newArr.find(self.get(i)) == -1:
                # if unique, insert into new array
                newArr.insert(self.get(i))
        return newArr
    
    '''
    # alternate removeDupes function that uses sets to remove duplicates
    def removeDupes(self):
        # since order doesnt matter, we can convert the list to a set
        self.__a = set(self.__a)
        # converts set back to list to return to [] rather than {}
        self.__a = list(self.__a)
        return self.__a
    '''