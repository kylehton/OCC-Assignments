class Link(object):  # One datum in a linked list
    def __init__(self, datum, next=None):  # Constructor
        self.__data = datum  # The datum for this link
        self.__next = next  # Reference to next Link

    def getData(self):  # Return the datum stored in this link
        return self.__data

    def setData(self, datum):  # Change the datum in this Link
        self.__data = datum

    def getNext(self): 
        return self.__next  # Return the next link

    def setNext(self, link):  # Change the next link to a new Link
        if link is None or isinstance(link, Link):  # Must be Link or None
            self.__next = link
        else:
            raise Exception("Next link must be Link or None")

    def isLast(self):  # Test if link is last in the chain
        return self.getNext() is None  # True if & only if no next Link

    def __str__(self):  # Make a string representation of link
        return str(self.getData())
