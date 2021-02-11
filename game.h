class Game
{
public:
    Game();
    void remove_hint();
    void word_guessed();
    int getPoints();
    int getWordsGuessed();

private:
    int guessedWords;
    int hints;
};