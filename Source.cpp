#include <iostream>
#include <string>
#include "Header.h"
#include <map>
#include<cctype>

#define TMap std::map;

using FText = std::string;
using int32 = int;

void openCrawl();
void startGame();
FText getGuess(int32);
bool playAgain();
FString MyHiddenWord;

fGame Player1;
fGame Player2;
Overseer Meta;

int main() {
	bool replay = false;
	do {
		openCrawl();
		startGame();
		replay = playAgain();
	} while (replay);
	return 0;
}

void openCrawl() {
	// introduction and setup
	std::cout << "This is a quick demo of my C++ skill." << std::endl << "The object of the game is the guess the word" << std::endl << "BUllS are letters that are in the right position." << std::endl << "COWS are letters that exist in the word but are not in the correct position";
	std::cout << std::endl;
	int Difficulty;
 do {
		std::cout << "Select a difficulty (1 to 3):";
		std::cin >> Difficulty;
		while(std::cin.fail()){
			std::cin.clear();   //clear istream
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');  //repair istream
			std::cout << "This is not a number.  Try again. \n";	
			std::cin >> Difficulty;
		}
	}while (Difficulty > 3 && Difficulty != 0);
	MyHiddenWord = Meta.playWord(Difficulty);//Gets the play word
	return;
}

void startGame() {
	Player1.Reset();
	Player2.Reset();	
	do {		
			std::cout << "Player 1 turn \n";
			FText Guess = getGuess(Player1.currentTry());
			BullCowCounter BullCowCount = Player1.Submit(Guess,MyHiddenWord);
			std::cout << "Bulls = " << BullCowCount.bulls << " ___ ";
			std::cout << "Cows = " << BullCowCount.cows << std::endl;
			std::cout << std::endl;
		if (Player1.IsGameWon()) {return;}//Start of player 2 turn
			std::cout << "Player 2 turn \n";
			Guess = getGuess(Player2.currentTry());
			BullCowCount = Player2.Submit(Guess,MyHiddenWord);
			std::cout << "Bulls = " << BullCowCount.bulls << " ___ ";
			std::cout << "Cows = " << BullCowCount.cows << std::endl;
			std::cout << std::endl;
	} while (!Player2.IsGameWon());

	return;
}

bool playAgain() {
	if (Player1.IsGameWon()) {
		std::cout << "Player 1 has guessed the word in " << Player1.currentTry() << " tries. \n";
		Meta.checkScores(Player1.currentTry());
	}
	else {
		std::cout << "Player 2 has guessed the word in " << Player2.currentTry() << " tries. \n";
		Meta.checkScores(Player2.currentTry());
	}
	std::cout << "THANKS FOR PLAYING!!!!!!" << std::endl << "Do you want to play again?";
	FText Answer;
	std::getline(std::cin, Answer);
	if (Answer[0] == 'y' || Answer[0] == 'Y') {
		return true;
	}
	else { return false; }
}

std::string getGuess(int32 TryNum) {
	EwordStatus Status = EwordStatus::Not_Isogram;
	FText Guess;
	do {
		std::cout << "Try No. " << TryNum <<  std::endl;
		std::cout << "Please enter a " << MyHiddenWord.length() << " letter word.\n";
		std::getline(std::cin, Guess);
		Status = Meta.checkGuess(Guess);///TODO take out of class
		switch (Status){
			default:
				return Guess;
			case EwordStatus::Wrong_length:
				std::cout << "That is not the correct amount of letters\n";
				break;
			case EwordStatus::Not_Lowercase:
				std::cout << "The word must be lower case\n";
				break;
			case EwordStatus::Not_Isogram:
				std::cout << "the word must be an Isogram\n";
				break;
			case EwordStatus::OK:
				break;
			}		
	} while (Status != EwordStatus::OK);
	return Guess;
}
		


