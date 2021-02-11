#include "highScore.h"
#include <stdlib.h>

using namespace std;

HighScore::HighScore(char *initials, double score)
{
    this->initials = initials;
    this->score = score;
}

double HighScore::getScore()
{
    return this->score;
}

char *HighScore::getInitials()
{
    return this->initials;
}