#include <iostream>
using namespace std;

class Word
{
public:
    Word(int height, int stamina, int strength);

    //void add_item(char *name, double bonus);
    void add_item();

private:
    int height;
    int stamina;
    int strength;

    int item_count;
};