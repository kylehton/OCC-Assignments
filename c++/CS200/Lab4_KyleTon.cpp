// Ton, Kyle

void BST::deleteItem(int itemToDelete)
{
    bool deletionComplete = false;
    
    if (root == nullptr) 
    {
        cerr << "Cannot delete from an empty tree." << endl;
        deletionComplete = true;
    }
    if (!deletionComplete && root->data == itemToDelete) 
    {
        // has no children
        if (root->llink == nullptr && root->rlink == nullptr) 
        {
            delete root;
            root = nullptr;
        }
        // has only right child
        else if (root->llink == nullptr) 
        {
            deleteNoLeftSubtree(root, nullptr);
        }
        // has only left child
        else if (root->rlink == nullptr) 
        {
            deleteNoRightSubtree(root, nullptr);
        }
        // has two children
        else 
        {
            deleteInternalNode(root);
        }
        deletionComplete = true;
        --totalNodes;
    }
     
    if (!deletionComplete) 
    {
        // search for the node to delete 
        Node* currentNode = root;
        Node* parentNode = nullptr;
        bool nodeFound = false;
         
        // find the node to delete and its parent
        while (currentNode != nullptr && !nodeFound) 
        {
            if (itemToDelete < currentNode->data) 
            {
                parentNode = currentNode;
                currentNode = currentNode->llink;
            } 
            else if (itemToDelete > currentNode->data) 
            {
                parentNode = currentNode;
                currentNode = currentNode->rlink;
            } 
            else 
            {
                nodeFound = true;
            }
        }
         
        // delete node if found
        if (nodeFound) 
        {
            // node to delete is a leaf
            if (currentNode->llink == nullptr && currentNode->rlink == nullptr) 
            {
                if (parentNode->llink == currentNode) 
                {
                    parentNode->llink = nullptr;
                } 
                else 
                {
                    parentNode->rlink = nullptr;
                }
                delete currentNode;
            }
            // node to delete has only right child
            else if (currentNode->llink == nullptr) 
            {
                deleteNoLeftSubtree(currentNode, parentNode);
            }
            // node to delete has only left child
            else if (currentNode->rlink == nullptr) 
            {
                deleteNoRightSubtree(currentNode, parentNode);
            }
            // node to delete has two children
            else 
            {
                deleteInternalNode(currentNode);
            }
            deletionComplete = true;
            --totalNodes;
        }
    }
    if (!deletionComplete)
    {
       cerr << "The item to delete is not in the tree." << endl;
    }
}