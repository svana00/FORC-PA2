# PA2 - FORC
## Version

We implemented version C with no bonuses.

## Compile

Compile with the command:
    g++ -o main.exe *.cpp

## Run code
Run the code with the command:
    ./main.exe

## Other
The score is calculated in the following way:
    - Each correct word gives you 50 points.
    - 56 is divided by the time it takes for the user to guess the word and the outcome is added to the score (the number    seemed nice, no reason for it)
    - Lastly, hints you have left is multiplied by 3 and the outcome is added to the final score.
    Meaning that the fewer hints you have left, the lower bonus you get.
