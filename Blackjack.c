#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "Blackjack.h"

#define MAX 3

void OpenGame();
void DealerShowing();
void PlayerTurn();
void DealerTurn();
void MakeDeck();
void PrintDeck();
void ShuffleDeck();
void DealOpeningHands();
void Hit(Card* array[]);
Card* GetTopCard();
void PrintHand(Card* array[]);
void UpdateTotal(Card* array[], bool isPlayer);

int main(){
	int usrOption = -1;
	char usrInput[MAX];
	char *ptr;
	srand(time(0));


	OpenGame();
	do{
		printf("Enter 1 to hit, 2 to stand, 0 to exit.\n");
		fgets(usrInput, MAX, stdin);
		usrOption = strtol(usrInput, &ptr, 10);

		if (usrOption==1){
			PlayerTurn();
		} else if (usrOption==2){
			DealerTurn();
			if (dealerTotal < playerTotal || dealerTotal > 21){
				printf("Player wins!\n");
				break;
			}
			if (dealerTotal > playerTotal){
				printf("Dealer wins!\n");
				break;
			}
			printf("Draw!\n");
			exit(0);
		} else if (usrOption==0){
			exit(0);
		} else {
			printf("Invalid input...\n");
		}
		memset(usrInput, '\0', sizeof(usrInput));

	} while (usrOption!=-1);
	return 0;
}

void OpenGame(){
	printf("Welcome to blackjack\n");
	MakeDeck();
	ShuffleDeck();
	DealOpeningHands();
	DealerShowing();
	printf("Player hand:\n");
	PrintHand(playerHand);
	UpdateTotal(playerHand, true);
	printf("Total: %d\n", playerTotal);
}

void DealerShowing(){
	printf("The dealer is showing a... ");
	char showingStr[3];
	if (dealerHand[0]->rank==14){
		sprintf(showingStr, "%c\n", 'A');
	} else {
		sprintf(showingStr, "%d\n", dealerHand[0]->rank);
	}
	printf("%s", showingStr);
}


void PlayerTurn(){
	Hit(playerHand);
	PrintHand(playerHand);
	UpdateTotal(playerHand, true);
	printf("Total: %d\n", playerTotal);
	if (playerTotal > 21){
		printf("Player busts!\n Thanks for playing.\n");
		exit(0);
	}
}

void DealerTurn(){
	printf("Dealer plays...\n");
	UpdateTotal(dealerHand, false);
	while(true){
		if (dealerTotal == 21){
			break;
		}
		if (dealerTotal>16 && dealerTotal < 22){
			break;
		}
		if (dealerTotal>21){
			break;
		}
		Hit(dealerHand);
		UpdateTotal(dealerHand, false);
		PrintHand(dealerHand);
	}
	printf("Dealer total: %d", dealerTotal);
}


void MakeDeck(){
	int i = 0;
	for (int j = hearts; j<clubs+1; j++){
		for (int k = two; k<ace+1; k++){
			Card card = {  k, j };
			deck[i] = card;
			i++;
		}
	}
}
				
void ShuffleDeck(){
	int firstPick, secondPick, i=0;
	while (i<200){
		firstPick = rand()%52;
		Card buf1 = deck[firstPick];
		secondPick = rand()%52;
		deck[firstPick] = deck[secondPick];
		deck[secondPick] = buf1;
		i++;
	}
}

void PrintDeck(){
	for (int i=0;i<52; i++){
		printf("%d %d\n",deck[i].rank, deck[i].suit);
	}
}

void DealOpeningHands(){
	playerHand[0] = GetTopCard();
	playerHand[1] = GetTopCard();
	dealerHand[0] = GetTopCard();
	dealerHand[1] = GetTopCard();
}
	
void Hit(Card* array[]){
	for (int i=0; i<12; i++){
		if (array[i]==0){
			array[i]=GetTopCard();
			break;
		}
	}
}

void UpdateTotal(Card* array[], bool isPlayer){
	int sum = 0;
	bool acePresent = false;
	for (int i=0;i<12;i++){
		if (array[i]!=0){
			if (array[i]->rank==14){
				sum += 1;
				acePresent=true;
			} else if(array[i]->rank>=10 && array[i]->rank<14){
				sum += 10;
			} else {
				sum += array[i]->rank;
			}
		}
	}
	if (sum<12 && acePresent){
		sum+=10;
	}
	if (isPlayer){
		playerTotal=sum;
	} else {
		dealerTotal=sum;
	}
}


Card* GetTopCard(){
	int offTheTop = currentTopCard;
	currentTopCard++;
	return &deck[offTheTop];
}

void PrintHand(Card* array[]){
	char suitChar;
	char rankStr[3];
	for (int i=0;i<12;i++){
		if (array[i]!=0){
			switch(array[i]->suit){
				case 1: 
					suitChar = 'h';
					break;
				case 2:
					suitChar = 's';
					break;
				case 3:
					suitChar = 'd';
					break;
				case 4:
					suitChar = 'c';
					break;
				default:
					suitChar = '?';
					break;
			}
			switch(array[i]->rank){
				case 10:
					sprintf(rankStr, "10");
					break;
				case 11:
					sprintf(rankStr, "J");
					break;
				case 12:
					sprintf(rankStr, "Q");
					break;
				case 13:
					sprintf(rankStr, "K");
					break;
				case 14:
					sprintf(rankStr, "A");
					break;
				default:
					sprintf(rankStr, "%d", array[i]->rank);
					break;
			}
			printf("%c%s ", suitChar, rankStr);
		}
	}

}
