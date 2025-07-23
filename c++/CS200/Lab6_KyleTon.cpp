// Ton, Kyle

// Part 1
void iterSwapStacks(stack<int>& stack1, stack<int>& stack2) 
{
    int size = stack1.size() - 1;  
    int tempElement;

    while (size > 0)
    {
        // move size-1 elements from stack1 to stack2
        for (int i = 0; i < size; i++)
        {
            stack2.push(stack1.top());
            stack1.pop();
        }

        //stack1 should have a single element left
        tempElement = stack1.top();
        stack1.pop();

        // move back to stack1
        for (int j = 0; j < size; j++)
        {
            stack1.push(stack2.top());
            stack2.pop();
        }

        // push tempElement to stack2
        stack2.push(tempElement);
        --size;
    }

    // move last element over
    tempElement = stack1.top();
    stack1.pop();
    stack2.push(tempElement);
}

// Part 2
void recurSwapStacks(stack<int>& stack1, stack<int>& stack2) 
{
    int element;
    
    if (!stack1.empty()) 
    {
        // store top element and decrement stack
        element = stack1.top();
        stack1.pop();
         
        recurSwapStacks(stack1, stack2);
         
        // only after reaching base case (stack1 is empty)
        // then starts pushing elements
        stack2.push(element);
    }
}

// Part 3
void stlSwapStacks(stack<int>& stack1, stack<int>& stack2) 
{
    stack1.swap(stack2);
}
 
// Part 4
void moveStacks(stack<int>& stack1, stack<int>& stack2) 
{
    stack2 = stack1;
    while (!stack1.empty())
    {
       stack1.pop();
    }
}
 