#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "word.h"
#include "game.h"
#include "highScore.h"
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

bool sort_high_scores(HighScore *a, HighScore *b)
{
    return a->getScore() >= b->getScore();
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

        while (!gameOver && game->getHintsLeft() != 0 && !wordGuessed)
        {
            // Print inital instructions
            cout << "\nYour scrambled word: " << scrambledWord << endl;
            char *hintedWord = classWord->get_word_with_hints();
            cout << "Word with hints: " << hintedWord << "\n"
                 << endl;

            cout << "You have " << game->getHintsLeft() - 1 << " hints left!" << endl;
            cout << "Guess word (g)\nHint (h)\nSee highscores (s)\nQuit game (q)\n\nEnter choice: ";
            cin >> choice;

            if (choice == 'h')
            {
                classWord->show_hint();
                game->remove_hint();

                // If user has used up hints, game is over
                if (game->getHintsLeft() == 0)
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
                    game->word_guessed();
                    wordGuessed = true;
                    auto t2 = high_resolution_clock::now();
                    auto duration = duration_cast<seconds>(t2 - t1).count();

                    game->addToScore(56 / ((double) duration) - classWord->get_hint_counter()*5);
                    cout << "You guessed correct! It took you " << ((double) duration) << " seconds to guess this word" << endl;
                }
                else
                {
                    cout << "Wrong guess! " << endl;
                }
            }

            else if (choice == 's')
            {
                int counter = 0;
                int highScoreCounter = 0;
                double score;
                HighScore **classHighscores = new HighScore *[100];
                char *initials = new char[6];
                char *scoreArr = new char[10];

                // Open input stream
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
                for (int i = 0; i < highScoreCounter; i++)
                {
                    cout << classHighscores[i]->getScore() << endl;
                }

                // Delete all pointers
                for (int i = 0; i < highScoreCounter; i++)
                {
                    delete classHighscores[i];
                }

                delete[] initials;
                delete[] scoreArr;
                delete[] classHighscores;
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

        delete classWord;
        delete originalWord;
        delete scrambledWord;
        delete[] guess;
    }

    game->addToScore(game->getWordsGuessed() * 50);
    cout << "Your total score is: " << game->getTotalScore() << "\n"
         << endl;

    // Add to highscores
    ofstream fout;
    fout.open("high_scores.txt", fstream::app);

    char initials[5];
    cout << "Enter your initials to record your score: ";
    cin >> initials;
    fout << initials << ',' << game->getTotalScore() << endl;

    fout.close();

    delete game;
    delete[] charList;
    delete[] wordsList;
    return 0;
}