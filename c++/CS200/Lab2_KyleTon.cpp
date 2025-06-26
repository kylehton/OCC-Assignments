//Ton, Kyle

//Part 1:
    void bfs(const vector<vector<int>>& adjM, list<int>& seq, int start)
    {
        const int graphSize = adjM.size();
        
        // create queue to iterate through nodes in graph
        queue<int> visitedQueue;
        
        // array for visited, populated with false values
        bool* b_visited = new bool[graphSize]();
        
        // start process for starting vertex
        visitedQueue.push(start);
        seq.push_back(start);
        b_visited[start] = true;
        
        int count = 1;
        
        while ((!visitedQueue.empty()) && count < graphSize)
        {
            int current = visitedQueue.front();
            visitedQueue.pop();
            
            for (int i = 0; i < graphSize; ++i)
            {
                // if 1 (is edge between this node and current) and it is not yet visited
                if ((adjM[current][i] == 1) && (!b_visited[i]))
                {
                    visitedQueue.push(i);
                    seq.push_back(i);
                    b_visited[i] = true;
                    ++count;
                }
            }
        }
        
        // case for disconnected graphs
        if (count < graphSize)
        {
            for (int v = 0; v < graphSize; ++v)
            {
                if (!b_visited[v])
                {
                    visitedQueue.push(v);
                    seq.push_back(v);
                    b_visited[v] = true;
                }
                while (!visitedQueue.empty() && count < graphSize)
                {
                    
                    int current = visitedQueue.front();
                    visitedQueue.pop();
                    
                    for (int i = 0; i < graphSize; ++i)
                    {
                        // if 1 (is edge between this node and current) and it is not yet visited
                        if ((adjM[current][v] == 1) && (!b_visited[v]))
                        {
                            visitedQueue.push(v);
                            seq.push_back(v);
                            b_visited[v] = true;
                            ++count;
                        }
                    }
                }
            }
            
        }   
        delete[] b_visited;
        b_visited = nullptr;
    }