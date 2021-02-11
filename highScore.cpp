#include "highScore.h"
#include <stdlib.h>

using namespace std;

HighScore::HighScore(char *initials, double score)
{
    this->initialsArr = new char[6];
    this->score = score;

    for (int i = 0; i < 6; i++)
    {
        this->initialsArr[i] = initials[i];
    }
}

double HighScore::getScore()
{
    return this->score;
}

char *HighScore::getInitials()
{
    cout << this->initialsArr << endl;
    return this->initialsArr;
}