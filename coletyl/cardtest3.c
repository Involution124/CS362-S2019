/*
 ** cardtest4.c
 **   
*/

/*
 * Testing the Mine cardEffect switch block
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include "assertT.h"
#define TESTCARD "Mine"

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


	gainCard(copper, &G, 2, 0);
	gainCard(silver, &G, 2, 0);
		printf("TEST 1: \n");

	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = whoseTurn(&testG);	

	int prevNumSilver = 0;
	for(int i=0; i<testG.handCount[currentPlayer]; i++){
		if(testG.hand[currentPlayer][i] == silver){
			prevNumSilver++;
		}
	}
	choice1 = 0;
	choice2 = silver;
	cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
	int numSilver = 0;
	for(int i=0; i<testG.handCount[currentPlayer]; i++){
		if(testG.hand[currentPlayer][i] == silver){
			numSilver++;
		}
	}
	printf("Player gained %i silver from a copper\n", numSilver - prevNumSilver); 
	assertT(numSilver - prevNumSilver == 1);	


	printf("TEST 2: \n");

	memcpy(&testG, &G, sizeof(struct gameState));
	currentPlayer = whoseTurn(&testG);	

	int prevNumGolds = 0;
	for(int i=0; i<testG.handCount[currentPlayer]; i++){
		if(testG.hand[currentPlayer][i] == gold){
			prevNumGolds++;
		}
	}
	choice1 = 6;
	choice2 = gold;
	cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
	int numGolds = 0;
	for(int i=0; i<testG.handCount[currentPlayer]; i++){
		if(testG.hand[currentPlayer][i] == gold){
			numGolds++;
		}
	}
	printf("Player gained %i gold from a silver\n", numGolds - prevNumGolds); 
	assertT(numGolds - prevNumGolds  == 1);	


}
