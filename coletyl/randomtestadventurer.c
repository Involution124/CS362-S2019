/*
 *
 ** cardtest4.c
 **   
*/

/*
 * Testing the smithy card effect switch block
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "assertT.h"
#include <time.h>
#define TESTCARD "Adventurer"

int main() {
	srand(time(NULL));
	int newCards = 0;
	int discarded = 1;
	int xtraCoins = 0;
	int shuffledCards = 0;
	int gainedCards, deckCards;
	int i, j, m;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int remove1, remove2;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	// initialize a game &testG and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	gainCard(13, &G, 1, 0);	
	
	
	// ----------- TEST 1: Test the adventurer function --------------
	for(int i=0; i<20000; i++){
		memcpy(&testG, &G, sizeof(struct gameState));
		printf("TEST %i: \n", i);
		int iterations1 = rand()%10 + 10;
		int iterations2 = rand()%10;
		if(rand()%2 == 0){
			endTurn(&testG);
		}
		int currentPlayer = whoseTurn(&testG);	
		for(int j=0; j<iterations1; j++){
			int card = rand() % 27;
			gainCard(card, &testG, 1, currentPlayer);
		}
		for(int j=0; j<iterations2; j++){
			drawCard(currentPlayer, &testG);
		}
		int prevNumTreasures = 0;
		for(int i=0; i<testG.deckCount[currentPlayer]; i++){
			if(testG.deck[currentPlayer][i] >= copper && testG.deck[currentPlayer][i] <= gold){
				prevNumTreasures++;
			}
		}
		Adventurer(currentPlayer, &testG, 0);
		int numTreasures = 0;
		for(int i=0; i<testG.deckCount[currentPlayer]; i++){
			if(testG.deck[currentPlayer][i] >= copper && testG.deck[currentPlayer][i] <= gold){
				numTreasures++;
			}
		}
		printf("Player gained %i treasures\n", numTreasures - prevNumTreasures); 
		printf("%i\n", numTreasures);
		assertT(numTreasures - prevNumTreasures == -2 || numTreasures == 0);
		// Assert they either gained 2 treasures, or ran out of treasures in deck	
	}	
}
