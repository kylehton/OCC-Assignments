// Ton, Kyle

// Part 1
    map<string, set<string>> neighbors = {
      {"Illinois", {"Indiana", "Iowa", "Michigan", "Missouri", "Wisconsin"}},
      {"Indiana", {"Illinois", "Michigan", "Ohio"}},
      {"Iowa", {"Illinois", "Minnesota", "Missouri", "Nebraska", "South Dakota", "Wisconsin"}},
      {"Kansas", {"Missouri", "Nebraska"}},
      {"Michigan", {"Illinois", "Indiana", "Minnesota", "Ohio", "Wisconsin"}},
      {"Minnesota", {"Iowa", "Michigan", "North Dakota", "South Dakota", "Wisconsin"}},
      {"Missouri", {"Illinois", "Iowa", "Kansas", "Nebraska"}},
      {"Nebraska", {"Iowa", "Kansas", "Missouri", "South Dakota"}},
      {"North Dakota", {"Minnesota", "South Dakota"}},
      {"Ohio", {"Indiana", "Michigan"}},
      {"South Dakota", {"Iowa", "Minnesota", "Nebraska", "North Dakota"}},
      {"Wisconsin", {"Illinois", "Iowa", "Michigan", "Minnesota"}}
   };

// Part 2
    void printNeighbors(const map<string, set<string>>& mapOfStates)
    {
        for (const auto& state : mapOfStates)
        {
            cout << state.first << " borders with: ";
            for (const auto& neighbor : state.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

// Part 3
    // easier to hard code since there are few examples, using a graph then translating to adj. matrix would be more spatially inefficient
    /*
      {"Illinois", {"Indiana", "Iowa", "Michigan", "Missouri", "Wisconsin"}},
      {"Indiana", {"Illinois", "Michigan", "Ohio"}},
      {"Iowa", {"Illinois", "Minnesota", "Missouri", "Nebraska", "South Dakota", "Wisconsin"}},
      {"Kansas", {"Missouri", "Nebraska"}},
      {"Michigan", {"Illinois", "Indiana", "Minnesota", "Ohio", "Wisconsin"}},
      {"Minnesota", {"Iowa", "Michigan", "North Dakota", "South Dakota", "Wisconsin"}},
      {"Missouri", {"Illinois", "Iowa", "Kansas", "Nebraska"}},
      {"Nebraska", {"Iowa", "Kansas", "Missouri", "South Dakota"}},
      {"North Dakota", {"Minnesota", "South Dakota"}},
      {"Ohio", {"Indiana", "Michigan"}},
      {"South Dakota", {"Iowa", "Minnesota", "Nebraska", "North Dakota"}},
      {"Wisconsin", {"Illinois", "Iowa", "Michigan", "Minnesota"}}
   */
   vector<vector<int>> neighbors = {
      { 0,  1,  1,  0,  1,  0,  1,  0,  0,  0,  0,  1}, // Illinois
      { 1,  0,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0}, // Indiana
      { 1,  0,  0,  0,  0,  1,  1,  1,  0,  0,  1,  1}, // Iowa
      { 0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0}, // Kansas
      { 1,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  1}, // Michigan
      { 0,  0,  1,  0,  1,  0,  0,  0,  1,  0,  1,  1}, // Minnesota
      { 1,  0,  1,  1,  0,  0,  0,  1,  0,  0,  0,  0}, // Missouri
      { 0,  0,  1,  1,  0,  0,  1,  0,  0,  0,  1,  0}, // Nebraska
      { 0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  1,  0}, // North Dakota
      { 0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0}, // Ohio
      { 0,  0,  1,  0,  0,  1,  0,  1,  1,  0,  0,  0}, // South Dakota
      { 1,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0}  // Wisconsin
   };

// Part 4
    bool areNeighbors(const vector<string>& allStates, const vector<vector<int>>& adjMatrix, const string& firstState, const string& secondState)
    {
        // check whether first state and second state are neighbors
        // since states are in alphabetical order/sorted, binary search can be used to find the index of vector to check
        int indexFirst;
        int low = 0;
        int high = static_cast<int>(allStates.size())-1;
        
        while (low <= high)
        {
            int mid = static_cast<int>((low+high)/2);
            int firstComparison = (allStates[mid].compare(firstState));
            if (firstComparison == 0)
            {
                indexFirst = mid;
                break;
            }
            else if (firstComparison < 0) // item at mid is less than target
            {
                low = mid+1;
            }
            else
            {
                high = mid-1;
            }
        }
        
        int indexSecond;
        low = 0;
        high = allStates.size()-1;
        while (low <= high)
        {
            int mid = static_cast<int>((low+high)/2);
            int secondComparison = (allStates[mid].compare(secondState));
            if (secondComparison == 0)
            {
                indexSecond = mid;
                break;
            }
            else if (secondComparison < 0) // item at mid is less than target
            {
                low = mid+1;
            }
            else
            {
                high = mid-1;
            }
        }
        
        return (adjMatrix[indexFirst][indexSecond] == 1);
        
    }


