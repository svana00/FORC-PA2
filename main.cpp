#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int maxWordLength = 20;
int numOfWords = 25936;

char* pick_word_from_list(char* wordsList)
{
    int randWord = rand() % numOfWords;
    return &wordsList[randWord]; 
}

void scramble_word()
{
}

void show_scrambled_word()
{
}

void guess_word()
{
}

int main()
{
    // Create array
    char wordsList[numOfWords][maxWordLength];

    ifstream fin;
    fin.open("word_list.fic", ios::binary);

    for (int i = 0; i < numOfWords; i++)
    {
        int counter = 1;
        fin.read(&wordsList[i][0], 1);

        while (wordsList[i][counter - 1] != '\n')
        {
            fin.read(&wordsList[i][counter], 1);
            counter++;
        }

        wordsList[i][counter - 1] = 0;
        cout << wordsList[i] << endl;
    }

    fin.close();
    return 0;
}