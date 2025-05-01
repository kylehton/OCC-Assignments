import Array
maxSize = 100
arr = Array.Array(maxSize)

arr.insert(77)
arr.insert(99)
arr.insert('foo')
arr.insert('bar')
arr.insert(44)
arr.insert(55)
arr.insert(12.34)
arr.insert(0)
arr.insert('baz')
arr.insert(-17)

print("Array containing", len(arr), "items:")
arr.traverse()

print("Search for 12 returns", arr.search(12))

print("Search for 12.34 returns", arr.search(12.34))

print("Deleting 0 returns", arr.delete(0))

print("Deleting 17 returns", arr.delete(17))

print("Setting item at index 3 to 33")
arr.set(3, 33)

print("Array after deletions has", len(arr), "items:")
arr.traverse()


#####################################################################################
# TEST CASE FOR REMOVE DUPLICATES FUNCTION
#####################################################################################

# Test case for random duplicate amount
duplicateTest1 = Array.Array(maxSize)
duplicateTest1.insert(1)
duplicateTest1.insert(2)
duplicateTest1.insert(3)
duplicateTest1.insert(1)
duplicateTest1.insert(2)
duplicateTest1.insert(3)
duplicateTest1.insert(4)
duplicateTest1.insert(5)
duplicateTest1.insert(5)
duplicateTest1.insert(5)
print("Removing duplicates [Test 1]:")
newArr1 = duplicateTest1.removeDupes()
newArr1.traverse()

# Test case for single element multi duplicates
duplicateTest2 = Array.Array(maxSize)
duplicateTest2.insert(1)
duplicateTest2.insert(1)
duplicateTest2.insert(1)
print("Removing duplicates [Test 2]:")
newArr2 = duplicateTest2.removeDupes()
newArr2.traverse()

# Edge case for no items or duplicates
duplicateTest3 = Array.Array(maxSize)
print("Removing duplicates [Test 3]:")
newArr3 = duplicateTest3.removeDupes()
newArr3.traverse()
