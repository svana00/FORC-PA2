#include "game.h"
#include <stdlib.h>

using namespace std;

Game::Game()
{
    this->guessedWords = 0;
    this->points = 10;
}

int Game::getPoints()
{
    return this->points;
}

int Game::getWordsGuessed()
{
    return this->guessedWords;
}

void Game::remove_point()
{
    this->points--;
}

void Game::word_guessed()
{
    this->guessedWords++;
}