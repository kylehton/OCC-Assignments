# Test the BinarySearchTree class interactively
from BinarySearchTree import *

theTree = BinarySearchTree()       # Start with an empty tree

############################################################################# Balanced BST #############################################################################

mapOfNodes = {}

# uses a dict (hashmap) to store nodes and their respective data
mapOfNodes.update({"Don": "1974 1"})   
mapOfNodes.update({"Herb": "1975 2"})
mapOfNodes.update({"Ken": "1979 1"})
mapOfNodes.update({"Ivan": "1988 1"})
mapOfNodes.update({"Raj": "1994 1"})
mapOfNodes.update({"Amir": "1996 1"})
mapOfNodes.update({"Adi": "2002 3"})
mapOfNodes.update({"Ron": "2002 3"})
mapOfNodes.update({"Fran": "2006 1"})
mapOfNodes.update({"Vint": "2006 2"})
mapOfNodes.update({"Tim": "2016 1"})

# sorts keys in ascending order
sortedKeys = sorted(mapOfNodes.keys())

# recursive function to create a balanced binary search tree
def createRecursiveTree(min, max):
    # base case to end recursive loop
    if min > max:
        return
    # finds middle index and key for the current node
    mid = (min + max) // 2
    key = sortedKeys[mid]

    # inserts node and its values into BST
    theTree.insert(key, mapOfNodes[key])

    # recursively creates left and right subtrees
    createRecursiveTree(min, mid - 1)
    createRecursiveTree(mid + 1, max)

createRecursiveTree(0, len(sortedKeys) - 1)

########################################################################################################################################################################


def print_commands(names):       # Print a list of possible commands
    print('The possible commands are', names)

def clearTree():                 # Remove all the nodes in the tree
    while not theTree.isEmpty():
        key, data = theTree.root()
        theTree.delete(key)

def traverseTree(traverseType="in"):    # Traverse & print all nodes
    for key, data in theTree.traverse(traverseType):
        print('{', str(key), ', ', str(data), '}', end=' ')
    print()



commands = [  # Command names, functions, and their parameters
    ['print', theTree.print, []],
    ['insert', theTree.insert, ('key', 'data')],
    ['delete', theTree.delete, ('key', )],
    ['search', theTree.search, ('key', )],
    ['traverse', traverseTree, ('type', )],
    ['clear', clearTree, []],
    ['help', print_commands, []],
    ['?', print_commands, []],
    ['quit', None, []],
]

# Collect all the command names in a list
command_names = ", ".join(c[0] for c in commands)
for i in range(len(commands)):    # Put command names in argument list
    if commands[i][1] == print_commands:  # of print_commands
        commands[i][2] = [command_names]

# Create a dictionary mapping first character of command name to
# command specification (name, function, parameters/args)
command_dict = dict((c[0][0], c) for c in commands)

# Print information for interactive loop
theTree.print()
print_commands(command_names)
ans = ' '

# Loop to get a command from the user and execute it
while ans[0] != 'q':
    print('The tree has', theTree.nodes(), 'nodes across', 
          theTree.levels(), 'levels')
    ans = input("Enter first letter of command: ").lower()
    if len(ans) == 0:
        ans = ' '
    if ans[0] in command_dict:
        name, function, parameters = command_dict[ans[0]]
        if function is not None:
            print(name)
            if isinstance(parameters, list):
                arguments = parameters
            else:
                arguments = []
                for param in parameters:
                    arg = input("Enter " + param + " for " + name + " " +
                                "command: ")
                    arguments.append(arg)
            try:
                result = function(*arguments)
                print('Result:', result)
            except Exception as e:
                print('Exception occurred')
                print(e)
    else:
        print("Invalid command: '", ans, "'")