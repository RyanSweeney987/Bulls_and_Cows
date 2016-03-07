#pragma once
#include <string>
#include <map>
#include <vector>

// Macro preprosessor directive
//#define TMap std::map
// Type alias (same as typedef)
using FString = std::string;
using int32 = int;
using TMap = std::map<int32, std::vector<FString>>;

class TIsogramMap {
public:
	TIsogramMap();

	TMap GetMyMap();
	FString GetRandomIsogram(int32);

private:
	TMap MyMap;
};