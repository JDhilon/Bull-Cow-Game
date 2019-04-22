/*  Defines FBullCowGame class to handle game logic.
*/

#pragma once
#include <string>
#include <cctype>

using FString = std::string;
using int32 = int;

//  Allows for proper classifications of incorrect inputs
enum class EWordStatus{
    Invalid,
    OK, 
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

//  Bull is a correct letter in the correct spot, Cow is a correct letter in an incorrect spot
struct BullCowCount {
    int32 bulls = 0;
    int32 cows = 0;
};

// Class definition
class FBullCowGame {
public:
    FBullCowGame();

    int32 getMaxTries() const;
    int32 getCurrentTry() const;
    FString getHiddenWord() const;
    EWordStatus checkGuessValid(FString) const;
    bool isGameWon() const;

    void reset();
    BullCowCount submitGuess(FString);

private:
    int32 max_tries;
    int32 current_try;
    FString hidden_word;
    bool game_won;
    
    bool isIsogram(FString) const;
    bool isLowercase(FString) const;
    
    FString initHiddenWord(int32);
};
