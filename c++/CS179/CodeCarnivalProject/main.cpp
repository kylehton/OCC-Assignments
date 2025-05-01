#include <iostream>
#include <string>
#include <vector> 

using namespace std;

string startGame()
{
    cout << "Welcome to Carl's Cardinal Carnival!" << endl;
    cout << "\nThe best carnival in this little ol' town! What name should I put your ticket under?" << endl;
    cout << "\nEnter your name: ";
    string name;
    getline(cin, name);
    cout << "\nYou are given 10 free tickets to start with. Enjoy the carnival, " << name << "!" << endl;
    return name;
}

void endGame()
{
    cout << "\nThank you for visiting Carl's Cardinal Carnival! We hope you had a great time!" << endl;
    cout << "\nPlease come back soon!\n" << endl;
    exit(0);
}

// Location Struct
struct LocationNode 
{
    public:
        string locationName;
        vector<LocationNode*> paths;
};

class Player 
{
    protected:
        string name;
        int tickets;
        LocationNode* locationPtr;

    public:
        Player() 
        {
            name = "";
            tickets = 0;
            locationPtr = nullptr;
        }

        void setName(const string& name) 
        {
            this->name = name;
        }

        string getName() const 
        {
            return name;
        }

        void addOrSubTickets(int amount) 
        {
            tickets += amount;
            if (tickets <= 0)
            {
                cout << "\nYou have run out of tickets! You must start over to continue using the booths." << endl;
                endGame();
            }
        }

        int getTickets() const {
            return tickets;
        }

        void setLocation(LocationNode* location) 
        {
            locationPtr = location;
        }

        LocationNode* getLocation() 
        {
            return locationPtr;
        }
};

struct Area : public LocationNode 
{
    Area(string name) 
    {
        locationName = name;
    }
};


// Booth Struct
struct Booth 
{
    public:
        string boothName;
        LocationNode* locationPtr; 

        Booth() 
        {
            boothName = "";
            locationPtr = nullptr;
        }

        void setBoothName(const string& name) 
        {
            boothName = name;
        }

        string getBoothName() const 
        {
            return boothName;
        }

        void setLocation(LocationNode* location) 
        {
            locationPtr = location;
        }

        LocationNode* getLocation() const 
        {
            return locationPtr;
        }
};

// Food Booth Struct 
struct FoodBooth : public Booth 
{
    string foodName;
    int foodPrice;

    FoodBooth(string name, int price, LocationNode* location) 
    {
        boothName = name;
        foodName = name;
        foodPrice = price;
        locationPtr = location; 
    }

    void buyFood(Player& player) 
    {
        if (player.getTickets() >= foodPrice) 
        {
            player.addOrSubTickets(-foodPrice);
            cout << "\nYou bought " << foodName << "! Enjoy!\n";
        } 
        else 
        {
            cout << "You don't have enough tickets for " << foodName << ".\n";
        }
    }
};

// Game Booth Struct (Playing Games Costs Tickets)
struct GameBooth : public Booth 
{
    string gameName;
    int gamePrice;

    GameBooth(string name, int price, LocationNode* location) 
    {
        boothName = name;
        gameName = name;
        gamePrice = price;
        locationPtr = location; 
    }

    void playGame(Player& player) 
    {
        if (player.getTickets() >= gamePrice) 
        {
            player.addOrSubTickets(-gamePrice);
            int reward = rand() % 5 + 1; // Random ticket win
            player.addOrSubTickets(reward);
            cout << "\nYou played " << gameName << " and won " << reward << " tickets!\n";
        } 
        else 
        {
            cout << "You don't have enough tickets to play " << gameName << ".\n";
        }
    }
};

struct RideBooth : public Booth 
{
    string rideName;
    int ridePrice;

    RideBooth(string name, int price, LocationNode* location) 
    {
        boothName = name;
        rideName = name;
        ridePrice = price;
        locationPtr = location; 
    }

    void ride(Player& player) 
    {
        if (player.getTickets() >= ridePrice) 
        {
            player.addOrSubTickets(-ridePrice);
            cout << "\nYou enjoyed the " << rideName << " ride!\n";
        } 
        else 
        {
            cout << "You don't have enough tickets to ride the " << rideName << ".\n";
        }
    }
};


// Function to create and link locations
vector<LocationNode*> createLocations() 
{
    vector<LocationNode*> locations;

    // Create locations
    locations.push_back(new LocationNode{"Exit"}); // index 0
    locations.push_back((new LocationNode{"Ticket Booth"})); // index 1
    locations.push_back(new LocationNode{"Game Area"}); // index 2
    locations.push_back(new LocationNode{"Food Area"}); // index 3
    locations.push_back(new LocationNode{"Ring Toss"}); // index 4
    locations.push_back(new LocationNode{"Archery Targets"}); // index 5
    locations.push_back(new LocationNode{"Hot Dog Stand"}); // index 6
    locations.push_back(new LocationNode{"Pizza Stand"}); // index 7
    locations.push_back(new LocationNode{"Ride Area"}); // index 8
    locations.push_back(new LocationNode{"Ferris Wheel"}); // index 9
    locations.push_back(new LocationNode{"Mini Roller Coaster"}); // index 10
    

    // Link locations together (ALL CAN EXIT)
    locations[1]->paths = {locations[2], locations[3], locations[8], locations[0]}; // Ticket Booth -> Game/Food/Ride Areas + Exit
    locations[2]->paths = {locations[3], locations[4], locations[5], locations[0]}; // Game Area -> Food Area + Game Booths + Exit
    locations[3]->paths = {locations[2], locations[6], locations[7], locations[0]}; // Food Area -> Game Area + Food Booths + Exit
    locations[4]->paths = {locations[2], locations[0]}; // Ring Toss -> Game Area + Exit
    locations[5]->paths = {locations[2], locations[0]}; // Archery Targets -> Game Area + Exit
    locations[6]->paths = {locations[3], locations[0]}; // Hot Dog Stand -> Food Area + Exit
    locations[7]->paths = {locations[3], locations[0]}; // Pizza Stand -> Food Area + Exit
    locations[8]->paths = {locations[2], locations[3], locations[9], locations[10], locations[0]}; // Ride Area -> Food/Game Areas + Ride Booths + Exit
    locations[9]->paths = {locations[8], locations[0]}; // Ferris Wheel -> Ride Area + Exit 
    locations[10]->paths = {locations[8], locations[0]}; // Mini Roller Coaster -> Ride Area + Exit

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

    // Create food booths 
    foodBooths.push_back(new FoodBooth("Hot Dog", 3, hotDogStand));
    foodBooths.push_back(new FoodBooth("Pizza", 5, pizzaStand));

    // Create game booths 
    gameBooths.push_back(new GameBooth("Ring Toss", 2, ringToss));
    gameBooths.push_back(new GameBooth("Archery Targets", 4, archeryTargets));

    rideBooths.push_back(new RideBooth("Ferris Wheel", 6, ferrisWheel));
    rideBooths.push_back(new RideBooth("Mini Roller Coaster", 8, miniRollerCoaster));
}



void interactWithBooths(Player& player, vector<FoodBooth*>& foodBooths, vector<GameBooth*>& gameBooths, vector<RideBooth*>& rideBooths)
{
    LocationNode* currentLocation = player.getLocation();

    // Check food booths
    for (FoodBooth* food : foodBooths) 
    {
        if (food->getLocation() == currentLocation) 
        {
            cout << "You found the " << food->getBoothName() << "! Would you like to buy " 
                 << food->foodName << " for " << food->foodPrice << " tickets? (y/n)\n" << endl;
            char choice;
            cin >> choice;
            
            if (choice == 'y') 
            {
                food->buyFood(player);  
            }
        }
    }

    // Check game booths
    for (GameBooth* game : gameBooths) 
    {
        if (game->getLocation() == currentLocation)  
        {
            cout << "You arrived at " << game->getBoothName() << "! Would you like to play " 
                 << game->gameName << " for " << game->gamePrice << " tickets? (y/n)\n";
            char choice;
            cin >> choice;
            if (choice == 'y') 
            {
                game->playGame(player);  
            }
            else
            {
                cout << "Ok then. See you later, then!\n" << endl;
            }
        }
    }

    // Check ride booths
    for (RideBooth* ride : rideBooths) 
    {
        if (ride->getLocation() == currentLocation)  
        {
            cout << "You arrived at " << ride->getBoothName() << "! Would you like to ride the " 
                 << ride->rideName << " for " << ride->ridePrice << " tickets? (y/n)\n";
            char choice;
            cin >> choice;
            if (choice == 'y') 
            {
                ride->ride(player);  
            }
            else
            {
                cout << "Ok then. See you later, then!\n" << endl;
            }
        }
    }

    cout << "You have " << player.getTickets() << " tickets left.\n";
}


// Function to move player
void movePlayer(Player& player) 
{
    LocationNode* currentLocation = player.getLocation();
    cout << "\nYou are at: " << currentLocation->locationName << endl;
    cout << "Where do you want to go?\n" << endl;

    for (size_t i = 0; i < currentLocation->paths.size(); i++) 
    {
        cout << i + 1 << ". " << currentLocation->paths[i]->locationName << endl;
    }


    int choice;
    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice > 0 && choice <= currentLocation->paths.size()) 
    {
        player.setLocation(currentLocation->paths[choice - 1]);
        cout << "\nYou moved to " << player.getLocation()->locationName << "!\n";

        if (player.getLocation()->locationName == "Exit") 
        {
            endGame();  // Call the end game function
        }
    } 
    else 
    {
        cout << "\nInvalid choice, try again.\n";
    }
}


// Main function
int main() 
{
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

    player.setLocation(locations[1]); // Start at Ticket Booth

    cout << "You are currently at: " << player.getLocation()->locationName << endl;

    while (true)
    {
        movePlayer(player);
        interactWithBooths(player, foodBooths, gameBooths, rideBooths);
    }

    // Deallocate memory
    for (FoodBooth* food : foodBooths) delete food;
    for (GameBooth* game : gameBooths) delete game;
    for (RideBooth* ride : rideBooths) delete ride;
    for (LocationNode* location : locations) delete location;

    return 0;
}
