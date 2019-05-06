/*
 ** cardtest4.c
 **   
*/

/*
 * Testing the Adventurer cardEffect switch block
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include "assertT.h"

#define TESTCARD "Adventurer"

int main() {
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
	srand(time(NULL));

	// initialize a game &testG and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


	for(int i=0; i<50; i++){
		gainCard(rand()%27, &G, 1, 0);
		gainCard(rand()%27, &G, 1, 1);
		gainCard(rand()%27, &G, 1, 2);
	}
	// ----------- TEST 1: Test the adventurer function --------------
	printf("TEST 1: \n");

	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = whoseTurn(&testG);	

	int prevNumTreasures = 0;
	for(int i=0; i<testG.deckCount[currentPlayer]; i++){
		if(testG.deck[currentPlayer][i] >= copper && testG.deck[currentPlayer][i] <= gold){
			prevNumTreasures++;
		}
	}
	printf("Current place = %i\n", prevNumTreasures);
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	int numTreasures = 0;
	for(int i=0; i<testG.deckCount[currentPlayer]; i++){
		if(testG.deck[currentPlayer][i] >= copper && testG.deck[currentPlayer][i] <= gold){
			numTreasures++;
		}
	}
	printf("Player gained %i treasures\n", numTreasures - prevNumTreasures); 
	assertT(numTreasures - prevNumTreasures == -2);	

}
