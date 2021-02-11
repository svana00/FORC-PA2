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

private:
    int guessedWords;
    int hints;
    double totalScore;
    
};