from HashTable import HashTable

hTable = HashTable()

for line in open('Hamlet_2B_or_not_2B.txt', 'r', encoding='windows-1252'):
    for word in line.split():
        word = word.strip('()<>[]{}-_,.!?:;`\'')
        if hTable.search(word) is None:
            hTable.insert(word, 1)
        else:
            hTable.insert(word, hTable.search(word) + 1)

for item in hTable.traverse():
    print(item[0], "-", item[1])