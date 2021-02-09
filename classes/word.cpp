
#include "word.h"

using namespace std;

Word::Word(int height, int stamina, int strength)
{
    this->height = height;
    this->stamina = stamina;
    this->strength = strength;

    item_count = 0;
}

void Word::add_item()
{
}