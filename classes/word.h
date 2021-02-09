#include <iostream>
using namespace std;

class Word
{
public:
    Word(char *wordList, int wordLength);

    void show_scrambled_word();
    void scramble_word();

private:
    char *wordList;
    int wordLength;
};