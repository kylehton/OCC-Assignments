from LinkedList import LinkedList
from Link import Link

def main():

    ##### LINKED LIST CREATION #####
    link1 = Link(1)
    link2 = Link(2)
    link3 = Link(3)

    link1.setNext(link2)
    link2.setNext(link3)

    linkedList = LinkedList()

    linkedList.setFirst(link1)
    

    ##### TRAVERSAL FUNCTION TESTING #####
    print("\n ---------- TESTING BEGINNING ---------- \n")

    print("Traversing the linked list:")
    linkedList.traverse()  # Should print 1 > 2 > 3

    ##### LEN FUNCTION TESTING #####
    print("\nLength of linked list:", len(linkedList))  # Should print 3

    ##### STR FUNCTION TESTING #####
    print("\nString representation of linked list:", str(linkedList))  # Should print [1 > 2 > 3]

    print("\n ---------- TESTING COMPLETE ---------- \n")

if __name__ == "__main__":
    main()