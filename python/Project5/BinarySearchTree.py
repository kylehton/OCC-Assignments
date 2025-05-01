class BinarySearchTree(object):    # A binary search tree class
    class _Node(object):           # A node in a binary search tree
        def __init__(
                self,
                key,                # Constructor takes a key that is
                data,               # used to determine the position
                left=None,          # inside the search tree,
                right=None):        # the data associated with the key
                                    # and a left and right child node
                                    # if known
            self.key = key          # Copy parameters to instance
            self.data = data        # attributes of the object
            self.leftChild = left
            self.rightChild = right
            
        def __str__(self):          # Represent a node as a string
            return "{" + str(self.key) + ", " + str(self.data) + "}"
    
    def __init__(self):             # The tree organizes nodes by their
        self.__root = None          # keys. Initially, it is empty.
    
    def isEmpty(self):              # Check for empty tree
        return self.__root is None
    
    def root(self):                 # Get the data and key of the root node
        if self.isEmpty():          # If the tree is empty, raise exception
            raise Exception("No root node in empty tree")
        return (                    # Otherwise return root data and its key
            self.__root.data, self.__root.key)
            
    def print(self,                 # Print the tree sideways with 1
              indentBy=4):          # node on each line and indenting each
                                    # level
        self.__pTree(self.__root,   # by some blanks. Start at root
                     "ROOT: ", "", indentBy) # node with no indent
    
    def __pTree(self,               # Recursively print a subtree,
                node,               # sideways
                nodeType,           # with the root node left justified
                                    # nodeType shows the relation to
                                    # its
                indent,             # parent and the indent shows its
                                    # level
                indentBy=4):        # Increase indent level for
                                    # subtrees
        if node:                    # Only print if there is a node
            self.__pTree(node.rightChild, "RIGHT: ", # Print the right
                         indent + " " * indentBy, indentBy) # subtree
            print(indent + nodeType, node) # Print this node
            self.__pTree(node.leftChild, "LEFT: ", # Print the left
                         indent + " " * indentBy, indentBy) # subtree
    
    def levels(self):               # Count the levels in the tree
        return self.__levels(self.__root) # Count starting at root
    
    def __levels(self, node):       # Recursively count levels in
                                    # subtree
        if node:                    # If a node is provided, then level
                                    # is 1
            return 1 + max(self.__levels(node.leftChild), # more than
                           self.__levels(node.rightChild)) # max child
        else: return 0              # Empty subtree has no levels
    
    def nodes(self):                # Count the tree nodes, using
                                    # iterator
        count = 0                   # Assume an empty tree
        for key, data in self.traverse(): # Iterate over all keys in any
            count += 1              # order and increment count
        return count
    
    def delete(self, goal):         # Delete a node whose key matches goal
        node, parent = self.__find(goal) # Find goal and its parent
        if node is not None:        # If node was found,
            return self.__delete(   # then perform deletion at node
                parent, node)       # under the parent
    
    def __delete(self,              # Delete the specified node in the tree
                 parent, node):     # modifying the parent node/tree
        deleted = node.data         # Save the data that's to be deleted
        if node.leftChild:          # Determine number of subtrees
            if node.rightChild:     # If both subtrees exist,
                self.__promote_successor( # Then promote successor to
                    node)           # replace deleted node
            else:                   # If no right child, move left child up
                if parent is self:  # If parent is the whole tree,
                    self.__root = node.leftChild # update root
                elif parent.leftChild is node: # If node is parent's left,
                    parent.leftChild = node.leftChild # child, update left
                else:               # else update right child
                    parent.rightChild = node.leftChild
        else:                       # No left child; so promote right child
            if parent is self:      # If parent is the whole tree,
                self.__root = node.rightChild # update root
            elif parent.leftChild is node: # If node is parent's left
                parent.leftChild = node.rightChild # child, then update
            else:                   # left child link else update
                parent.rightChild = node.rightChild # right child
        return deleted              # Return the deleted node's data
    
    def minNode(self):              # Find and return node with minimum key
        if self.isEmpty():          # If the tree is empty, raise exception
            raise Exception("No minimum node in empty tree")
        node = self.__root          # Start at root
        while node.leftChild:       # While node has a left child,
            node = node.leftChild   # follow left child reference
        return (node.key, node.data) # return final node key and data
    
    def maxNode(self):              # Find and return node with maximum key
        if self.isEmpty():
            raise Exception("No maximum node in empty tree")
        node = self.__root
        while node.rightChild:
            node = node.rightChild
        return (node.key, node.data)
    
    def inOrderTraverse(            # Visit all nodes of the tree in-
                                    # order
                self, function=print): # and apply a function to each
                                    # node
        self.__inOrderTraverse(     # Call recursive version starting
                                    # at
                self.__root, function=function) # root node
    
    def __inOrderTraverse(          # Visit a subtree in-order,
                                    # recursively
                self, node, function): # The subtree's root is node
        if node:                    # Check that this is real subtree
            self.__inOrderTraverse( # Traverse the left subtree
                node.leftChild, function)
            function(node)          # Visit this node
            self.__inOrderTraverse( # Traverse the right subtree
                node.rightChild, function)
    
    def __preOrderTraverse(self, node, function):
        if node:
            function(node)
            self.__preOrderTraverse(node.leftChild, function)
            self.__preOrderTraverse(node.rightChild, function)
    
    def __postOrderTraverse(self, node, function):
        if node:
            self.__postOrderTraverse(node.leftChild, function)
            self.__postOrderTraverse(node.rightChild, function)
            function(node)
    
    def insert(self,                # Insert a new node in a
                                    # binary
               key,                 # search tree finding where
                                    # its key
               data):               # places it and storing its
                                    # data
        node, parent = self.__find( # Try finding the key in the
                                    # tree
               key)                 # and getting its parent node
        if node:                    # If we find a node with this
                                    # key,
            node.data = data        # then update the node's data
            return False            # and return flag for no
                                    # insertion
    
        if parent is self:          # For empty trees, insert new
                                    # node at
            self.__root = self._Node(key, data) # root of tree
        elif key < parent.key:      # If new key is less than parent's
                                    # key,
            parent.leftChild = self._Node( # insert new node as left
                key, data)          # child of parent
        else:                       # Otherwise insert new node
                                    # as right
            parent.rightChild = self._Node( # child of parent
                key, data)
        return True                 # Return flag for valid
                                    # insertion
    
    def __find(self, goal):         # Find an internal node whose
                                    # key
        current = self.__root       # matches goal and its parent.
                                    # Start at
        parent = self               # root and track parent of
                                    # current node
    
        while (current and          # While there is a tree left to
                                    # explore
               goal != current.key): # and current key isn't the goal
            parent = current        # Prepare to move one level down
            current = (             # Advance current to left
                                    # subtree when
                current.leftChild if goal < current.key else # goal is
                current.rightChild) # less than current key, else
                                    # right
    
        # If the loop ended on a node, it must have the goal key
        return (current, parent)    # Return the node or None and
                                    # parent
    
    def search(self, goal):         # Public method to get data
                                    # associated
        node, p = self.__find(goal) # with a goal key. First, find
                                    # node
        return node.data if node else None # w/ goal & return any data
    
    def __promote_successor(self, node):
        """
        Helper method for delete operation when a node has two children.
        Finds the in-order successor (smallest node in right subtree),
        copies its key and data to the node to be deleted, and then
        deletes the successor.
        """
        # Find the successor (minimum node in right subtree)
        successor = node.rightChild
        successorParent = node
        
        # Find the leftmost node in the right subtree
        while successor.leftChild:
            successorParent = successor
            successor = successor.leftChild
        
        # Copy the successor's key and data to the node
        node.key = successor.key
        node.data = successor.data
        
        # Delete the successor - it has at most one child (right child)
        if successorParent is node:
            # If successor is direct right child of node
            successorParent.rightChild = successor.rightChild
        else:
            # If successor is deeper in the tree
            successorParent.leftChild = successor.rightChild
    
    def traverse(self, traverseType="in"):
        """
        Generator method to traverse the tree and yield key-data pairs.
        traverseType can be "in" for in-order, "pre" for pre-order, or "post" for post-order.
        """
        result = []
        
        def collect_nodes(node):
            result.append((node.key, node.data))
        
        if traverseType == "in":
            self.__inOrderTraverse(self.__root, collect_nodes)
            
        # Return the collected nodes as a generator
        for item in result:
            yield item
            
    def __iter__(self):
        """Make the tree iterable with a for loop, using in-order traversal by default."""
        return self.traverse()