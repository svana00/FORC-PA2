
#include "word.h"

using namespace std;

Word::Word(char *wordList, int wordLength)
{
    this->wordLength = wordLength;
    this->word = new char[wordLength];
    this->scrambled = new char[wordLength];

    // Fill the word and scrambled lists
    for (int i = 0; i < wordLength; i++)
    {
        this->word[i] = wordList[i];
        this->scrambled[i] = wordList[i];
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