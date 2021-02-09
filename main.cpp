#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int maxWordLength = 20;
int numOfWords = 25936;

char *pick_word_from_list(char **wordsList)
{
    // Picks a random word from the list of words and returns a pointer to the
    // first letter of the word
    srand(time(NULL));
    int randWord = rand() % numOfWords;
    return wordsList[randWord];
}

void guess_word()
{
}

int main()
{
    // Create array
    char *charList = new char[numOfWords * maxWordLength];
    char **wordsList = new char *[numOfWords];

    ifstream fin;
    fin.open("word_list.fic", ios::binary);

    int counter = 0;
    for (int i = 0; i < numOfWords; i++)
    {
        wordsList[i] = &charList[counter];
        fin.read(&charList[counter++], 1);
        while (charList[counter - 1] != '\n')
        {
            fin.read(&charList[counter++], 1);
        }
        charList[counter - 1] = 0;
        cout << wordsList[i] << endl;
    }

    fin.close();

    char *word = pick_word_from_list(wordsList);
    cout << word << endl;

    delete[] charList;
    delete[] wordsList;
    return 0;
}