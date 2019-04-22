/*  Handles game logic for bull cow game.
*/

#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

//  Calls reset to set game to beginning state
FBullCowGame::FBullCowGame() 
{
    reset();
}

//  Getter methods
int32 FBullCowGame::getCurrentTry() const {return current_try;}
FString FBullCowGame::getHiddenWord() const {return hidden_word;}
bool FBullCowGame::isGameWon() const {return game_won;}

int32 FBullCowGame::getMaxTries() const
{
    TMap<int32, int32> word_length_to_tries { {3,5}, {4,8}, {5,12}, {6,16}, {7,19}, {8, 22} }; 
    return word_length_to_tries[hidden_word.length()];
}

//  Returns game to beginning state. 
void FBullCowGame::reset()
{
    hidden_word = initHiddenWord(6); // TODO initialize this with input from user on length
    max_tries = getMaxTries();
    current_try = 1;
    game_won = false;
    return;
}

//  TODO add functionality to return a random isogram based on word length desired
FString FBullCowGame::initHiddenWord(int32 length)
{
    return "planet";
}

//  Calls helper method to error check user guess
EWordStatus FBullCowGame::checkGuessValid(FString guess) const
{
    if(guess.length() != hidden_word.length()){
        return EWordStatus::Wrong_Length;
    }

    if(!isLowercase(guess)){
        return EWordStatus::Not_Lowercase;
    }

    if(!isIsogram(guess)){
        return EWordStatus::Not_Isogram;
    }

    return EWordStatus::OK;
}

bool FBullCowGame::isLowercase(FString word) const
{
    for(auto letter : word){
        if(!islower(letter)){
            return false;
        }
    }
    return true;
}

bool FBullCowGame::isIsogram(FString word) const
{
    TMap<char,bool> map;
    for(auto letter : word){
        if(map[letter]){
            return false;
        }
        else{
            map[letter] = true;
        }
    }
    return true;
}

//  Loops through user guess and returns bulls and cows. 
//  Assumes isogram input of proper length (checking provided by checkGuessValid)
BullCowCount FBullCowGame::submitGuess(FString guess){
    current_try ++;
    BullCowCount count;
    for(int32 i = 0; i < guess.length(); i++){
        for(int32 j = 0; j < hidden_word.length(); j++){
            if(guess[i] == hidden_word[j]){
                if(i == j){
                    count.bulls ++;
                }
                else{
                    count.cows ++;
                }
            }
        }
    }

    if(guess == hidden_word){
        game_won = true;
    }

    return count;
}