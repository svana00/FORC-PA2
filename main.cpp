#include <iostream>
#include <fstream>

using namespace std;

void pick_word_from_file()
{
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
    int maxWordLength, numOfWords;
    maxWordLength = 20;
    numOfWords = 25936;
    char allWordsArray[numOfWords][maxWordLength];

    ifstream fin;
    fin.open("word_list.fic", ios::binary);

    for (int i = 0; i < numOfWords; i++)
    {
        int counter = 1;
        fin.read(&allWordsArray[i][0], 1);

        while (allWordsArray[i][counter - 1] != '\n')
        {
            fin.read(&allWordsArray[i][counter], 1);
            counter++;
        }

        allWordsArray[i][counter - 1] = 0;
        cout << allWordsArray[i] << endl;
    }

        fin.close();
    return 0;
}