/*
 ** cardtest4.c
 **   
*/

/*
 ** Include the following lines in your makefile:
 **
 ** cardtest4: cardtest4.c dominion.o rngs.o
 **      gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "assertT.h"
#define TESTCARD "Smithy"

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

	// initialize a game &testG and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


	gainCard(13, &G, 1, 0);
	gainCard(13, &G, 1, 1);
	// ----------- TEST 1: Test the smithy function --------------
	printf("TEST 1: \n");

	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = whoseTurn(&testG);	


	int prevHand = testG.handCount[currentPlayer];
	int prevDeck = testG.deckCount[currentPlayer];
	Smithy(currentPlayer, &testG, 0);
	gainedCards = testG.handCount[currentPlayer] - prevHand;
	deckCards = testG.deckCount[currentPlayer] - prevDeck;
	printf("Player gained %i cards\n", gainedCards); 
	printf("Deck gained %i cards\n", deckCards);
	assertT(gainedCards == 2);
	assertT(deckCards == -3);	


	// ----------- Test 2: Test other player ---------------
	currentPlayer = whoseTurn(&testG);
		
	prevHand = testG.handCount[currentPlayer];
	prevDeck = testG.deckCount[currentPlayer];
	Smithy(currentPlayer, &testG, handpos);
	gainedCards = testG.handCount[currentPlayer] - prevHand;
	deckCards = testG.deckCount[currentPlayer] - prevDeck;
	printf("Player gained %i cards\n", gainedCards); 
	printf("Deck gained %i cards\n", deckCards);
	assertT(gainedCards == 2);
	assertT(deckCards == -3);	


}
