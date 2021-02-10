class Game
{
public:
    Game();
    void remove_point();
    void word_guessed();
    int getPoints();
    int getWordsGuessed();

private:
    int guessedWords;
    int points;
};