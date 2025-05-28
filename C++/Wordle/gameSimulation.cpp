
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // variables
    int userChoice;
    int fileSize = 0;
    vector<string> wordList;
    string chosenWord;
    string word;
    ifstream wordFile("fiveOnly.txt");

    // srand variable to force different random words every time we run the program
    srand(time(0));

    // basic interface for now
    cout << "Get 6 chances to guess a 5-letter word." << endl;
    cout << "Select a game mode: -------------------" << endl;

    // error checking
    // if user inputs an invalid option, return to selection
    while (userChoice != 1 && userChoice !=2)
    {
        cout << "Press 1 for Normal mode" << endl;
        cout << "Press 2 for Hard mode" << endl;
        cin >> userChoice;
        if (userChoice < 1 || userChoice > 2)
        {
            cout << "Invalid Response. Try Again." << endl;
        }
    }
    
    // normal mode
    if(wordFile.is_open())
    {
        // put contents of file into an array
        while(getline(wordFile, word))
        {
            // determine file size
            fileSize++;
            wordList.push_back(word);
        }

        // randomly select a word from the array
        chosenWord = wordList[rand() % fileSize];

        // fun part; user plays the game
        int guesses = 0;
        string guessedWord;
        while(guesses < 6)
        {
            cout << "Enter a five letter word" << endl;
            cin >> guessedWord;
        }

        wordFile.close();
    }

    return 0;
}