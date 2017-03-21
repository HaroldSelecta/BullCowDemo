#pragma once
#include<string>

using FString = std::string;
using int32 = int;

struct BullCowCounter {
	int32 bulls = 0;
	int32 cows = 0;
};

enum EwordStatus {
	OK,
	Not_Isogram,
	Wrong_length,
	Not_Lowercase

};

class fGame {
public:
	fGame();
	void Reset();
	int32  currentTry() const;
	bool IsGameWon() const;
	BullCowCounter Submit(FString, FString);
	

private:
	int32 MyCurrentTry;
	bool bGameIsWon;
	
};

class Overseer {
public:
	FString playWord(int32);
	EwordStatus checkGuess(FString);
	void checkScores(int);

private:
	FString MyHiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString)const;


};
