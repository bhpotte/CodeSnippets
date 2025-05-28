
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// simple printing tool
void printWord(string list)
{
    for (int i = 0; i < list.length(); i++)
    {
        cout << i;
    }
    cout << endl;
}

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
        int guesses = 0; // 6 guesses
        string guessedWord;

        string matches; // [X] = char is in the word. correct position
                                // [*X] = char is in the word, wrong position
                                // [_] = letter is not in the word

        while(guesses < 6)
        {
            cout << "Enter a five letter word" << endl;
            cin >> guessedWord;

            // compare each char to the chosen word
            for (int i = 0; i < chosenWord.length(); i++)
            {
                // if its in the correct position and is in the word
                if (guessedWord[i] == chosenWord[i])
                {
                    matches[i] = chosenWord[i];
                }
                // if its in the word, but wrong position
                if (guessedWord[i] != chosenWord[i] && chosenWord.find(guessedWord[i]))
                {
                    matches[i] = '*'+guessedWord[i];
                }
                // else, its not in the word
                else
                {
                    matches[i] = '_';
                }
            }

            printWord(matches);
            if (matches == chosenWord)
            {
                cout << "Good Job!" << endl;
                guesses = 7;
            }
            else
            {
                guesses++;
            }
        }

        wordFile.close();
    }

    return 0;
}