// This program illustrates the use of constructors
// and destructors in the allocation and deallocation of memory.
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Squares {
    private:
        int length;
        std::unique_ptr<int[]> sq;
        public:
        // Constructor allocates storage for sequence
        // of squares and creates the sequence
        Squares(int len)
        {
            length = len;

            sq = make_unique<int[]>(len);
            for (int k = 0; k < length; k++)
            {
                sq[k] = (k+1)*(k+1); 
            }
        cout << "Construct an object of size " << length << endl; 
        }

        // Print the sequence
        void print()
        {
            for (int k = 0; k < length; k++)
                cout << sq[k] << " ";
            cout << endl;
        }

        void outputSquares(Squares *sqPtr)
        { 
            cout << "The list of squares is: "; 
            sqPtr->print();
        }
 };

 //************************************************
 // Outputs the sequence of squares in a          *
 // Squares object                                *
 //************************************************

 int main()
 {
    // Main allocates a Squares object
    Squares *sqPtr = new Squares(3);
    sqPtr->Squares::outputSquares(sqPtr);

    // Main deallocates the Squares object
    delete sqPtr;

    return 0;
}