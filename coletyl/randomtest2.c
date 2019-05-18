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
#define TESTCARD "Mine"

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
	gainCard(16, &G, 1, 0);	
	
	
	// ----------- TEST 1: Test the Mine function --------------
	for(int i=0; i<80000; i++){
		memcpy(&testG, &G, sizeof(struct gameState));
		printf("TEST %i: \n", i);
		int iterations1 = rand()%30 + 30;
		int iterations2 = rand()%20;
		if(rand()%2 == 0){
			endTurn(&testG);
		}
		int currentPlayer = whoseTurn(&testG);	
		for(int j=0; j<iterations1; j++){
			int card = rand() % 27;
			gainCard(card, &testG, 2, currentPlayer);
		}
		for(int j=0; j<iterations2; j++){
			drawCard(currentPlayer, &testG);
		}
		choice1 = rand() % 27;
		choice2 = rand() % 29 - 1;
		gainCard(choice1, &testG, 1, currentPlayer);
		int prevNum = 0;
		for(int i=0; i<testG.handCount[currentPlayer]; i++){
			if(testG.hand[currentPlayer][i] == choice2){
				prevNum++;
			}
		}
		printf("Current place = %i\n", prevNum);
		int ret = Mine(currentPlayer, &testG, 4, choice1, choice2);
		int num = 0;
		for(int i=0; i<testG.handCount[currentPlayer]; i++){
			if(testG.hand[currentPlayer][i] == choice2){
				num++;
			}
		}
		printf("Player gained %i %i from a %i\n", num - prevNum, choice1, choice2); 
		if ((&testG)->hand[currentPlayer][choice1] < copper || (&testG)->hand[currentPlayer][choice1] > gold || choice2 > treasure_map || choice2 < curse || (getCost((&testG)->hand[currentPlayer][choice1]) + 3) > getCost(choice2)){
			assertT(ret == -1);
		} else {
			assertT(num - prevNum == 1);	
		}
	} 
}

