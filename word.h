#include <iostream>
using namespace std;

class Word
{
public:
    Word(char *wordList, int wordLength);

    void scramble_word();
    char *get_word();
    char *get_scrambled();
    bool compare_guess(char *guess);

private:
    int wordLength;
    char *word;
    char *scrambled;
};