#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "word.h"

using namespace std;

int maxWordLength = 20;
int numOfWords = 25936;

char *pick_word_from_list(char **wordsList)
{
    // Picks a random word from the list of words and returns a pointer to the
    // first letter of the word
    srand(time(NULL));
    int randWord = rand() % numOfWords;
    return wordsList[randWord];
}

void guess_word()
{
}

int main()
{
    // Create array
    char *charList = new char[numOfWords * maxWordLength];
    char **wordsList = new char *[numOfWords];

    ifstream fin;
    fin.open("word_list.fic", ios::binary);

    int counter = 0;
    for (int i = 0; i < numOfWords; i++)
    {
        wordsList[i] = &charList[counter];
        fin.read(&charList[counter++], 1);
        while (charList[counter - 1] != '\n')
        {
            fin.read(&charList[counter++], 1);
        }
        charList[counter - 1] = 0;
    }

    fin.read(&charList[counter++], 1);

    fin.close();

    char *word = pick_word_from_list(wordsList);

    // Find length of word
    int wordLength = 0;

    while (word[wordLength] != 0)
    {
        wordLength++;
    }

    // Create word class and test it
    Word *classWord;
    classWord = new Word(word, wordLength);
    char *originalWord = classWord->get_word();
    char *scrambledWord = classWord->get_scrambled();
    cout << "Actual word: " << originalWord << endl;
    cout << "Scrambled word: " << scrambledWord << endl;

    char choice = 'y';
    char *guess = new char[maxWordLength];

    while (choice == 'y')
    {
        cout << "Guess word: ";
        cin >> guess;
        cout << guess << endl;
        if (classWord->compare_guess(guess))
        {
            cout << "You guessed correct!" << endl;
            choice = 'n';
        }
        else
        {
            cout << "You guessed wrong!" << endl;
            cout << "Want to try again (y/n)? ";
            cin >> choice;
        }
    }

    // Delete all pointers
    delete classWord;
    delete originalWord;
    delete scrambledWord;
    delete[] charList;
    delete[] guess;
    delete[] wordsList;
    return 0;
}