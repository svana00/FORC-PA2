#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "word.h"
#include "game.h"
#include "helpers.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int maxWordLength = 20;
int numOfWords = 25936;

int main()
{
    // Create arrays
    char *charList = new char[numOfWords * maxWordLength];
    char **wordsList = new char *[numOfWords];

    ifstream fin;
    fin.open("word_list.fic", ios::binary);

    // Read from file into the arrays
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

    // Print start screen
    cout << "\n------------------- HANGMAN -------------------" << endl;
    cout << "\nThe rules are simple. You have 10 hints in total and can guess \nas many words as you want before there are no hints left.\nYour total score is how many words you can guess."
         << endl;

    // Create the current game and variables
    Game *game;
    game = new Game();
    bool wordGuessed = false;
    bool gameOver = false;

    while (gameOver != true)
    {
        wordGuessed = false;
        gameOver = false;

        // Get a random word from the array
        char *word = pick_word_from_list(wordsList);

        // Find length of word
        int wordLength = 0;
        while (word[wordLength] != 0)
        {
            wordLength++;
        }

        // Create classes and variables for game
        Word *classWord;
        classWord = new Word(word, wordLength);
        char *originalWord = classWord->get_word();
        char *scrambledWord = classWord->get_scrambled();
        char *guess = new char[maxWordLength];
        char choice;

        // Start the timer
        auto t1 = high_resolution_clock::now();

        // Start the round
        while (!gameOver && game->getHintsLeft() != 0 && !wordGuessed)
        {
            // Print main instructions
            cout << "\n------------------- GAME -------------------" << endl;
            cout << "\nYour scrambled word: " << scrambledWord << endl;
            char *hintedWord = classWord->get_word_with_hints();
            cout << "Word with hints: " << hintedWord << "\n"
                 << endl;
            cout << "You have " << game->getHintsLeft() - 1 << " hints left!" << endl;
            cout << "\n1. Guess word\n2. Hint\n3. See highscores\n4. Quit game\n\nEnter choice: ";
            cin >> choice;

            if (choice == '1')
            {
                cout << "Guess word: ";
                cin >> guess;
                cout << "\n";

                // Check if word matches
                if (classWord->compare_guess(guess))
                {
                    game->word_guessed();
                    wordGuessed = true;

                    // Stop the timer
                    auto t2 = high_resolution_clock::now();
                    auto duration = duration_cast<seconds>(t2 - t1).count();

                    // Calculate score from time and how many hints are left
                    game->addToScore(56 / ((double)duration));
                    cout << "You guessed correct! It took you " << ((double)duration) << " seconds to guess this word" << endl;

                    // Let user press a key to keep playing
                    char backToMenu;
                    cout << "\nEnter any letter to continue: ";
                    cin >> backToMenu;
                }
                else
                {
                    cout << "Wrong guess! :(" << endl;
                }
            }

            else if (choice == '2')
            {
                if (classWord->get_hint_counter() != classWord->get_word_length())
                {
                    game->remove_hint();
                }
                classWord->show_hint();

                // If user has used up hints, game is over
                if (game->getHintsLeft() == 0)
                {
                    cout << "\n------------------- GAME OVER -------------------" << endl;
                    cout << "\nGame over! The word was " << classWord->get_word() << endl;
                    cout << "You managed to guess " << game->getWordsGuessed() << " word/s\n"
                         << endl;

                    gameOver = true;
                }
            }

            else if (choice == '3')
            {
                int counter = 0;
                int highScoreCounter = 0;
                double score;
                HighScore **classHighscores = new HighScore *[100];
                char *initials = new char[6];
                char *scoreArr = new char[10];

                // Open the high scores file and read from it
                ifstream highScores;
                highScores.open("high_scores.txt");

                while (highScores.read(&initials[counter++], 1))
                {
                    // Find the initials
                    while (initials[counter - 1] != ',')
                    {
                        highScores.read(&initials[counter++], 1);
                    }
                    initials[counter - 1] = 0;
                    counter = 0;

                    // Find the score
                    while (scoreArr[counter - 1] != '\n')
                    {
                        highScores.read(&scoreArr[counter++], 1);
                    }
                    counter = 0;
                    score = atof(scoreArr);

                    HighScore *hs;
                    hs = new HighScore(initials, score);
                    classHighscores[highScoreCounter++] = hs;

                    // Sort the list
                    sort(classHighscores, classHighscores + highScoreCounter, sort_high_scores);
                }

                highScores.close();

                char choice;
                cout << "\n------------------- HIGHSCORES -------------------" << endl;
                cout << "\n1. See all highscores\n2. See top 5\n\nEnter choice: ";
                cin >> choice;

                cout << "\n";
                if (choice == '1' || highScoreCounter < 5)
                {
                    for (int i = 0; i < highScoreCounter; i++)
                    {
                        cout << "Score " << i + 1 << ": " << classHighscores[i]->getScore() << " by " << classHighscores[i]->getInitials() << endl;
                    }
                }
                else if (choice == '2')
                {
                    for (int i = 0; i < 5; i++)
                    {
                        cout << "Score " << i + 1 << ": " << classHighscores[i]->getScore() << " by " << classHighscores[i]->getInitials() << endl;
                    }
                }

                // Let user press a key to keep playing
                char backToMenu;
                cout << "\nEnter any letter to continue: ";
                cin >> backToMenu;

                // Delete all pointers
                for (int i = 0; i < highScoreCounter; i++)
                {
                    delete classHighscores[i];
                }
                delete[] initials;
                delete[] scoreArr;
                delete[] classHighscores;
            }

            else if (choice == '4')
            {
                cout << "\n------------------- GAME OVER -------------------" << endl;
                cout << "\nYou quit the game. The word was " << classWord->get_word() << endl;
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

    // Calculate and output final score
    game->printFinalScore();

    // Add to highscores
    ofstream fout;
    fout.open("high_scores.txt", fstream::app);

    char initials[5];
    cout << "Enter your initials to record your score (max 5 letters): ";
    cin >> initials;
    fout << initials << ',' << game->getTotalScore() << endl;

    fout.close();

    delete game;
    delete[] charList;
    delete[] wordsList;
    return 0;
}