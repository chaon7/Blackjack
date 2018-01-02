#include "stdafx.h"
#include <iostream>
#include <string>
#include <array>
#include <utility>
#include <cstdlib>
#include <ctime>

enum CardSuit
{
	SUIT_CLUB,
	SUIT_DIAMOND,
	SUIT_HEART,
	SUIT_SPADE,
	MAX_SUITS
};

enum CardRank
{
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	RANK_ACE,
	MAX_RANKS
};

struct Card
{
	CardRank rank;
	CardSuit suit;
};

void printCard(const Card &card)
{
	switch (card.rank)
	{
	case RANK_2:		std::cout << '2'; break;
	case RANK_3:		std::cout << '3'; break;
	case RANK_4:		std::cout << '4'; break;
	case RANK_5:		std::cout << '5'; break;
	case RANK_6:		std::cout << '6'; break;
	case RANK_7:		std::cout << '7'; break;
	case RANK_8:		std::cout << '8'; break;
	case RANK_9:		std::cout << '9'; break;
	case RANK_10:		std::cout << 'T'; break;
	case RANK_JACK:		std::cout << 'J'; break;
	case RANK_QUEEN:	std::cout << 'Q'; break;
	case RANK_KING:		std::cout << 'K'; break;
	case RANK_ACE:		std::cout << 'A'; break;
	}

	switch (card.suit)
	{
	case SUIT_CLUB:		std::cout << 'C'; break;
	case SUIT_DIAMOND:	std::cout << 'D'; break;
	case SUIT_HEART:	std::cout << 'H'; break;
	case SUIT_SPADE:	std::cout << 'S'; break;
	}
}

void printDeck(const std::array<Card, 52> &deck)
{
	for (const auto &card : deck)
	{
		printCard(card);
		std::cout << ' ';
	}

	std::cout << '\n';
}

void swapCard(Card &a, Card &b) {
	Card temp = a;
	a = b;
	b = temp;
}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void shuffleDeck(std::array<Card, 52> &deck) {

	srand(static_cast<unsigned int>(time(0)));
	rand();

	for (int card = 0; card < 52; card++) {
		int card2 = getRandomNumber(0, 51);
		swapCard(deck[card], deck[card2]);
	}

}

int getCardValue(const Card &card) {
	switch (card.rank)
	{
	case RANK_2:		return 2;
	case RANK_3:		return 3;
	case RANK_4:		return 4;
	case RANK_5:		return 5;
	case RANK_6:		return 6;
	case RANK_7:		return 7;
	case RANK_8:		return 8;
	case RANK_9:		return 9;
	case RANK_10:		return 10;
	case RANK_JACK:		return 10;
	case RANK_QUEEN:	return 10;
	case RANK_KING:		return 10;
	case RANK_ACE:		return 11;
	}

	return 0;
}

bool playBlackjack(std::array<Card, 52> &deck) {
	int dealerScore = 0;
	int playerScore = 0;
	int card = 0;
	shuffleDeck(deck);

	dealerScore += getCardValue(deck[card++]);
	std::cout << "The dealer has " << dealerScore << " points." << std::endl;
	playerScore += getCardValue(deck[card++]);
	playerScore += getCardValue(deck[card++]);
	std::cout << "You have " << playerScore << " points." << std::endl;

	bool stand = false;
	char answer;
	do {
		std::cout << "Do you want to hit or stand (h/s)?";
		std::cin >> answer;

		if (answer == 'h') {
			playerScore += getCardValue(deck[card++]);
			std::cout << "You have " << playerScore << " points." << std::endl;
		}
		else if (answer == 's')
			stand = true;
		else
			std::cout << "Wrong input";

	} while ((playerScore <= 21) && (!stand));

	if (playerScore > 21) {
		std::cout << "Player busts!" << std::endl;
		return false;
	}

	do {
		dealerScore += getCardValue(deck[card++]);
		std::cout << "The dealer has " << dealerScore << " points." << std::endl;
	} while (dealerScore < 17);

	if (dealerScore > 21) {
		std::cout << "Dealer busts!" << std::endl;
		return true;
	}

	if (playerScore > dealerScore) {
		std::cout << "You got a higher score!" << std::endl;
		return true;
	}
	else {
		std::cout << "You got a lower score!" << std::endl;
		return false;
	}

}

int main()
{
	std::array<Card, 52> deck;

	int card = 0;
	for (int suit = 0; suit < MAX_SUITS; ++suit)
		for (int rank = 0; rank < MAX_RANKS; ++rank)
		{
			deck[card].suit = static_cast<CardSuit>(suit);
			deck[card].rank = static_cast<CardRank>(rank);
			++card;
		}

	if (playBlackjack(deck))
		std::cout << "You Won!" << std::endl;
	else
		std::cout << "You lost" << std::endl;
	return 0;
}
