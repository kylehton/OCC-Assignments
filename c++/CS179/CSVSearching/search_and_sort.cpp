#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

string getName(string name) {
    string nameToUpper;
    for (char c : name) {
        nameToUpper += toupper(c);
    }
    return nameToUpper;
}

void getPlayerData(unordered_map<string, double>& playerData){
    string playerName;
    cout << "Please enter the name of the player: " << endl;
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, playerName);
    playerName = getName(playerName);
    // .find() returns iterator to end() if not found
    if (playerData.find(playerName) != playerData.end()) {
        cout << "Player name and average: " << playerName << " - " << playerData[playerName] << endl;
    } else {
        cout << "Player not found." << endl;
    }
}

vector <pair<string, double>> ascendingSort(unordered_map<string, double> playerData) {
    vector<pair<string, double>> sortedPlayers(playerData.begin(), playerData.end());
    for (int i = 0; i < sortedPlayers.size() - 1; i++) {
        for (int j = 0; j < sortedPlayers.size() - i - 1; j++) {
            if (sortedPlayers[j].second > sortedPlayers[j + 1].second) {
                swap(sortedPlayers[j], sortedPlayers[j + 1]);
            }
        }
    }
    return sortedPlayers;
}

vector <pair<string, double>> descendingSort(unordered_map<string, double> playerData) {
    vector<pair<string, double>> sortedPlayers(playerData.begin(), playerData.end());
    for (int i = 0; i < sortedPlayers.size() - 1; i++) {
        for (int j = 0; j < sortedPlayers.size() - i - 1; j++) {
            if (sortedPlayers[j].second < sortedPlayers[j + 1].second) {
                swap(sortedPlayers[j], sortedPlayers[j + 1]);
            }
        }
    }
    return sortedPlayers;
}

unordered_map<string, double> sortPlayersByName(unordered_map<string, double>& playerData) {
    int order;
    cout << "Sorting players by averages:" << endl;
    cout << "Enter 1 for ascending or 2 for descending order: ";
    cin >> order;
    switch (order) {
        case 1: {
            vector<pair<string, double>> sortedPlayers = ascendingSort(playerData);
            for (const auto& player : sortedPlayers) {
                cout << player.first << " - " << player.second << endl;
            }
            break;
        }
        case 2: {
            vector<pair<string, double>> sortedPlayers = descendingSort(playerData);
            for (const auto& player : sortedPlayers) {
                cout << player.first << " - " << player.second << endl;
            }
            break;
        }
        default: {
            cout << "Invalid choice. Please enter 1 or 2." << endl;
            sortPlayersByName(playerData);
            break;
        }
    } 
    return playerData;
}

void allPlayersWithMinScore(unordered_map<string, double>& playerData) {
    double minScore;
    cout << "Enter the minimum score between 0.00 and 1.00: ";
    cin >> minScore;
    while (minScore < 0.00 || minScore > 1.00) {
        cout << "Invalid score. Please enter a score between 0.00 and 1.00: ";
        cin >> minScore;
    }
    cout << "Players with a score greater than or equal to " << minScore << ":" << endl;

    bool found = false;
    // since playerData is sorted, we can iterate through it and break at the first player that meets the criteria
    for (const auto& player : playerData) {
        if (player.second >= minScore) {
            cout << player.first << " - " << player.second << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No players found with a score greater than or equal to " << minScore << "." << endl;
    }

}

    int main() {
        string fileName = "aves.csv";
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error opening file: " << fileName << endl;
            return 1;
        }
        unordered_map<string, double> playerData;
        string line;
        while (getline(file, line)) {
            playerData[getName(line.substr(0, line.find(',')))] = stod(line.substr(line.find(',') + 1));
        }

        file.close();

        while (true) {
            int choice;
            cout << "Enter the one of the following options: " << endl;
            cout << "1. Search for a player\n";
            cout << "2. Sort players by name\n";
            cout << "3. Search for all players with a minimum score\n";
            cout << "4. Exit\n";
            cin >> choice;
            if (choice < 1 || choice > 4) {
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                cin >> choice;
            } else if (choice == 1) {
                getPlayerData(playerData);
                cout << endl;   
            } else if (choice == 2) {
                sortPlayersByName(playerData);
                cout << endl;
            } else if (choice == 3) {
                allPlayersWithMinScore(playerData);
                cout << endl;
            } else if (choice == 4) {
                cout << "\nThank you for using the program. Goodbye!" << endl;
                return 0;
            }
        }


    
    }