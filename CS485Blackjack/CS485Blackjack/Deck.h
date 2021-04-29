#pragma once
#include "Card.h"
#include <vector>


class Deck {
private:
	int mNumOfSets;
	std::vector<Card> mCards;

public:
	Deck(); 
	Deck(int);
	void shuffleDeck();
	void stackDeck();
	Card drawCard();
	void changeNumOfSets(int);

};