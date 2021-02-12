#include <iostream>
#include "game.h"
#include <stdlib.h>

using namespace std;

Game::Game()
{
    this->guessedWords = 0;
    this->hints = 10;
}

int Game::getHintsLeft()
{
    return this->hints;
}

int Game::getWordsGuessed()
{
    return this->guessedWords;
}

void Game::remove_hint()
{
    this->hints--;
}

void Game::word_guessed()
{
    this->guessedWords++;
}

void Game::addToScore(double points)
{
    this->totalScore += points;
}

double Game::getTotalScore()
{
    return this->totalScore;
}

void Game::printFinalScore()
{
    if (this->guessedWords != 0)
    {
        this->addToScore(this->guessedWords * 50 + this->hints * 3);
        cout << "Your total score is: " << this->totalScore << "\n"
             << endl;
    }
    else
    {
        cout << "Your total score is: " << this->totalScore << "\n"
             << endl;
    }
}