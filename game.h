class Game
{
public:
    Game();
    void remove_hint();
    void word_guessed();
    int getHintsLeft();
    int getWordsGuessed();
    void addToScore(double points);
    double getTotalScore();
    void printFinalScore();

private:
    int guessedWords;
    int hints;
    double totalScore;
};