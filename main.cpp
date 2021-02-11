#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "word.h"
#include "game.h"
#include <time.h> /* clock_t, clock, CLOCKS_PER_SEC */
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

        auto t1 = high_resolution_clock::now();

        while (!gameOver && game->getPoints() != 0 && !wordGuessed)
        {
            // Print inital instructions
            cout << "\nYour scrambled word: " << scrambledWord << endl;
            char *hintedWord = classWord->get_word_with_hints();
            cout << "Word with hints: " << hintedWord << "\n"
                 << endl;

            cout << "You have " << game->getPoints() << " hints left!" << endl;
            cout << "Guess word (g)\nHint (h)\nQuit game (q)\n\nEnter choice: ";
            cin >> choice;

            if (choice == 'h')
            {
                classWord->show_hint();
                game->remove_point();

                // If user has used up hints, game is over
                if (game->getPoints() == 0)
                {
                    cout << "\nGame over! The word was " << classWord->get_word() << endl;
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
                    auto t2 = high_resolution_clock::now();
                    auto duration = duration_cast(seconds(t2 - t1));

                    cout << "Time elapsed: " << endl;
                }
                else
                {
                    cout << "Wrong guess! " << endl;
                }
            }

            else if (choice == 'q')
            {
                cout << "You quit the game. The word was " << classWord->get_word() << endl;
                cout << "You managed to guess " << game->getWordsGuessed() << " word/s\n"
                     << endl;
                gameOver = true;
            }

            else
            {
                cout << "Unkown command, try again!" << endl;
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