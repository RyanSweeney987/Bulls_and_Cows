/*
	This is the console executable that makes use of FBullCow class.
	This acts as the view in a MVC pattern and is responsible for all user interactions.
	For game logic see the FBullCowGame class.
*/
#pragma once

#include <sstream>
#include <iostream>
#include <string>
#include "FBullCowGame.h"
// <> when importing standard libraries
// "" when importing my own files

// To make syntax similar to Unreal Engine
using FText = std::string;
using int32 = int;

// Note to self, function prototypes outside of class since we're not using one
void PrintStart();
void PrintHowToPlay();
void PrintStartingHint();
void PrintEnd();
void PlayGame();
FText GetGuess();
bool CheckGuess(FText Guess, FText Word);
bool AskToPlayAgain();
void AskWordLength();

void PrintGameSummary();

FBullCowGame BCGame;

int main() {
	PrintStart();
	PrintHowToPlay();

	do {
		BCGame.Reset();
		AskWordLength();
		PrintStartingHint();
		PlayGame();
	} while (AskToPlayAgain());
	
	return 0;
}

void PrintStart() {
	std::cout << "\t\t\t+-----------------------------------------------------+" << std::endl;
	std::cout << "\t\t\t|                                                     |" << std::endl;
	std::cout << "\t\t\t|      Welcome to Bulls and Cows, a fun word game.    |" << std::endl;
	std::cout << "\t\t\t|                                                     |" << std::endl;
	std::cout << "\t\t\t+-----------------------------------------------------+" << std::endl;
}

void PrintHowToPlay() {
	std::cout << "\n" << std::endl;
	std::cout << "\t\t\t\t\t    How to play:" << std::endl;
	std::cout << "\t- " << "The goal is to correctly guess the word with all letters in the correct place." << std::endl;
	std::cout << "\t- " << "The words are isograms, meaning that they don't contain two or more of any given letter." << std::endl;
	std::cout << "\t- " << "Bulls (0) represent a letter that is in the word and in the correct place." << std::endl;
	std::cout << "\t- " << "Cows (O) represent a letter that is in the word but is in the wrong place." << std::endl;
	std::cout << "\t- " << "A letter that isn't in the word is represented by a hash symbol (#)" << std::endl;
	//std::cout << "\t- " << "" << std::endl;
	std::cout << std::endl;
}

void PrintStartingHint() {
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl << std::endl;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations, you won!" << std::endl;

		std::cout << "And you did it in " << BCGame.GetCurrentTry() << " out of " << BCGame.GetMaxTries() << " tries, nice!" << std::endl;
	}
	else {
		std::cout << "Unlucky, better luck next time." << std::endl;
	}
}

void PlayGame() {
	// Maximum number attempts available
	int32 MaxTries = BCGame.GetMaxTries(); 
	
	// Loop asking for guesses while the game is not won and there are still tries remaining
	while (BCGame.GetCurrentTry() <= MaxTries && !BCGame.IsGameWon()) {
		// Acquire the players guess and check validity
		FText Guess = GetGuess();

		// If guess is valid submit to find if it's correct, if not, how many bulls and cows there are
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		// Print result
		std::cout << "(Bull: 0 Cow: O Wrong: #)\t" << BCGame.GetGuessHint() << std::endl;
		std::cout << "Bulls = " << BullCowCount.Bulls << ", Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}

	PrintGameSummary();
}

FText GetGuess() {
	EWordValidity Status = EWordValidity::INVALID;
	FText Guess = "";
	bool AskAgain = true;

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 MaxTries = BCGame.GetMaxTries();
		// Get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << MaxTries << ". Enter your guess: \t";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuess(Guess);

		switch (Status) {
		case EWordValidity::NOT_ISOGRAM:
			std::cout << "Please enter a word without repeating letters!" << std::endl << std::endl;
			break;
		case EWordValidity::NOT_LOWERCASE:
			std::cout << "Please only use lower case letters!" << std::endl << std::endl;
			break;
		case EWordValidity::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl << std::endl;
			break;
		case EWordValidity::OK:
			AskAgain = false;
			break;
		default:
			// Redundant but just in case anything comes throught that wasn't either caught or meant to
			std::cout << "Unknown bug! Arrgh!!!" << std::endl << std::endl;
			break;
		}
	} while (AskAgain);

	return Guess;
}

void AskWordLength() {
	bool HasSelectedValidOption = false;

	while (!HasSelectedValidOption) {
		std::cout << "Do you want to choose the word length? (y/n) ";

		FText Result = "";
		std::getline(std::cin, Result);

		// If Result is equal to y, get the number and set the hidden word length which defines difficulty of game
		if (Result[0] == 'Y' || Result[0] == 'y') {
			std::cout << "Please select a number value from 3 to 7. ";

			FString Number = "";
			std::getline(std::cin, Number);

			// TODO learn what this actually does
			// Not too sure what this does... But it seems to get certain parts out of an FString
			std::istringstream IStringStream(Number);

			int Value = 0;

			// Apparently applies the first int found in the FString Number to Value
			IStringStream >> Value;

			// In case user doesn't enter a number, give error and ask again
			if (Value < 3 || Value > 7) {
				std::cout << "Please enter a value between 3 and 7!" << std::endl << std::endl;
			}
			else {
				std::cout << "The word length you chose is " << Value << "." << std::endl;

				BCGame.SetHiddenWordLength(Value);

				HasSelectedValidOption = true;
			}
		}
		else if (Result[0] == 'N' || Result[0] == 'n') {
			HasSelectedValidOption = true;
		}
		else {
			// Just in case user enters something invalid
			std::cout << "Please enter a valid value! Otherwise, type \'n\' to use the default length." << std::endl << std::endl;
		}
	}
	std::cout << std::endl;
}

bool AskToPlayAgain() {
	bool HasSelectedValidOption = false;
	bool QueryResult = false;

	while (!HasSelectedValidOption) {
		std::cout << std::endl << "Do you want to play again? (y/n) ";
		FText Result = "";
		std::getline(std::cin, Result);

		if (Result[0] == 'Y' || Result[0] == 'y') {
			QueryResult = true;
			HasSelectedValidOption = true;
		}
		else if (Result[0] == 'N' || Result[0] == 'n') {
			QueryResult = false;
			HasSelectedValidOption = true;
		}
		else {
			// Just in case the user enters something invalid
			std::cout << "Please enter a valid value! Otherwise, type \'n\' or hit the [X] in the top righ hand corner to exit." << std::endl;
		}
	}

	return QueryResult;
}