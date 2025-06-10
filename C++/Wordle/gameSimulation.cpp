/*
Bugs to decode:
sometimes the guessed word would give incorrect hints ( a_A__ for FLAWN)
*/





#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// wordToUpper simply prints the word in only uppercase format
string wordToUpper(string word)
{
    for (int i = 0; i < word.length(); i++)
    {
        word[i] = toupper(word[i]);
    }

    return word;
}

int main()
{
    // variables
    char userChoice;
    int fileSize = 0;
    int guesses = 6; // 6 guesses to use
    string chosenWord;
    string guessedWord;
    string usedLetters = "";
    unordered_map<char, int> letterCount;
    unordered_map<char, int> dupes;
    unordered_map<char, vector<int>> hardModeCorrectPos;
    vector<char> hardModeWrongPos;
    vector<string> wordList;
    ifstream wordFile("fiveOnly.txt");

    // srand variable to force different random words every time we run the program
    srand(time(0));

    // basic interface for now
    cout << "Get 6 chances to guess a 5-letter word." << endl;
    cout << "Select a game mode: -------------------" << endl;

    // error checking
    // if user inputs an invalid option, return to selection
    // Note: might add strict mode as an option later down the line
    while (userChoice != 'Y' && userChoice != 'N')
    {
        cout << "Do you want to play Hard Mode? (Y/N)" << endl;
        cin >> userChoice;
        userChoice = toupper(userChoice);
        if (userChoice == 'Y' || userChoice == 'N')
        {
            continue; // exit the loop
        }
        else
        {
            cout << "Invalid Response. Try Again." << endl;
        }
    }
    
    if(wordFile.is_open())
    {
        string line;
        // put contents of file into an array
        while(getline(wordFile, line))
        {
            // determine file size
            fileSize++;
            wordList.push_back(line);
        }

        // randomly select a word from the array
        chosenWord = wordList[rand() % fileSize];

        // update dupes to find if any duplicates are found in the chosen word.
        for (int i = 0; i < chosenWord.length(); i++)
        {
            dupes[chosenWord[i]]++;
        }

        // fun part; user plays the game
        while(guesses > 0)
        {
            // refresh each match and letterCount
            string matches = "_____"; // [X] = char is in the word. correct position
                                // [x] = char is in the word, wrong position
                                // [_] = letter is not in the word
            letterCount.clear();

            // helpful stats
            cout << "Used letters: ";
            for (int i = 0; i < usedLetters.length(); i++)
            {
                cout << usedLetters[i];
            }
            cout << endl << "Guesses left: " << guesses << endl;


            bool invalid = true;


            while(invalid)
            {
                cout << "Enter a five letter word:" << endl;
                cin >> guessedWord;
                guessedWord = wordToUpper(guessedWord);

                // rule 0: Word has to be 5 letters
                if (guessedWord.length() != 5)
                {
                    cout << "Word must be 5 letters" << endl << endl;
                    invalid = true;
                }

                // rule 1: Word has to be in the word list
                for (const auto word : wordList)
                {
                   if (guessedWord == word)
                   {
                        invalid = false;
                   }
                }

                if (invalid == true && guessedWord.length() == 5)
                {
                    cout << "Word not in word list." << endl << endl;
                }

                // hard mode module
                if (userChoice == 'Y' && guesses >= 1 && invalid == false && guessedWord.length() == 5)
                {
                    // rule 2: word has to have the correct guessed letter 
                    // in the correct position
                    for (const auto& pair : hardModeCorrectPos)
                    {
                        for (int loc : pair.second)
                        {
                            if (guessedWord[loc] != pair.first)
                            {
                                invalid = true;
                                cout << "Word must have the letter " << pair.first << 
                                " at position " << loc+1 << endl << endl;
                            }
                        }
                    }

                    // rule 3: word has to have a letter IF the guessed word
                    // has it identified (doesn't have to be in the right position)
                    for (const auto letter : hardModeWrongPos)
                    {
                        if (guessedWord.find(letter) != string::npos)
                        {
                            invalid = false;
                        }
                        else
                        {
                            cout << "Word must have the letter " << letter << endl << endl;
                            invalid = true;
                        }
                    }

                }
            }

            // to avoid duplicates
            hardModeCorrectPos.clear();
            hardModeWrongPos.clear();

            // compare each char to the chosen word
            for (int i = 0; i < chosenWord.length(); i++)
            {
                // if its in the correct position and is in the word
                if (guessedWord[i] == chosenWord[i])
                {
                    // if we are in hard mode, add the letter to the map with correct position
                    if (userChoice == 'Y')
                    {
                        hardModeCorrectPos[guessedWord[i]].push_back(i);
                    }

                    matches[i] = guessedWord[i];
                }
                // else if its in the word, wrong position, and potentially has multiple same letters
                else if (chosenWord.find(guessedWord[i]) != string::npos && 
                    letterCount[guessedWord[i]] < dupes[guessedWord[i]])
                {
                    // if we are in hard mode, if wrong position, add to list
                    if (userChoice == 'Y')
                    {
                        hardModeWrongPos.push_back(guessedWord[i]);
                    }
        
                    letterCount[guessedWord[i]]++;
                    matches[i] = tolower(guessedWord[i]);
                }
                // else, its not in the word
                else
                {
                    matches[i] = '_';
                    
                    // Only add if not already in usedLetters
                    if (usedLetters.find(guessedWord[i]) == string::npos)
                    {
                        usedLetters += guessedWord[i];
                    }
                }
            }

            // shows what letters you got right; what position they're in
            cout << matches << endl << endl;
            
            if (guessedWord == chosenWord)
            {
                cout << "Good Job!" << endl;
                guesses = 0;
            }
            // else, we still got guesses left
            else
            {
                guesses--;
            }

            // we reached the limit of guesses
            if (guesses == 0)
            {
                cout << "The word was: " << chosenWord << endl;
            }
        }

        wordFile.close();
    }

    return 0;
}