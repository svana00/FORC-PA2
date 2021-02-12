#include <iostream>
#include "helpers.h"

using namespace std;

char *pick_word_from_list(char **wordsList)
{
    // Picks a random word from the list of words and returns a pointer to the
    // first letter of the word
    srand(time(NULL));
    int randWord = rand() % 25936;
    return wordsList[randWord];
}

bool sort_high_scores(HighScore *a, HighScore *b)
{
    return a->getScore() >= b->getScore();
}

void enterKey()
{
    // Let user press a key to keep playing
    char backToMenu;
    cout << "\nEnter any letter to continue: ";
    cin >> backToMenu;
}