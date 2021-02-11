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