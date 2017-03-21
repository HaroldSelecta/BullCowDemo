#include <iostream>
#include <string>
#include "Header.h" 
#include <map>
#include <fstream>
#include<iostream>
#include<array>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include <iomanip>
#include <locale>
#include <sstream>
#define TMap std::map
using int32 = int;

fGame::fGame()
{
	Reset();
}

void fGame::Reset()
{
	bGameIsWon = false;
	MyCurrentTry = 1;
	return;
}

int32 fGame::currentTry()const{return MyCurrentTry;}

bool fGame::IsGameWon()const
{return bGameIsWon;}

BullCowCounter fGame::Submit(FString Guess, FString MyHiddenWord)
{
	BullCowCounter BullCowCount;
	int32 WordLength = MyHiddenWord.length();		
		for (int32 i = 0; i < WordLength; i++) {
			for (int32 j = 0; j < WordLength; j++) {				
				if (MyHiddenWord[i] == Guess[j]) {	
					if (i == j) {
						//std::cout << MyHiddenWord[i];
						BullCowCount.bulls++;			
					}
					else{
						BullCowCount.cows++;
					}
				}
				
			}/*std::cout << "_";*/
		}std::cout << "\n";
			if (BullCowCount.bulls == WordLength) {
				bGameIsWon = true;
			}
		else {
			bGameIsWon = false;
			MyCurrentTry++;
		}
		return BullCowCount;
}

FString Overseer::playWord(int32 Difficulty){
	std::map<int32, FString> theWord;
	int nosePicker;
	do {
		nosePicker = rand() % 6 + 1;
		switch (Difficulty) {
		case 1:
			theWord = { { 1, "live" },{ 2, "file" },{ 3, "fair" },{ 4, "head" },{ 5, "exit" },{ 6, "blue" } };
			break;
		case 2:
			theWord = { { 1, "build" },{ 2, "bread" },{ 3, "light" },{ 4, "might" },{ 5, "plane" },{ 6, "groan" } };
			break;
		case 3:
			theWord = { { 1, "source" },{ 2, "sureal" },{ 3, "project" },{ 4, "global" },{ 5, "window" },{ 6, "search" } };
			break;
		}
	} while (MyHiddenWord == theWord[nosePicker]);
	MyHiddenWord = theWord[nosePicker];

	return FString(MyHiddenWord);
}

EwordStatus Overseer::checkGuess(FString Guess)
{
	if (!IsIsogram(Guess)) {
	return EwordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {
		return EwordStatus::Not_Lowercase;
	}
	else if (Guess.length() != MyHiddenWord.length()) {
		return EwordStatus::Wrong_length;
	}
	else {
		return EwordStatus::OK;
	}
}

bool Overseer::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }
	TMap<char, bool> letterSeen;
	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		if (letterSeen[Letter]) {
			return false;
		}
		else {
			letterSeen[Letter] = true;

		}
	}
	return true;
}

bool Overseer::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
		else { return true; }
	}
	return false;
}

void Overseer::checkScores(int myScore)
{
	std::string line;//temp for passing values
	std::vector<std::string> totalscores;
	std::vector<std::string>totalnames;
	std::fstream myfile;
	myfile.open("scoretable.txt");
	if (myfile.is_open()) {
		while (std::getline(myfile, line)) {
			std::istringstream iss(line);
			FString name, score;
			if (!(iss >> name >> score)) { break; }
			totalscores.push_back(score);
			totalnames.push_back(name);

		}
		myfile.close();
	}
	else { std::cout << "unable to openfile \n"; }
	for (int32 x = 0; x < totalscores.size(); x++) {
		int32 scoreHolder;//temp for post converted score
		std::string currentScore = totalscores[x];
		std::istringstream convert(currentScore);//converting Str to int
			if (!(convert >> scoreHolder)) {
				scoreHolder = 0;
			}
		if (myScore < scoreHolder) {
			std::cout << "I am ranked " << x+1  << std::endl;
			std::cout << "What are your initials? (Must be three characters)\n";
			std::string Initials;
				do {
					std:getline(std::cin, Initials);
				} while (Initials.length() != 3);
			auto it = totalnames.begin();
			totalnames.insert(it + x, Initials);//adding initials
			it = totalscores.begin();//changes from name to score
			std::string nameHolder;//temp holder for names
			std::ostringstream convert;
				convert << myScore;
					nameHolder = convert.str();
						totalscores.insert(it + x, nameHolder);//TODO find better name than nameHolders
			break;
		}
		else {}//pointless

	}
	totalnames.pop_back();
	totalscores.pop_back();
	myfile.open("scoretable.txt");
	std::cout << "HERE ARE THE HIGH SCORES \n";
		if (myfile.is_open()) {
			for (int x = 0; x <= totalnames.size()-1; x++) {
				myfile << totalnames[x] << " " << totalscores[x] << '\n';
				std::cout << x+1 << " | " << totalnames[x]<<  " | " << totalscores[x] << '\n';
			}
			myfile.close();
		}else { std::cout << "unable to openfile \n"; }
	return;
}



