#include <iostream>
#include <iomanip>

using namespace std;

// Price constants for different sections
const double PRICE_A = 10.00;
const double PRICE_B = 15.00;
const double PRICE_C = 20.00;

// Class to represent a theater seat
class Seat {
public:
    bool isSold;
    bool isWheelchairAccessible;
    double price;
    bool hasObstructedView;
    int seatNumber;
    char section;

    // Default constructor with initialization
    Seat()
    {
        isSold = false;
        isWheelchairAccessible = false;
        price = 0.0;
        hasObstructedView = false;
        seatNumber = 0;
        section = 'X';
    }
};

// Function to display the seating map
void displaySeatingMap(Seat seats[3][10]) {
    cout << "\n===== THEATER SEATING MAP =====\n";
    cout << "     "; // One space less
    for (int j = 0; j < 10; j++) {
        cout << setw(5) << j*2+1; // Back to setw(4)
    }
    cout << "\n";

    for (int i = 0; i < 3; i++) {
        cout << "Row " << static_cast<char>('A' + i) << ": ";
        for (int j = 0; j < 10; j++) {
            Seat* seatPtr = &seats[i][j];
            if (seatPtr->isSold) {
                cout << " [X] ";
            } else if (seatPtr->hasObstructedView) {
                cout << " [O] ";
            } else if (seatPtr->isWheelchairAccessible) {
                cout << " [W] ";
            } else {
                cout << " [ ] ";
            }
        }
        cout << "\n";
    }
    cout << "\nLegend: [X] = Sold, [ ] = Available, [O] = Obstructed View, [W] = Wheelchair Accessible\n";
}

// Function to initialize the theater with default values
void initializeTheater(Seat seats[3][10]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            Seat* seatPtr = &seats[i][j];
            seatPtr->seatNumber = j*2+1; // Odd numbers only: 1,3,5,...,19
            
            // Set section and price based on row
            if (i == 0) {
                seatPtr->section = 'A';
                seatPtr->price = PRICE_A;
            } else if (i == 1) {
                seatPtr->section = 'B';
                seatPtr->price = PRICE_B;
            } else {
                seatPtr->section = 'C';
                seatPtr->price = PRICE_C;
            }
        }
    }
    
    // Mark some seats as obstructed view (with 20% discount)
    Seat* obstructedPtr1 = &seats[0][8];
    Seat* obstructedPtr2 = &seats[0][9];
    Seat* obstructedPtr3 = &seats[1][8];
    Seat* obstructedPtr4 = &seats[1][9];
    Seat* obstructedPtr5 = &seats[2][8];
    Seat* obstructedPtr6 = &seats[2][9];
    
    obstructedPtr1->hasObstructedView = true;
    obstructedPtr2->hasObstructedView = true;
    obstructedPtr3->hasObstructedView = true;
    obstructedPtr4->hasObstructedView = true;
    obstructedPtr5->hasObstructedView = true;
    obstructedPtr6->hasObstructedView = true;
    
    obstructedPtr1->price *= 0.8;
    obstructedPtr2->price *= 0.8;
    obstructedPtr4->price *= 0.8;
    
    // Mark some seats as wheelchair accessible
    Seat* wheelchairPtr1 = &seats[2][0];
    Seat* wheelchairPtr2 = &seats[2][1];
    Seat* wheelchairPtr3 = &seats[1][0];
    Seat* wheelchairPtr4 = &seats[2][4];
    Seat* wheelchairPtr5 = &seats[2][5];
    
    wheelchairPtr1->isWheelchairAccessible = true;
    wheelchairPtr2->isWheelchairAccessible = true;
    wheelchairPtr3->isWheelchairAccessible = true;
    wheelchairPtr4->isWheelchairAccessible = true;
    wheelchairPtr5->isWheelchairAccessible = true;
}

// Function to find max consecutive available seats in a row using pointers
int findMaxConsecutive(Seat seats[3][10], int row, int& startCol, bool needWheelchair) {
    int maxConsecutive = 0;
    int currentConsecutive = 0;
    int startPos = -1;
    
    Seat* rowPtr = &seats[row][0]; // Pointer to the beginning of the row
    
    for (int j = 0; j < 10; j++) {
        Seat* currentSeatPtr = rowPtr + j; // Using pointer arithmetic to navigate the row
        
        // Skip wheelchair seats if not needed
        if (currentSeatPtr->isWheelchairAccessible && !needWheelchair) {
            // Reset the consecutive count if we encounter a wheelchair seat and don't need it
            if (currentConsecutive > maxConsecutive) {
                maxConsecutive = currentConsecutive;
                startCol = startPos;
            }
            currentConsecutive = 0;
            continue;
        }
        
        if (!currentSeatPtr->isSold) {
            if (currentConsecutive == 0) {
                startPos = j;
            }
            currentConsecutive++;
        } else {
            if (currentConsecutive > maxConsecutive) {
                maxConsecutive = currentConsecutive;
                startCol = startPos;
            }
            currentConsecutive = 0;
        }
    }
    
    // Check one more time after the loop
    if (currentConsecutive > maxConsecutive) {
        maxConsecutive = currentConsecutive;
        startCol = startPos;
    }
    
    return maxConsecutive;
}

// Function to find and assign seats using pointers
bool findAndAssignSeats(Seat seats[3][10], char requestedSection, int numSeats, bool needWheelchair) {
    int startRow;
    
    // Convert section to row number
    if (requestedSection == 'A' || requestedSection == 'a') {
        startRow = 0;
    } else if (requestedSection == 'B' || requestedSection == 'b') {
        startRow = 1;
    } else if (requestedSection == 'C' || requestedSection == 'c') {
        startRow = 2;
    } else {
        std::cout << "Invalid section. Please try again.\n";
        return false;
    }
    
    // Check for wheelchair accessibility if needed
    if (needWheelchair) {
        bool foundWheelchair = false;
        for (int i = startRow; i < 3 && !foundWheelchair; i++) {
            Seat* rowPtr = &seats[i][0];
            for (int j = 0; j < 10; j++) {
                Seat* seatPtr = rowPtr + j;
                if (seatPtr->isWheelchairAccessible && !seatPtr->isSold) {
                    foundWheelchair = true;
                    break;
                }
            }
        }
        
        if (!foundWheelchair) {
            std::cout << "No wheelchair accessible seats available in the requested sections.\n";
            return false;
        }
    }
    
    // Try to find consecutive seats in the requested row
    int startCol;
    int maxConsecutive = findMaxConsecutive(seats, startRow, startCol, needWheelchair);
    
    if (maxConsecutive >= numSeats) {
        // We found enough consecutive seats in the requested row
        double totalPrice = 0.0;
        std::cout << "Seats assigned:\n";
        
        Seat* rowPtr = &seats[startRow][0];
        for (int j = startCol; j < startCol + numSeats; j++) {
            Seat* seatPtr = rowPtr + j;
            
            // Skip wheelchair seats if not needed
            if (seatPtr->isWheelchairAccessible && !needWheelchair) {
                std::cout << "Error: Cannot assign regular customer to wheelchair accessible seat.\n";
                return false;
            }
            
            seatPtr->isSold = true;
            totalPrice += seatPtr->price;
            
            std::cout << "  Row " << seatPtr->section << ", Seat " << seatPtr->seatNumber;
            
            if (seatPtr->hasObstructedView) {
                std::cout << " (Obstructed View - 20% discount)";
            }
            if (seatPtr->isWheelchairAccessible) {
                std::cout << " (Wheelchair Accessible)";
            }
            std::cout << "\n";
        }
        
        std::cout << "Total price: $" << std::fixed << std::setprecision(2) << totalPrice << "\n";
        return true;
    }
    
    // If we get here, we couldn't find enough consecutive seats in the requested row
    // Check if we can use the wrap-around approach
    
    if (startRow >= 2) {
        // We're already in the last row, can't wrap around
        std::cout << "Not enough consecutive seats available in section " << requestedSection << ".\n";
        return false;
    }
    
    // Count total available seats in current row
    int availableInCurrentRow = 0;
    Seat* currentRowPtr = &seats[startRow][0];
    for (int j = 0; j < 10; j++) {
        Seat* seatPtr = currentRowPtr + j;
        // Skip wheelchair seats if not needed
        if (seatPtr->isWheelchairAccessible && !needWheelchair) {
            continue;
        }
        if (!seatPtr->isSold) {
            availableInCurrentRow++;
        }
    }
    
    if (availableInCurrentRow == 0) {
        std::cout << "No seats available in section " << requestedSection << ".\n";
        return false;
    }
    
    // Check if we have enough total seats between this row and the next
    int availableInNextRow = 0;
    Seat* nextRowPtr = &seats[startRow + 1][0];
    for (int j = 0; j < 10; j++) {
        Seat* seatPtr = nextRowPtr + j;
        // Skip wheelchair seats if not needed
        if (seatPtr->isWheelchairAccessible && !needWheelchair) {
            continue;
        }
        if (!seatPtr->isSold) {
            availableInNextRow++;
        }
    }
    
    if (availableInCurrentRow + availableInNextRow < numSeats) {
        std::cout << "Not enough total seats available in sections " << requestedSection 
                  << " and " << static_cast<char>(requestedSection + 1) << ".\n";
        return false;
    }
    
    // Try to implement the wraparound approach
    // First, place as many seats as possible in the current row
    // starting from the rightmost available seat
    int seatsInCurrentRow = std::min(availableInCurrentRow, numSeats);
    int remainingSeats = numSeats - seatsInCurrentRow;
    
    // Keep track of assigned seats for potential rollback
    int assignedSeats[30][2]; // [seatIndex][0=row, 1=col]
    int totalAssigned = 0;
    double totalPrice = 0.0;
    
    // Find the rightmost available seats in the current row
    int assignedToCurrentRow = 0;
    currentRowPtr = &seats[startRow][0];
    for (int j = 9; j >= 0 && assignedToCurrentRow < seatsInCurrentRow; j--) {
        Seat* seatPtr = currentRowPtr + j;
        // Skip wheelchair seats if not needed
        if (seatPtr->isWheelchairAccessible && !needWheelchair) {
            continue;
        }
        if (!seatPtr->isSold) {
            assignedSeats[totalAssigned][0] = startRow;
            assignedSeats[totalAssigned][1] = j;
            totalAssigned++;
            assignedToCurrentRow++;
        }
    }
    
    // Now place remaining seats in the row behind, directly behind the ones in current row
    // Starting from the rightmost seats
    if (remainingSeats > 0) {
        nextRowPtr = &seats[startRow + 1][0];
        for (int i = 0; i < assignedToCurrentRow && remainingSeats > 0; i++) {
            int col = assignedSeats[i][1];
            Seat* seatPtr = nextRowPtr + col;
            // Skip wheelchair seats if not needed
            if (seatPtr->isWheelchairAccessible && !needWheelchair) {
                continue;
            }
            if (!seatPtr->isSold) {
                assignedSeats[totalAssigned][0] = startRow + 1;
                assignedSeats[totalAssigned][1] = col;
                totalAssigned++;
                remainingSeats--;
            }
        }
        
        // If we still need more seats, look for any available in the next row
        if (remainingSeats > 0) {
            for (int j = 9; j >= 0 && remainingSeats > 0; j--) {
                // Skip columns we've already assigned
                bool alreadyAssigned = false;
                for (int i = assignedToCurrentRow; i < totalAssigned; i++) {
                    if (assignedSeats[i][1] == j) {
                        alreadyAssigned = true;
                        break;
                    }
                }
                
                if (!alreadyAssigned) {
                    Seat* seatPtr = nextRowPtr + j;
                    // Skip wheelchair seats if not needed
                    if (seatPtr->isWheelchairAccessible && !needWheelchair) {
                        continue;
                    }
                    if (!seatPtr->isSold) {
                        assignedSeats[totalAssigned][0] = startRow + 1;
                        assignedSeats[totalAssigned][1] = j;
                        totalAssigned++;
                        remainingSeats--;
                    }
                }
            }
        }
    }
    
    // Check if we managed to assign all the seats
    if (totalAssigned < numSeats) {
        std::cout << "Could not find appropriate seats with wrap-around configuration.\n";
        return false;
    }
    
    // Actually mark the seats as sold and calculate the price
    std::cout << "Seats assigned:\n";
    for (int i = 0; i < totalAssigned; i++) {
        int row = assignedSeats[i][0];
        int col = assignedSeats[i][1];
        
        Seat* seatPtr = &seats[row][col];
        
        // Double check that we're not assigning wheelchair seats to non-wheelchair customers
        if (seatPtr->isWheelchairAccessible && !needWheelchair) {
            std::cout << "Error: Cannot assign regular customer to wheelchair accessible seat.\n";
            // Rollback any seats we've already marked as sold
            for (int j = 0; j < i; j++) {
                Seat* rollbackPtr = &seats[assignedSeats[j][0]][assignedSeats[j][1]];
                rollbackPtr->isSold = false;
            }
            return false;
        }
        
        seatPtr->isSold = true;
        totalPrice += seatPtr->price;
        
        std::cout << "  Row " << seatPtr->section << ", Seat " << seatPtr->seatNumber;
        
        if (seatPtr->hasObstructedView) {
            std::cout << " (Obstructed View - 20% discount)";
        }
        if (seatPtr->isWheelchairAccessible) {
            std::cout << " (Wheelchair Accessible)";
        }
        std::cout << "\n";
    }
    
    std::cout << "Total price: $" << std::fixed << std::setprecision(2) << totalPrice << "\n";
    return true;
}

int main() {
    Seat theaterSeats[3][10]; // 3 rows of 10 seats
    initializeTheater(theaterSeats);
    
    std::cout << "Welcome to the Theater Booking System!\n";
    displaySeatingMap(theaterSeats);
    
    char choice;
    do {
        int numSeats;
        char section;
        char wheelchairChoice;
        bool needWheelchair = false;
        
        std::cout << "\n=== New Booking ===\n";
        std::cout << "How many seats would you like to purchase? ";
        std::cin >> numSeats;
        
        if (numSeats <= 0 || numSeats > 30) {
            std::cout << "Invalid number of seats. Please enter a number between 1 and 30.\n";
            continue;
        }
        
        std::cout << "Which section would you prefer (A, B, C)? ";
        std::cin >> section;
        
        std::cout << "Do you need wheelchair accessible seats? (Y/N): ";
        std::cin >> wheelchairChoice;
        needWheelchair = (wheelchairChoice == 'Y' || wheelchairChoice == 'y');
        
        if (findAndAssignSeats(theaterSeats, section, numSeats, needWheelchair)) {
            std::cout << "Booking successful!\n";
        } else {
            std::cout << "Booking failed. Please try again.\n";
        }
        
        displaySeatingMap(theaterSeats);
        
        std::cout << "\nWould you like to make another booking? (Y/N): ";
        std::cin >> choice;
    } while (choice == 'Y' || choice == 'y');
    
    std::cout << "Thank you for using the Theater Booking System!\n";
    
    return 0;
}