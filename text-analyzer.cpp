#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

void analyzeTextFile();
void countLetters(ifstream &file);
void countWords(ifstream &file);
bool askSave();

int main() {
    int num; // user choice for what to do

    do {
        cout << "1. Analyze a text file" << endl;
        cout << "2. Quit" << endl << "> ";
        bool cont = true; // whether the user entered a valid value

        do {
            string ans; // user input as a string
            getline(cin, ans);
            stringstream ss(ans);

            // if the user input a number (this doesn't check if it's actually 1 or 2)
            if (!(ss >> num)) {
                cerr << "Please enter a valid number, 1 or 2." << endl;
                cont =  false;
            } else {
                ss >> num;
                cont = true;
            }
        } while(!cont);

        // if the user did not quit
        if (num == 1) {
            analyzeTextFile();
        } else {
            cout << "Invalid input." << endl;
        }

    } while (num != 2); 
    return 0;
}

void analyzeTextFile() {
    cout << "Enter the file path: ";
    string filePath; // user input file path, either explicit or implicit
    getline(cin, filePath);
    cout << "1. Count letters" << endl;
    cout << "2. Count words" << endl << "> ";

    int num; // user choice for what to do
    bool cont = true; // whether the user entered a valid value
    do {
        string ans; // user input as a string
        getline(cin, ans);
        stringstream ss(ans);

        // if the user input a number (this doesn't check if it's actually 1 or 2)
        if (!(ss >> num)) {
            cerr << "Please enter a valid number, 1 or 2." << endl;
            cont =  false;
        } else {
            ss >> num;
            cont = true;
        }
    } while(!cont);

    // open the file at the specified location
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    switch (num) {
        case 1:
            countLetters(file);
            break;
        case 2:
            countWords(file);
            break;
        default:
            cout << "Invalid input." << endl;
            break;
    }

    return;
}

void countLetters(ifstream &file) {
    unordered_map<char, int> letterCount; // dictionary of characters with their number of occurrences
    string line; // line of the iterated text file

    while (getline(file, line)) {
        for (char c : line) {
            // if it's a letter, add it to the map (lowercase)
            if (isalpha(c)) {
                c = tolower(c);
                letterCount[c]++;
            }
        }
    }

    file.close();

    vector<pair<char, int>> freqVec(letterCount.begin(), letterCount.end()); // vector form of the same map, so it can be sorted

    // sort the vector by number of occurrences
    sort(freqVec.begin(), freqVec.end(), [](const pair<char, int> &a, const pair<char, int> &b) {
        return b.second < a.second;
    });

    // print the results
    for (const auto &pair : freqVec) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // if the user wants to save the results to a file, do so
    if (askSave()) {
        ofstream outFile("results.txt"); // output file

        if (!outFile.is_open()) {
            cerr << "Failed to open the file for writing." << endl;
            return;
        }

        // add results line by line
        for (const auto &pair : freqVec) {
            outFile << pair.first << ": " << pair.second << endl;
        }

        outFile.close();

        cout << "Results saved to results.txt." << endl;
    }
    return;
}
void countWords(ifstream &file) {
    unordered_map<string, int> wordCount; // dictionary of words with their number of occurrences
    string line; // line of the iterated text file

    while (std::getline(file, line)) {
        istringstream stream(line);
        string word;

        // if it's not a number or punctuation, add it to the map (lowercase)
        while (stream >> word) {
            word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (!(any_of(word.begin(), word.end(), ::isdigit))) {
                wordCount[word]++;
            }
        }
    }

    file.close();

    vector<pair<string, int>> freqVec(wordCount.begin(), wordCount.end()); // vector form of the same map, so it can be sorted

    // sort the vector by number of occurrences
    sort(freqVec.begin(), freqVec.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
        return b.second < a.second;
    });

    // print the results
    cout << "Number of unique words: " << freqVec.size() << endl;
    cout << "Word frequencies:" << endl;
    for (const auto &pair : freqVec) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // if the user wants to save the results to a file, do so
    if (askSave()) {
        ofstream outFile("results.txt"); // output file

        if (!outFile.is_open()) {
            cerr << "Failed to open the file for writing." << endl;
            return;
        }

        outFile << "Number of unique words: " << freqVec.size() << endl;

        // add results line by line
        for (const auto &pair : freqVec) {
            outFile << pair.first << ": " << pair.second << endl;
        }

        outFile.close();

        cout << "Results saved to results.txt." << endl;
    }
    return;
}

bool askSave() {
    cout << "Would you like to save these frequencies to a file?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl << "> ";

    int num; // user choice for what to do
    bool cont = true; // whether the user entered a valid value
    do {
        string ans; // user input as a string
        getline(cin, ans);
        stringstream ss(ans);

        // if the user input a number (this doesn't check if it's actually 1 or 2)
        if (!(ss >> num)) {
            cerr << "Please enter a valid number, 1 or 2." << endl;
            cont =  false;
        } else {
            ss >> num;
            cont = true;
        }
    } while(!cont);
    
    switch (num) {
        case 1:
            return true;
        case 2:
            return false;
    }
}