#include <iostream>
#include "helpers.h"

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