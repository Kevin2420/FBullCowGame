#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map 
// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;


FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const
{
	TMap < int32, int32> WordLengthToMaxTries{ {3, 4}, {4,6}, { 5, 8 },{ 6, 10 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase  
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong
	{
		return EGuessStatus::Incorrect_Word_Length;
	}
	else// otherwise
	{
		return EGuessStatus::OK;
	}
	
}
// receives a VALID guess, increments turns
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	//loop through all letters in the hideen word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		// compare letters againts the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			// IF THEY MATCH THEN
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar == GChar) { // increment bulls if they ARE IN the same place
					BullCowCount.Bulls++; // increment bulls
							}
			else {
					BullCowCount.Cows++; //increment cows if they ARE NOT in the same plac
				 }
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;  // setup our map
	for (auto Letter : Word)	// for all letters of the word
	{	
		Letter = tolower(Letter);// handle mixed case
		if (LetterSeen[Letter]) { // if the letter is in the map
			return false;		  // we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}			
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
