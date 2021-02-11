#include <iostream>
using namespace std;

class HighScore
{
public:
    HighScore(char* initals, double score);
    char* getInitials();
    double getScore();
    bool sorting();

private:
    char* initials;
    double score;
};