from Deque import Deque

def main():
    ##### Basic Function Testing #####
    deque1 = Deque(5)  # Create a deque of size 5

    deque1.insertLeft(3)
    deque1.insertLeft(2)
    deque1.insertLeft(1)
    deque1.insertRight(4)
    deque1.insertRight(5)

    print("Deque after insertions:", str(deque1))

    print("\n__________ PEEK CASE TESTING __________\n")
    print("Peek Left:", deque1.peekLeft())  # Should return 1
    print("Peek Right:", deque1.peekRight())  # Should return 5

    print("\n__________ REMOVAL CASE TESTING __________\n")
    print("Remove Left:", deque1.removeLeft())  # Should return 1
    print("Deque after removing left:", str(deque1))
    print("Remove Right:", deque1.removeRight())  # Should return 5
    print("Deque after removing right:", str(deque1))

    ##### Wrap-Around Case Testing #####
    
    print("\n__________ WRAP-AROUND CASE TESTING __________\n")

    wrapDeque = Deque(4)
    wrapDeque.insertRight(1)  # rear becomes 1
    wrapDeque.insertRight(2)  # rear becomes 2
    wrapDeque.insertRight(3)  # rear becomes 3
    print("Initial wrap-around deque", str(wrapDeque))
    
    print("Removing Left x2:", str(wrapDeque))
    wrapDeque.removeLeft()     # front becomes 2, nItems = 2
    wrapDeque.removeLeft()     # front becomes 3, nItems = 1
        
    print("Inserting 4 and 5 into right:", str(wrapDeque))
    wrapDeque.insertRight(4)  # rear becomes 0 (wraparound!), nItems = 2
    wrapDeque.insertRight(5)  # rear becomes 1, nItems = 3

    print("Deque after wraparound:", str(wrapDeque))

    ##### Exception Case Testing #####

    print("\n__________ EXCEPTION CASE TESTING __________\n")
    exceptDeque = Deque(3)
    exceptDeque.insertLeft(1)
    exceptDeque.insertRight(2)
    exceptDeque.insertLeft(2)
    print("Current Exception Deque:", str(exceptDeque))

    try:
        print("Inserting past size: Exception should occur (overflow)")
        exceptDeque.insertRight(3)  # should have an exception here
        print(str(exceptDeque))
    except Exception as e:
        print("Exception caught:", e)

    emptyDeque = Deque(2)
    print("\nTrying to remove from an empty deque:", str(emptyDeque))
    print(emptyDeque.peekRight())  # Should return None without raising an exception

    try:
        print("Removing left from empty queue: Exception should occur (underflow)")
        print(emptyDeque.removeLeft())  # Should raise an exception
    except Exception as e:
        print("Exception caught:", e)

    print("\n__________ ALL TESTS COMPLETED __________\n")


if __name__ == "__main__":
    main()