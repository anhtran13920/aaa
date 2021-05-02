#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
bool PrintWordAndCheckWin(string word, string guessed)
{
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++)
    {
        if (guessed.find(word[i]) == string::npos)
        {
            won = false;
            s += "_ ";
        }
        else
        {
            s += word[i];
            s += " ";
        }
    }

    cout << s << endl;

    return won;
}
string LoadRandomWord(string path)
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);

        int randomLine = rand() % v.size();

        word = v.at(randomLine);
        reader.close();
    }
    return word;
}

int main()
{
    srand(time(0));
    string wordToGuess;
    string fileName;
    string choice;

    cout << "What file stores the puzzle words?" << endl;
    cin >> fileName;

    cout << "Would you like to play hangman (yes,no)?\n";
    cin >> choice;
    while (choice == "yes") {
        int tries = 0;
        bool win = false;
        string guesses;
        wordToGuess = LoadRandomWord(fileName);     //get random word from file

        do {
            bool fault1 = false, fault2 = false;
            cout << "You currently have " << tries << " incorrect guesses.\n";
            cout << "Here is your puzzle:\n";

            win = PrintWordAndCheckWin(wordToGuess, guesses);

            if (win)
                break;

            char x;
            cout << "Please enter your guess.\n";
            cin >> x;

            if (guesses.find(x) == string::npos)
                guesses += x;
            else
                fault1 = true;
            if (wordToGuess.find(x) == string::npos)
                fault2 = true;

            if (!fault1 && !fault2)
                cout << "\nCongratulations, you guessed a letter in the puzzle!\n\n";
            if (fault1) {
                cout << "\nSorry, you have guessed that letter already.\n";
                cout << "Now it counts as a miss.";
                tries++;
            }
            else if (fault2) {
                cout << "\nSorry, that letter is NOT in the puzzle.\n";
                tries++;
            }
        } while (tries < 5);

        if (win)
            cout << "\nCongratulations! You got the correct word, " << wordToGuess << ".\n\n";
        else {
            cout << "Sorry, you have made 5 incorrect guesses, you lose.\n";
            cout << "The correct word was " << wordToGuess << ".\n\n";
        }

        cout << "Would you like to play hangman (yes,no)?\n";
        cin >> choice;
    }

    cout << "Thanks for playing!\n";

    system("pause");
    return 0;
}
