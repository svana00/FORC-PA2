#include <iostream>
using namespace std;

class Word
{
public:
    Word(char *wordList, int wordLength);

    char *wordList;
    int wordLength;
    //void add_item(char *name, double bonus);
    void show_scrambled_word();
    void scramble_word();

private:
    int height;
    int stamina;
    int strength;

    int item_count;
};