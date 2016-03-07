#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordValidity {
	OK, 
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE,
	INVALID
};

class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetGuessHint() const;
	bool IsGameWon() const;	
	
	EWordValidity CheckGuess(FString String) const;

	void SetHiddenWordLength(int32);

	void Reset(); 

	FString GetGuess();

	// Counts bulls and cows, increase try number assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	FString MyGuessResultHint;
	bool bIsGameWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;

	void ResetGuessResult();
	void InitGuessResult(int32);
};