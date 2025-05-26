/*
Word_List_Separator is a simple tool that allows you to take a list of words
in 1 text file and separate the words by their letter length to other text files.

It makes it easier to decide what words we want to work with depending on how many
letters we want to work with (Such as only working with 5-letter words).abort
I also included toupper because I want all words to be uppercase for the future.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    // error checking
    if (argc != 3)
    {
        cerr << "Usage: ./somename <wordList.txt> <newFile.txt>" << endl;
        return 1;
    }

    int wordLen;

    // specify word length target user wants
    cout << "How many letters you want to put into a separate list?" << endl;
    cout << "Recommended: 3-7" << endl;
    cin >> wordLen;

    // read into word list
    ifstream readFile(argv[1]);
    ofstream newFile(argv[2]);
    string line;

    // open both files, read in to the first one and copy contents to the second file
    if (readFile.is_open() && newFile.is_open())
    {
        while(getline(readFile,line))
        {
            // if we find a word that matches the length, append to file
            if (line.length() == wordLen)
            {
                for(int i = 0; i < line.length(); i++)
                {
                    line[i] = toupper(line[i]);
                }
                newFile << line << endl;
            }
        }
        readFile.close();
        newFile.close();
    }
    else
    {
        cerr << "Error: Had trouble opening files." << endl;
        return 1;
    }

    return 0;
}