#include "TIsogramMap.h"
#include <iostream>

TIsogramMap::TIsogramMap()
{
	std::vector<FString> ThreeLetterWords = {"bot"};
	std::vector<FString> FourLetterWords = { "roam" };
	std::vector<FString> FiveLetterWords = { "jumpy" };
	std::vector<FString> SixLetterWords = { "planet" };
	std::vector<FString> SevenLetterWords = { "stumped" };

	MyMap = { { 3, ThreeLetterWords },{ 4, FourLetterWords },{ 5, FiveLetterWords },{ 6, SixLetterWords },{ 7, SevenLetterWords } };
}

TMap TIsogramMap::GetMyMap()
{
	return MyMap;
}

FString TIsogramMap::GetRandomIsogram(int32 Position)
{
	std::vector<FString> ListOfWords = MyMap[Position];
	int32 SizeOfArray = ListOfWords.size();
	// Ternary operator, if SizeOfArray is greater than one, set RandomPosition to the random value, otherwise set it to 1
	int32 RandomPosition = ((SizeOfArray > 1) ? rand() % ListOfWords.size() : 0);
	return ListOfWords[RandomPosition];
}
