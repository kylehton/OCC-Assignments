from Link import Link

class LinkedList(object):  # A linked list of data elements

    def __init__(self):  # Constructor
        self.__first = None  # Reference to first Link

    def getFirst(self): 
        return self.__first  # Return the first link

    def setFirst(self, link):  # Change the first link to a new Link
        if link is None or isinstance(link, Link):  # It must be None or a Link object
            self.__first = link
        else:
            raise Exception("First link must be Link or None")

    def getNext(self): 
        return self.getFirst()  # First link is next

    def setNext(self, link): 
        self.setFirst(link)  # First link is next

    def isEmpty(self):  # Test for empty list
        return self.getFirst() is None  # True iff no first Link

    def first(self):  # Return the first item in the list
        if self.isEmpty():  # as long as it is not empty
            raise Exception('No first item in empty list')
        return self.getFirst().getData()  # Return data item (not Link)



    def traverse(self, func=print):  # Apply a function to all items in list
        listIteration = iter(self)  # Create an iterator for the list
        for item in listIteration:
            func(item)

    def __len__(self):  # Get length of list
        l = 0
        listIteration = iter(self)  # Start with first link
        for iteration in listIteration:  # Keep going until no more links
            l += 1  # Count iteration in list
        return l

    def __str__(self):  # Build a string representation
        result = "["  # Enclose list in square brackets
        listIteration = iter(self)  # Start with first link
        for iteration in listIteration:  # Keep going until no more links
            if len(result) > 1:  # After first link,
                result += " > "  # separate links with right arrowhead
            result += str(iteration)  # Append string version of link
        return result + "]"  # Close with square bracket

    def __iter__(self):
        next = self.getFirst()
        while next is not None:
            yield next.getData()
            next = next.getNext()