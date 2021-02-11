#include <iostream>
using namespace std;

class Word
{
public:
    Word(char *wordList, int wordLength);

    void scramble_word();
    void show_hint();
    char *get_word();
    char *get_scrambled();
    char *get_word_with_hints();
    bool compare_guess(char *guess);
    int get_hint_counter();

private:
    int wordLength;
    char *word;
    char *scrambled;
    char *hintWord;
    int hintCounter;
};