#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

using namespace std;

// Function to convert string to lowercase for case‑insensitive comparison
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function to get yes/no input with error handling
bool getYesNoInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt << " (y/n): ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Please enter y or n.\n";
            continue;
        }
        char choice = tolower(input[0]);
        if (choice == 'y') return true;
        if (choice == 'n') return false;
        cout << "Please enter 'y' for yes or 'n' for no.\n";
    }
}

// Function to get integer input with error handling
int getIntInput(const string& prompt, int min, int max) {
    string input;
    int choice;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            choice = stoi(input);
            if (choice >= min && choice <= max) {
                return choice;
            } else {
                cout << "Please enter a number between " << min << " and " << max << ".\n";
            }
        } catch (const invalid_argument&) {
            cout << "Invalid input. Please enter a valid number.\n";
        } catch (const out_of_range&) {
            cout << "Number too large. Please enter a valid number.\n";
        }
    }
}

string startGame() {
    cout << "====================================================" << endl;
    cout << "    Welcome to Carl's Cardinal Carnival!" << endl;
    cout << "====================================================" << endl;
    cout << "\nA mysterious carnival has appeared overnight in your town..." << endl;
    cout << "Carnival Carl, the beloved robo-mascot, is missing!" << endl;
    cout << "Your friend Jeff, the carnival director, rushes over in a panic." << endl;
    cout << "\"The hashed virtual key to our secret cotton-candy recipe and my bitcoin wallet is stored in Carl's hard drive!\"" << endl;
    cout << "Jeff pleads with you to help locate Carnival Carl before someone else does." << endl;
    cout << "\nWhat name should I put your ticket under?" << endl;
    cout << "Enter your name: ";
    string name;
    getline(cin, name);
    cout << "\nYou are given 10 free tickets to start with. Enjoy the carnival, " << name << "!" << endl;
    cout << "Your goal: Collect clues, track down Carnival Carl, and secure the virtual key." << endl;
    cout << "But be careful. Upset the wrong people and you might find yourself in trouble..." << endl;
    return name;
}

void endGame() {
    cout << "\n====================================================" << endl;
    cout << "Thank you for visiting Carl's Cardinal Carnival!" << endl;
    cout << "The mystery remains unsolved . . . for now." << endl;
    cout << "Please come back soon to continue your investigation!" << endl;
    cout << "====================================================" << endl;
    exit(0);
}

// Location Struct
struct LocationNode {
    string locationName;
    vector<LocationNode*> paths;
};

class Player {
protected:
    string name;
    int tickets;
    LocationNode* locationPtr;
    bool hasRope;
    map<string, bool> techniciansUpset;
    set<string> cluesCollected;
    list<string> locationHistory;
    list<string>::iterator currentLocationInHistory;
public:
    Player() : name(""), tickets(0), locationPtr(nullptr), hasRope(false) {
        currentLocationInHistory = locationHistory.end();
    }
    void setName(const string& n) { name = n; }
    string getName() const { return name; }
    void addOrSubTickets(int amount) {
        tickets += amount;
        if (tickets <= 0) {
            cout << "\nYou have run out of tickets! The carnival mystery will remain unsolved..." << endl;
            cout << "You must leave the carnival empty-handed. Game Over!" << endl;
            endGame();
        }
    }
    int getTickets() const { return tickets; }
    void setLocation(LocationNode* loc) {
        locationPtr = loc;
        if (locationHistory.empty() || locationHistory.back() != loc->locationName) {
            locationHistory.push_back(loc->locationName);
            currentLocationInHistory = prev(locationHistory.end());
        }
    }
    LocationNode* getLocation() { return locationPtr; }
    void pickUpRope() {
        hasRope = true;
        cout << "\nYou picked up a sturdy coil of rope. This might be useful later!\n";
    }
    bool hasRopeItem() const { return hasRope; }
    void useRope() { hasRope = false; }
    void upsetTechnician(const string& techName) { techniciansUpset[techName] = true; }
    bool isTechnicianUpset(const string& techName) const {
        auto it = techniciansUpset.find(techName);
        return (it != techniciansUpset.end() && it->second);
    }
    void addClue(const string& clue) {
        cluesCollected.insert(clue);
        cout << "\nCLUE DISCOVERED: " << clue << endl;
        cout << "This has been added to your investigation notes!" << endl;
    }
    bool hasClue(const string& clue) const { return cluesCollected.find(clue) != cluesCollected.end(); }
    void showClues() const {
        cout << "\nYOUR INVESTIGATION NOTES:" << endl;
        cout << "=============================" << endl;
        if (cluesCollected.empty()) {
            cout << "No clues collected yet. Keep exploring!" << endl;
        } else {
            int i = 1;
            for (const string& clue : cluesCollected) {
                cout << i++ << ". " << clue << endl;
            }
        }
        cout << "=============================" << endl;
    }
    void showLocationHistory() const {
        cout << "\nYOUR TRAVEL HISTORY:" << endl;
        cout << "========================" << endl;
        if (locationHistory.empty()) {
            cout << "You haven't been anywhere yet!" << endl;
        } else {
            int i = 1;
            for (const string& loc : locationHistory) {
                cout << i++ << ". " << loc << endl;
            }
        }
        cout << "========================" << endl;
    }
    bool hasVisitedLocation(const string& loc) const {
        return find(locationHistory.begin(), locationHistory.end(), loc) != locationHistory.end();
    }
    int getVisitCount(const string& loc) const {
        return count(locationHistory.begin(), locationHistory.end(), loc);
    }
    list<string> getLocationHistory() const { return locationHistory; }
};

struct Area : public LocationNode {
    Area(string n) { locationName = n; }
};

struct Booth {
    string boothName;
    LocationNode* locationPtr;
    Booth() : boothName(""), locationPtr(nullptr) {}
    void setBoothName(const string& n) { boothName = n; }
    string getBoothName() const { return boothName; }
    void setLocation(LocationNode* loc) { locationPtr = loc; }
    LocationNode* getLocation() const { return locationPtr; }
};

struct FoodBooth : public Booth {
    string foodName;
    int foodPrice;
    FoodBooth(string n, int price, LocationNode* loc) {
        boothName = n;
        foodName = n;
        foodPrice = price;
        locationPtr = loc;
    }
    void buyFood(Player& player) {
        if (player.getTickets() >= foodPrice) {
            player.addOrSubTickets(-foodPrice);
            cout << "\nYou bought " << foodName << "! Delicious!\n";
            if (player.getVisitCount(locationPtr->locationName) > 1) {
                cout << "The vendor recognizes you: 'Back for more? You have good taste!'\n";
            }
            if (rand() % 3 == 0) {
                if (foodName == "Hot Dog") {
                    player.addClue("Hot-dog vendor mentioned seeing strange lights near the Ferris Wheel at night");
                } else if (foodName == "Pizza") {
                    player.addClue("Pizza chef whispered about missing ingredients and weird carnival meetings");
                }
            }
        } else {
            cout << "You don't have enough tickets for " << foodName << ". You need " << foodPrice << " tickets.\n";
        }
    }
};

struct GameBooth : public Booth {
    string gameName;
    int gamePrice;
    GameBooth(string n, int price, LocationNode* loc) {
        boothName = n;
        gameName = n;
        gamePrice = price;
        locationPtr = loc;
    }
    void playGame(Player& player) {
        if (player.getTickets() >= gamePrice) {
            player.addOrSubTickets(-gamePrice);
            cout << "\nGet ready to play " << gameName << "!" << endl;
            cout << "Press Enter when you're ready to play...";
            string dummy;
            getline(cin, dummy);
            cout << "Here we go... " << endl;
            int reward = rand() % 5 + 1;
            player.addOrSubTickets(reward);
            if (reward >= 4) {
                cout << "Amazing! You won " << reward << " tickets!\n";
            } else if (reward >= 2) {
                cout << "Nice! You won " << reward << " tickets!\n";
            } else {
                cout << "You won " << reward << " ticket. Better luck next time!\n";
            }
            int meetChance = rand() % 10;
            if (meetChance < 3) {
                string techName = (gameName == "Ring Toss") ? "Rusty" : "Sparky";
                cout << "\nYou bump into " << techName << ", the ride technician.";
                if (rand() % 2 == 0) {
                    cout << " They seem annoyed and walk away upset!\n";
                    player.upsetTechnician(techName);
                } else {
                    cout << " They share some carnival tips with you.\n";
                    if (techName == "Rusty") {
                        player.addClue("Rusty mentioned the Ferris Wheel makes strange noises at midnight");
                    } else {
                        player.addClue("Sparky hinted that the roller coaster tracks show unusual wear patterns");
                    }
                }
            }
        } else {
            cout << "You don't have enough tickets to play " << gameName << ". You need " << gamePrice << " tickets.\n";
        }
    }
};

struct RideBooth : public Booth {
    string rideName;
    int ridePrice;
    bool isBroken;
    string technicianName;
    RideBooth(string n, int price, LocationNode* loc, string tech) {
        boothName = n;
        rideName = n;
        ridePrice = price;
        locationPtr = loc;
        isBroken = false;
        technicianName = tech;
    }
    void ride(Player& player, map<string, string>& contacts) {
        if (player.getTickets() < ridePrice) {
            cout << "You don't have enough tickets to ride the " << rideName << ". You need " << ridePrice << " tickets.\n";
            return;
        }
        player.addOrSubTickets(-ridePrice);
        cout << "\nYou climb aboard the " << rideName << "!" << endl;
        if (player.hasVisitedLocation(locationPtr->locationName) && player.getVisitCount(locationPtr->locationName) > 1) {
            cout << "The ride operator recognizes you: 'Back again? You're brave!'" << endl;
        }
        cout << "Hold on tight..." << endl;
        if (rand() % 4 == 0) {
            isBroken = true;
            cout << "\nThe " << rideName << " has broken down while you're on it!\n";
            if (rideName == "Ferris Wheel") {
                cout << "You're stuck at the very top of the Ferris Wheel! The wind is getting stronger...\n";
                player.addClue("From the top of the broken Ferris Wheel, you spotted a secret meeting behind the maintenance shed");
            } else if (rideName == "Mini Roller Coaster") {
                cout << "You're stuck upside down on the loop!\n";
            } else if (rideName == "Haunted House") {
                cout << "You're stuck in the darkest part of the Haunted House with strange noises all around you!\n";
                player.addClue("Strange whispers in the Haunted House mentioned 'the plan' and 'midnight'");
            }
            if (player.isTechnicianUpset(technicianName)) {
                cout << "\nYou call for " << technicianName << ", but they refuse to help!\n";
                if (rideName == "Ferris Wheel" && player.hasRopeItem()) {
                    cout << "Luckily, you have that rope and manage to climb down safely!\n";
                    player.useRope();
                } else if (rideName == "Haunted House") {
                    cout << "You'll have to find your own way out through the dark corridors...\n";
                    int lost = rand() % 3 + 1;
                    player.addOrSubTickets(-lost);
                    cout << "You lost " << lost << " tickets in your panic to escape!\n";
                } else {
                    cout << "After hanging on for what feels like hours, another worker finally helps you down.\n";
                    player.addOrSubTickets(-2);
                    cout << "You lost 2 tickets for the inconvenience.\n";
                }
            } else {
                string contact = contacts[technicianName];
                cout << "\nYou call " << technicianName << " at " << contact << ". They arrive quickly and fix the ride.\n";
                int bonus = rand() % 3 + 1;
                player.addOrSubTickets(bonus);
                cout << "For your patience, you receive " << bonus << " bonus tickets!\n";
                if (rand() % 2 == 0) {
                    if (technicianName == "Rusty") {
                        player.addClue("Rusty confided that someone has been tampering with the ride mechanisms");
                    } else if (technicianName == "Sparky") {
                        player.addClue("Sparky mentioned seeing suspicious figures near the rides after closing time");
                    } else if (technicianName == "Spooky") {
                        player.addClue("Spooky revealed that the Haunted House sound effects have been acting up mysteriously");
                    }
                }
            }
            isBroken = false;
        } else {
            cout << "\nYou enjoyed the " << rideName << " ride! What a thrill!\n";
            if (rand() % 4 == 0) {
                if (rideName == "Ferris Wheel") {
                    player.addClue("From the Ferris Wheel, you noticed unusual activity near the maintenance shed");
                } else if (rideName == "Mini Roller Coaster") {
                    player.addClue("During the roller coaster ride, you glimpsed someone in a hooded cloak near the game area");
                } else if (rideName == "Haunted House") {
                    player.addClue("In the Haunted House, you heard real voices discussing 'the final phase'");
                }
            }
        }
    }
};

// Function to create and link locations
vector<LocationNode*> createLocations() 
{
    vector<LocationNode*> locations;

    // Create locations
    locations.push_back(new LocationNode{"Exit"}); // index 0
    locations.push_back(new LocationNode{"Ticket Booth"}); // index 1
    locations.push_back(new LocationNode{"Game Area"}); // index 2
    locations.push_back(new LocationNode{"Food Area"}); // index 3
    locations.push_back(new LocationNode{"Ring Toss"}); // index 4
    locations.push_back(new LocationNode{"Archery Targets"}); // index 5
    locations.push_back(new LocationNode{"Hot Dog Stand"}); // index 6
    locations.push_back(new LocationNode{"Pizza Stand"}); // index 7
    locations.push_back(new LocationNode{"Ride Area"}); // index 8
    locations.push_back(new LocationNode{"Ferris Wheel"}); // index 9
    locations.push_back(new LocationNode{"Mini Roller Coaster"}); // index 10
    locations.push_back(new LocationNode{"Haunted House"}); // index 11
    locations.push_back(new LocationNode{"Maintenance Shed"}); // index 12
    

    // Link locations together (ALL CAN EXIT)
    locations[1]->paths = {locations[2], locations[3], locations[8], locations[0]}; // Ticket Booth -> Game/Food/Ride Areas + Exit
    locations[2]->paths = {locations[3], locations[4], locations[5], locations[8], locations[0]}; // Game Area -> Food Area + Game Booths + Ride Area + Exit
    locations[3]->paths = {locations[2], locations[6], locations[7], locations[8], locations[0]}; // Food Area -> Game Area + Food Booths + Ride Area + Exit
    locations[4]->paths = {locations[2], locations[0]}; // Ring Toss -> Game Area + Exit
    locations[5]->paths = {locations[2], locations[0]}; // Archery Targets -> Game Area + Exit
    locations[6]->paths = {locations[3], locations[0]}; // Hot Dog Stand -> Food Area + Exit
    locations[7]->paths = {locations[3], locations[0]}; // Pizza Stand -> Food Area + Exit
    locations[8]->paths = {locations[2], locations[3], locations[9], locations[10], locations[11], locations[12], locations[0]}; // Ride Area -> Food/Game Areas + Ride Booths + Maintenance Shed + Exit
    locations[9]->paths = {locations[8], locations[0]}; // Ferris Wheel -> Ride Area + Exit 
    locations[10]->paths = {locations[8], locations[0]}; // Mini Roller Coaster -> Ride Area + Exit
    locations[11]->paths = {locations[8], locations[0]}; // Haunted House -> Ride Area + Exit
    locations[12]->paths = {locations[8], locations[0]}; // Maintenance Shed -> Ride Area + Exit

    return locations;
}

// Function to create and link locations with booths
void createBooths(vector<FoodBooth*>& foodBooths, vector<GameBooth*>& gameBooths, vector<RideBooth*>& rideBooths, vector<LocationNode*>& locations) 
{
    // Get locations
    LocationNode* ringToss = locations[4];   
    LocationNode* archeryTargets = locations[5]; 
    LocationNode* hotDogStand = locations[6]; 
    LocationNode* pizzaStand = locations[7];
    LocationNode* ferrisWheel = locations[9];
    LocationNode* miniRollerCoaster = locations[10];
    LocationNode* hauntedHouse = locations[11];

    // Create food booths 
    foodBooths.push_back(new FoodBooth("Hot Dog", 3, hotDogStand));
    foodBooths.push_back(new FoodBooth("Pizza", 5, pizzaStand));

    // Create game booths 
    gameBooths.push_back(new GameBooth("Ring Toss", 2, ringToss));
    gameBooths.push_back(new GameBooth("Archery Targets", 4, archeryTargets));

    // Create ride booths with the technician responsible for each ride
    rideBooths.push_back(new RideBooth("Ferris Wheel", 6, ferrisWheel, "Rusty"));
    rideBooths.push_back(new RideBooth("Mini Roller Coaster", 8, miniRollerCoaster, "Sparky"));
    rideBooths.push_back(new RideBooth("Haunted House", 7, hauntedHouse, "Spooky"));
}

// Function to create emergency contacts map
map<string, string> createTechnicianContacts() {
    map<string, string> contacts;
    contacts["Rusty"] = "111-0123";
    contacts["Sparky"] = "222-4567";
    contacts["Spooky"] = "333-8901";
    return contacts;
}

void interactWithBooths(Player& player, vector<FoodBooth*>& foodBooths, vector<GameBooth*>& gameBooths, vector<RideBooth*>& rideBooths, map<string, string>& technicianContacts)
{
    LocationNode* currentLocation = player.getLocation();

    // Check if player is at the maintenance shed to get rope
    if (currentLocation->locationName == "Maintenance Shed" && !player.hasRopeItem()) {
        cout << "\nYou enter the dimly lit maintenance shed. Tools hang on the walls and strange diagrams are pinned to a bulletin board.\n";
        cout << "You notice a coil of sturdy rope in the corner. It might be useful for your investigation.\n";
        
        if (getYesNoInput("Take the rope?")) {
            player.pickUpRope();
            // Chance to find a clue in the maintenance shed
            if (rand() % 2 == 0) {
                player.addClue("Found a maintenance log showing suspicious after-hours work on all the rides");
            }
        }
    }

    // Check food booths
    for (FoodBooth* food : foodBooths) 
    {
        if (food->getLocation() == currentLocation) 
        {
            cout << "\nYou found the " << food->getBoothName() << "! The aroma is making your mouth water." << endl;
            cout << "The " << food->foodName << " costs " << food->foodPrice << " tickets." << endl;
            
            if (getYesNoInput("Would you like to buy " + food->foodName + "?")) 
            {
                food->buyFood(player);  
            } else {
                cout << "Maybe next time! The food will be here when you're ready.\n";
            }
        }
    }

    // Check game booths
    for (GameBooth* game : gameBooths) 
    {
        if (game->getLocation() == currentLocation)  
        {
            cout << "\nYou arrived at " << game->getBoothName() << "! The game operator greets you with a big smile." << endl;
            cout << "Playing " << game->gameName << " costs " << game->gamePrice << " tickets." << endl;
            
            if (getYesNoInput("Would you like to play " + game->gameName + "?")) 
            {
                game->playGame(player);  
            }
            else
            {
                cout << "No problem! Come back when you're feeling lucky!\n";
            }
        }
    }

    // Check ride booths
    for (RideBooth* ride : rideBooths) 
    {
        if (ride->getLocation() == currentLocation)  
        {
            cout << "\nYou arrived at " << ride->getBoothName() << "! ";
            
            if (player.hasVisitedLocation(currentLocation->locationName) && player.getVisitCount(currentLocation->locationName) > 1) {
                cout << "You've been here before - it looks just as exciting as you remember!" << endl;
            } else {
                cout << "The ride towers above you, looking both thrilling and slightly ominous." << endl;
            }
            
            cout << "Riding the " << ride->rideName << " costs " << ride->ridePrice << " tickets." << endl;
            
            if (getYesNoInput("Would you like to ride the " + ride->rideName + "?")) 
            {
                ride->ride(player, technicianContacts);  
            }
            else
            {
                cout << "Maybe you'll work up the courage later! The ride will be here waiting.\n";
            }
        }
    }

    cout << "\nYou have " << player.getTickets() << " tickets remaining.\n";
}

// Function to move player with enhanced interaction
void movePlayer(Player& player) 
{
    LocationNode* currentLocation = player.getLocation();
    cout << "\nYou are currently at: " << currentLocation->locationName << endl;
    
    // Provide context based on location history
    if (player.hasVisitedLocation(currentLocation->locationName) && player.getVisitCount(currentLocation->locationName) > 1) {
        cout << "You've been here " << player.getVisitCount(currentLocation->locationName) << " times before.\n";
    }
    
    cout << "\n🚶 Where would you like to go next?\n";

    for (size_t i = 0; i < currentLocation->paths.size(); i++) 
    {
        cout << i + 1 << ". " << currentLocation->paths[i]->locationName;
        
        // Show if location has been visited before
        if (player.hasVisitedLocation(currentLocation->paths[i]->locationName)) {
            cout << " (visited before)";
        }
        cout << endl;
    }

    int choice = getIntInput("\nEnter your choice: ", 1, static_cast<int>(currentLocation->paths.size()));

    player.setLocation(currentLocation->paths[choice - 1]);
    cout << "\nYou moved to " << player.getLocation()->locationName << "!\n";

    if (player.getLocation()->locationName == "Exit") 
    {
        // Check if player has collected enough clues to solve the mystery
        if (player.getLocationHistory().size() >= 3) { // Player explored enough
            cout << "\nAs you prepare to leave, you reflect on your investigation..." << endl;
            player.showClues();
            
            if (player.hasClue("Found a maintenance log showing suspicious after-hours work on all the rides") &&
                player.hasClue("From the top of the broken Ferris Wheel, you spotted a secret meeting behind the maintenance shed")) {
                cout << "\nMYSTERY SOLVED! You've uncovered enough evidence to prove that Carl and his technicians" << endl;
                cout << "have been staging the ride breakdowns to create drama and excitement!" << endl;
                cout << "The 'mystery' was all part of the carnival experience. Well done, detective!" << endl;
            }
        }
        endGame();  // Call the end game function
    }
}

// Function to display the technician contact list
void showTechnicianContacts(const map<string, string>& technicianContacts) {
    cout << "\n===== MAINTENANCE STAFF CONTACT LIST =====\n";
    for (const auto& pair : technicianContacts) {
        cout << pair.first << " (";
        
        if (pair.first == "Rusty") {
            cout << "Ferris Wheel";
        } else if (pair.first == "Sparky") {
            cout << "Mini Roller Coaster";
        } else if (pair.first == "Spooky") {
            cout << "Haunted House";
        }
        
        cout << " Technician): " << pair.second << endl;
    }
    cout << "============================================\n";
}

// Function to show player menu with enhanced options
void showPlayerMenu(Player& player) {
    cout << "\n===== PLAYER MENU =====\n";
    cout << "1. View Investigation Notes (Clues)\n";
    cout << "2. View Travel History\n";
    cout << "3. Check Ticket Count\n";
    cout << "4. Continue Exploring\n";
    cout << "========================\n";
    
    int choice = getIntInput("What would you like to do? ", 1, 4);
    
    switch(choice) {
        case 1:
            player.showClues();
            break;
        case 2:
            player.showLocationHistory();
            break;
        case 3:
            cout << "\nYou currently have " << player.getTickets() << " tickets.\n";
            break;
        case 4:
            break;
    }
}

// Main function
int main() 
{
    // Seed random number generator
    srand(time(nullptr));
    
    try {
        // Initialize player
        Player player;
        player.setName(startGame());
        player.addOrSubTickets(10); // Start with 10 tickets

        // Create map and booths
        vector<LocationNode*> locations = createLocations();
        vector<FoodBooth*> foodBooths;
        vector<GameBooth*> gameBooths;
        vector<RideBooth*> rideBooths;
        createBooths(foodBooths, gameBooths, rideBooths, locations);
        
        // Create technician contact map
        map<string, string> technicianContacts = createTechnicianContacts();

        player.setLocation(locations[1]); // Start at Ticket Booth

        cout << "\nYou are currently at: " << player.getLocation()->locationName << endl;
        cout << "\nHELPFUL TIPS:\n";
        cout << "• There's a list of maintenance staff contacts posted around the carnival\n";
        cout << "• Keep your eyes open for clues to solve the carnival mystery\n";
        cout << "• Visit different locations to uncover the truth\n";
        cout << "• Be nice to the technicians - you might need their help!\n";

        // Game loop with enhanced interaction
        while (true)
        {
            // If at the Ride Area, show the technician contacts list
            if (player.getLocation()->locationName == "Ride Area") {
                cout << "\nYou notice a posted sign with emergency contacts.\n";
                showTechnicianContacts(technicianContacts);
            }
            
            // Show player menu occasionally (every few moves)
            if (player.getLocationHistory().size() > 2 && player.getLocationHistory().size() % 3 == 0) {
                if (getYesNoInput("\nWould you like to check your progress and clues?")) {
                    showPlayerMenu(player);
                }
            }
            
            movePlayer(player);
            interactWithBooths(player, foodBooths, gameBooths, rideBooths, technicianContacts);
        }

        // Deallocate memory
        for (FoodBooth* food : foodBooths) delete food;
        for (GameBooth* game : gameBooths) delete game;
        for (RideBooth* ride : rideBooths) delete ride;
        for (LocationNode* location : locations) delete location;

    } catch (const exception& e) {
        cout << "\nAn unexpected error occurred: " << e.what() << endl;
        cout << "The carnival experience has been interrupted. Please try again!" << endl;
        return 1;
    }

    return 0;
}