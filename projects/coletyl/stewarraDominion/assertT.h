#include <stdio.h>
#include <stdlib.h>


int assertT(int v){
	if(v){
		printf("TEST SUCCESSFULl!\n");
	} else {
		printf("------------------------------------\n");
		printf("------------- ERROR ----------------\n");
		printf("------------- ERROR ----------------\n");
		printf("------------------------------------\n");
		printf("A test was unsuccessful\n");
	}
}
