#ifndef BLACKJACK_H_
#define BLACKJACK_H_

typedef enum cardSuit{ hearts=1, spades, diamonds, clubs } Suit;
typedef enum cardFace{ two=2, three, four, five, six, seven, 
	eight, nine, ten, jack, queen, king, ace } Rank;
typedef struct cards{
	Rank rank;
	Suit suit;
} Card;

Card deck[52];
Card* playerHand[12] = { 0 };
Card* dealerHand[12] = { 0 };
int currentTopCard = 0;
int playerTotal = 0, dealerTotal = 0, dealerShown = 0;

#endif
