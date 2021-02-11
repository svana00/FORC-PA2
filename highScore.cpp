#include "highScore.h"
#include <stdlib.h>

using namespace std;

HighScore::HighScore(char *initials, double score)
{
    cout << initials << endl;
    cout << score << endl;

    this->initials = initials;
    this->score = score;
}

bool operator<(HighScore a, HighScore b)
{
    if (a.getScore() <= b.getScore())
        return true;
    return false;
}

double HighScore::getScore()
{
    return this->score;
}

char *HighScore::getInitials()
{
    return this->initials;
}