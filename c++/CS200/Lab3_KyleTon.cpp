// Ton, Kyle

// Part 1:
   // instantiate added node
   Node *nodeToInsert = new Node();
   nodeToInsert->data = elemToInsert;
   
   // Empty node edge case
   if (!root)
   {
      root = nodeToInsert;
      count++;
   }
   else
   {
      Node *curr = root;
      Node *prev = nullptr;
      bool hasDuplicate = false;
   
      while (!hasDuplicate && (curr != nullptr))
      {
         // check for equality
         if (curr->data == elemToInsert)
         {
            cerr << "Element " << elemToInsert << " is already in the list. Duplicates are not allowed." << endl;
            hasDuplicate = !hasDuplicate;
         }
         else if (curr->data < elemToInsert)
         {
            prev = curr;
            curr = curr->rlink;
         }
         else
         {
            prev = curr;
            curr = curr->llink;
         }
      }
      
      if (!hasDuplicate)
      {
         // add in node (which should have no children)
         if (prev->data > elemToInsert)
         {
            prev->llink = nodeToInsert;
         }
         else
         {
            prev->rlink = nodeToInsert;
         }
         count++;
      }
   }


// Part 2:
    void BST::nonRecursiveInorder() const
    {
    stack<Node*> nodeStack;
    Node* curr = root;

    while ((curr != nullptr) || !nodeStack.empty())
    {
        //move as far down left as possible per parent node
        while (curr != nullptr)
        {
            nodeStack.push(curr);
            curr = curr->llink;
        }
        // go back up
        curr = nodeStack.top();
        nodeStack.pop();
        
        //print node
        cout << curr->data << " ";
        
        // move to right subtree
        curr = curr->rlink;
    }
    cout << endl;
    }

