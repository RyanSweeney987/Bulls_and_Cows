#include <map>
#include <iostream>
#include "FBullCowGame.h"
#include "TIsogramMap.h"

#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FBullCowGame::GetGuessHint() const { return MyGuessResultHint; }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

int32 FBullCowGame::GetMaxTries() const {
	// Max tries is based upon the hidden word length in a key-value map
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,6},{5,8},{6,10},{7,12} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bIsGameWon = false;

	// Default word is provided initially unless chosen by the player
	constexpr int32 DEFAULT_HIDDEN_WORD_LENGTH = 6;
	SetHiddenWordLength(DEFAULT_HIDDEN_WORD_LENGTH);

	InitGuessResult(DEFAULT_HIDDEN_WORD_LENGTH);
}

std::string FBullCowGame::GetGuess()
{
	return std::string();
}

EWordValidity FBullCowGame::CheckGuess(FString Guess) const
{
	// Check the vality of the guess using private some helper methods
	if (!IsIsogram(Guess)) {
		return EWordValidity::NOT_ISOGRAM;
	}
	else if (!IsLowerCase(Guess)) {
		return EWordValidity::NOT_LOWERCASE;
	} 
	else if (Guess.length() != GetHiddenWordLength()) {
		return EWordValidity::WRONG_LENGTH;
	}
	else {
		return EWordValidity::OK;
	}
}

void FBullCowGame::SetHiddenWordLength(int32 WordLength)
{
	// Map wrapper class containing isograms
	TIsogramMap HiddenWordsMap;

	// Gets random X letter isogram
	MyHiddenWord = HiddenWordsMap.GetRandomIsogram(WordLength);

	InitGuessResult(WordLength);
}

// Recieves a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	ResetGuessResult();

	FBullCowCount BullCowCount;

	int32 WordLength = GetHiddenWordLength();

	// Loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++) {
		// For each letter compare letters against the guess
		for (int32 j = 0; j < WordLength; j++) {
			// If the match
			if (Guess[i] == MyHiddenWord[j]) {
				//std::cout << "Match!" << std::endl;
				if (i == j) {
					// Increment bulls if they're in the same place
					BullCowCount.Bulls++;
					MyGuessResultHint[i] = '0';
 				}
				else {
					// Increment cows if not
					BullCowCount.Cows++;
					MyGuessResultHint[i] = 'O';
				}
			}
			else {
				//std::cout << "No match!" << std::endl;
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) {
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
		// Increment only when we know that the player hasn't won yet
		MyCurrentTry++;
	}	

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) {
		return true;
	}

	TMap<const char, bool> LettersSeen;

	// Loop through using an "enhanced" for loop (forgot what it's called in C++)
	// and see if there's a duplicate
	for (auto Elem : Word) {
		Elem = tolower(Elem);

		if (LettersSeen[Elem]) {
			return false;
		}
		else {
			LettersSeen[Elem] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	if (Word.length() == 0) {
		return true;
	}

	for (auto Letter : Word) {
		// isalpha checks to see if letter is an alphabet character, if it is check to see if it is lower
		// if both are true, logical AND returns true and the end result is true
		if (isalpha(Letter) && islower(Letter)) {
			return true;
		}
		else {
			return false;
		}
	}

	return true;
}

void FBullCowGame::ResetGuessResult()
{
	InitGuessResult(GetHiddenWordLength());
}

void FBullCowGame::InitGuessResult(int32 WordLength)
{
	MyGuessResultHint = "";
	for (int32 i = 0; i < WordLength; i++) {
		MyGuessResultHint += "#";
	}
}
