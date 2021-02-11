
#include "word.h"
#include <stdlib.h>

using namespace std;

Word::Word(char *wordList, int wordLength)
{
    this->wordLength = wordLength;
    this->word = new char[wordLength];
    this->scrambled = new char[wordLength];
    this->hintWord = new char[wordLength];
    this->hintCounter = 0;

    // Fill the word and scrambled lists
    for (int i = 0; i < wordLength; i++)
    {
        this->word[i] = wordList[i];
        this->scrambled[i] = wordList[i];
        this->hintWord[i] = '-';
    }

    scramble_word();
}

char *Word::get_word()
{
    return this->word;
}

char *Word::get_scrambled()
{
    return this->scrambled;
}

char *Word::get_word_with_hints()
{
    return this->hintWord;
}

bool Word::compare_guess(char *guess)
{
    for (int i = 0; i < wordLength; i++)
    {
        if (guess[i] != word[i])
        {
            return false;
        }
    }
    return true;
}

void Word::show_hint()
{
    srand(time(NULL));

    if (this->hintCounter != this->wordLength) {
        int index = rand() % this->wordLength;
        while (this->hintWord[index] != '-')
        {
            index = rand() % this->wordLength;
            
        }
        this->hintWord[index] = this->word[index];
        this->hintCounter++;
    }
    else {
        cout << endl << "You have used all your hints for this word! Now you can guess it" << endl;
    }
    
}

void Word::scramble_word()
{
    srand(time(NULL));

    char tempChar;
    for (int i = 0; i < 20; i++)
    {
        // Find two indexes to switch
        int letterOneIndex = rand() % this->wordLength;
        int letterTwoIndex = rand() % this->wordLength;

        // Make sure the two numbers are unique
        while (letterOneIndex == letterTwoIndex)
        {
            letterTwoIndex = rand() % this->wordLength;
        }

        // Switch places in the scrambled list
        tempChar = this->scrambled[letterOneIndex];
        this->scrambled[letterOneIndex] = this->scrambled[letterTwoIndex];
        this->scrambled[letterTwoIndex] = tempChar;
    }
}

int Word::get_hint_counter() {
    return this->hintCounter;
}