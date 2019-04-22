/*  Console executable for the BullCowGame.
    Handles user interactions.
    FBullCowGame class contains gameplay logic.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

// Initiate game
FBullCowGame game;

//  Prototypes
void showGuess(FText guess);
FText getValidGuess();
void printIntro();
void playGame();
bool replayGame();
void summarizeGame();

//  TODO initiate game with user input on word length
int main()
{
    bool keep_playing = true;

    printIntro();

    while(keep_playing){
        playGame();
        keep_playing = replayGame();
    }
    
    return 0;
}

//  Loops until won or max tries reached
void playGame()
{
    game.reset();
    while(!game.isGameWon() && game.getCurrentTry() <= game.getMaxTries()){
        FText user_guess = getValidGuess();
        BullCowCount count = game.submitGuess(user_guess);
        std::cout << "Bulls = " << count.bulls;
        std::cout << ". Cows = " << count.cows << "\n\n";
    }
    summarizeGame();
    return;
}

//  Asks user if they want to replay game.
//  TODO give option to change word
bool replayGame()
{
    FText response = "";
    std::cout << "Do you want to play again with the same word? Y/N : ";
    getline(std::cin, response);
    return (response[0] == 'y' || response [0] =='Y');

}

void printIntro()
{
    std::cout << std::endl;
    std::cout << "Welcome to Bulls and Cows, a fun word game\n";
    std::cout << "Can you guess the " << game.getHiddenWord().length();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;

}

//  Gets a valid guess from user, printing error messages for incorrect attempts
FText getValidGuess()
{
    int32 count = 0;
    FText guess = "";
    EWordStatus status = EWordStatus::Invalid;
    do {
        count ++;
        int32 try_num = 0;
        try_num = game.getCurrentTry();
        std::cout << "Try " << try_num << " of " << game.getMaxTries() <<". Enter your guess ... ";
        getline(std::cin, guess);
        status = game.checkGuessValid(guess);
        switch (status){
            case EWordStatus::Wrong_Length:
                std::cout << "Please enter a " << game.getHiddenWord().length() << " letter word.\n\n";
                break;
            case EWordStatus::Not_Isogram:
                std::cout << "Please enter an isogram. An isogram has NO repeating letters.\n\n";
                break;
            case EWordStatus::Not_Lowercase:
                std::cout << "Please enter a word in lower case only.\n\n";
                break;
            default:
                //  Assume guess is valid
                break;
        }
        std::cout << std::endl;
    } while(status != EWordStatus::OK);

    return guess;
}

void showGuess(FText guess)
{
    std::cout << "Your guess was: " << guess << std::endl;
}

//  Recaps game and prints summary to console
void summarizeGame(){
    if(game.isGameWon()){
        std::cout << "Good job! You guessed the word!\n";
        if(game.getCurrentTry() <= 2){
            std::cout << "It took you " << game.getCurrentTry() - 1 << " try!!\n"; 
            std::cout << "Wowza! You must be a wizard or something!\n";
        }
        else if(game.getCurrentTry() <= game.getMaxTries()/3){
            std::cout << "It took you " << game.getCurrentTry() - 1 << " tries!!\n"; 
            std::cout << "That is a pretty quick guess, amazing!\n"; 
        }
        else {
            std::cout << "It took you " << game.getCurrentTry() - 1 << " tries!\n";
        }
    }
    else{
        std::cout << "Aw you lost. Better luck next time!\n";
    }
    std::cout << std::endl;
    return;
}