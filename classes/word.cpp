
#include "word.h"
#include <string.h>

using namespace std;

Word::Word(char *wordList, int wordLength)
{
    this->wordList = wordList;
    this->word = new char [wordLength];
    this->wordLength = wordLength;
    this->scrambled = new char [wordLength];


}

void Word::scramble_word()
{
}

void Word::show_scrambled_word()
{
}