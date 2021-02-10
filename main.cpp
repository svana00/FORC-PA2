#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "word.h"
#include "game.h"

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
    }

    fin.read(&charList[counter++], 1);

    fin.close();

    // Create the current game
    Game *game;
    game = new Game();

    bool wordGuessed = false;
    bool gameOver = false;

    cout << "\n------------------- HANGMAN ------------------- \nThe rules are simple. You have 10 hints in total and can guess as many words as \nyou want before there are no hints left.\nYour total score is how many words you can guess.\n"
         << endl;

    while (gameOver != true)
    {
        wordGuessed = false;
        gameOver = false;

        char *word = pick_word_from_list(wordsList);

        // Find length of word
        int wordLength = 0;

        while (word[wordLength] != 0)
        {
            wordLength++;
        }

        // Create word class and test it
        Word *classWord;
        classWord = new Word(word, wordLength);
        char *originalWord = classWord->get_word();
        char *scrambledWord = classWord->get_scrambled();

        char continueGame = 'y';
        char choice;
        char *guess = new char[maxWordLength];

        while (!gameOver && game->getPoints() != 0 && !wordGuessed)
        {
            // Print inital instructions
            cout << "Your scrambled word: " << scrambledWord << "\n"
                 << endl;

            cout << "Guess word (g)\nHint (h)\nQuit game (q)\n\nEnter choice: ";
            cin >> choice;

            if (choice == 'h')
            {
                classWord->show_hint();
                char *hintedWord = classWord->get_word_with_hints();
                cout << "\nWord with hints: " << hintedWord << endl;
                game->remove_point();
                cout << "Points left: " << game->getPoints() << endl;

                // If user has used up guesses, game is over
                if (game->getPoints() == 0)
                {
                    cout << "\nGame over!" << endl;
                    cout << "You managed to guess " << game->getWordsGuessed() << " word/s\n"
                         << endl;
                    gameOver = true;
                }
            }

            else if (choice == 'g')
            {
                cout << "Guess word: ";
                cin >> guess;
                cout << "\n";

                if (classWord->compare_guess(guess))
                {
                    cout << "You guessed correct!" << endl;
                    game->word_guessed();
                    wordGuessed = true;
                }
                else
                {
                    cout << "Wrong guess! " << endl;
                }
            }
            else
            {
                gameOver = true;
            }
        }

        // Delete all pointers
        delete classWord;
        delete originalWord;
        delete scrambledWord;
        delete[] guess;
    }

    delete[] charList;
    delete[] wordsList;
    return 0;
}