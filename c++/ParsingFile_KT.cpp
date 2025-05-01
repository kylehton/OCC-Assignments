#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>

using namespace std;

// Function to remove punctuation from a string
string removePunctuation(const string& text) {
    string result;
    for (char c : text) {
        if (!ispunct(c)) {
            result += c;
        }
    }
    return result;
}

int main() {
    // Set random seed
    srand(time(NULL));
    
    // File path - user should modify this as needed
    string filePath = "hamlet.txt"; 
    // Character to search for
    string character;
    cout << "Enter the character abbreviation (e.g., 'Ham' for Hamlet): ";
    getline(cin, character);
    
    // Character speech marker (e.g., "Ham.")
    string marker = character + ".";

    // Open the file
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filePath << endl;
        return 1;
    }

    // Process the file line by line to find speeches
    vector<string> speeches;
    string line;
    string currentSpeech = "";
    bool collectingSpeech = false;
    
    while (getline(file, line)) {
        // Check if this line starts a new speech by our character
        if (line.find(marker) == 0) {
            // If we were already collecting a speech, add it to the list
            if (collectingSpeech && !currentSpeech.empty()) {
                speeches.push_back(currentSpeech);
                currentSpeech = "";
            }
            
            // Start a new speech, removing the character marker
            collectingSpeech = true;
            currentSpeech = line.substr(marker.length());
            
            // Trim any leading spaces
            while (!currentSpeech.empty() && isspace(currentSpeech[0])) {
                currentSpeech = currentSpeech.substr(1);
            }
        }
        // Check if this line starts a different character's speech
        else if (!line.empty() && line.find(".") != string::npos && isalpha(line[0])) {
            // This might be another character speaking
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '.') {
                    // This is likely another character's marker
                    if (collectingSpeech && !currentSpeech.empty()) {
                        speeches.push_back(currentSpeech);
                        currentSpeech = "";
                    }
                    collectingSpeech = false;
                    break;
                }
            }
        }
        // If we're collecting a speech, add this line
        else if (collectingSpeech) {
            if (!currentSpeech.empty()) {
                currentSpeech += " ";
            }
            currentSpeech += line;
        }
    }
    
    // Add the last speech if we were collecting one
    if (collectingSpeech && !currentSpeech.empty()) {
        speeches.push_back(currentSpeech);
    }
    
    file.close();

    // Count speeches
    int speechCount = speeches.size();

    // If no speeches found
    if (speechCount == 0) {
        cout << "No speeches found for this character." << endl;
        return 0;
    }

    // Select a random speech
    int randomIndex = rand() % speechCount;
    string randomSpeech = speeches[randomIndex];

    // Clean the speech - replace multiple spaces with single space
    string cleanSpeech = "";
    bool lastWasSpace = false;
    for (char c : randomSpeech) {
        if (isspace(c)) {
            if (!lastWasSpace) {
                cleanSpeech += ' ';
                lastWasSpace = true;
            }
        } else {
            cleanSpeech += c;
            lastWasSpace = false;
        }
    }
    
    // Remove punctuation
    cleanSpeech = removePunctuation(cleanSpeech);

    // Prepare output
    string outputStr = "Character: " + character + "\n";
    outputStr += "Number of speeches: " + to_string(speechCount) + "\n";
    outputStr += "Random speech without punctuation:\n" + cleanSpeech + "\n";

    // Write to output file
    string outputFile = character + ".txt";
    ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        cout << "Error: Could not create output file " << outputFile << endl;
        return 1;
    }
    
    outFile << outputStr;
    outFile.close();

    cout << "Analysis complete! Results written to " << outputFile << endl;

    return 0;
}