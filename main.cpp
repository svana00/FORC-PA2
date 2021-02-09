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

    cout << allWordsArray << endl;

    fin.close();
    return 0;
}