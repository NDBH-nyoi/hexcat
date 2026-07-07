#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char LookFor_str[] = "80,64,ff,24"; 
char ConversionBuf[32][3]; // set 32 as the number of hex characters you can put into conversionBuf, equaling 2 lines of hex
unsigned char ConverBufCounter = 0;
unsigned char CharMatch = 0;
int MatchCounter = 0;


// We need to 1st split up example str and do conversion into int( or of course unsigned char)
// then while iterating over example_arr with i after conversion into int, we do the following:
// k = 0, if match_arr[k] == example_arr[i] -> k++, and if k = length -> return match and put k=0
// else k = 0

//80 = 80 , 64 != 80, 

char Example_arr[][3] = {"20", "16", "34", "80", "80", "80", "64", "ff", "24", "10","80", "64", "ff", "24"};
unsigned char Example_arrSize = 14;
int main() {
    char *Token = strtok(LookFor_str, ",");
    while (Token != NULL) {

        strcpy(ConversionBuf[ConverBufCounter], Token);
        ConverBufCounter++;

        Token = strtok(NULL, ",");

    }

    printf("%d\n", ConverBufCounter);

    // for (int i = 0; i < ConverBufCounter; i++) {
    //     printf("%s\n", ConversionBuf[i]);
    //     // printf("%d\n", strtol(ConversionBuf[i], NULL, 16));
    // }

    for (int i = 0; i < Example_arrSize; i++) {
        if (strtol(Example_arr[i], NULL, 16) == strtol(ConversionBuf[CharMatch], NULL, 16)) {
            CharMatch++;
        }
      
        else {
            CharMatch = 0;
            if (strtol(Example_arr[i], NULL, 16) == strtol(ConversionBuf[CharMatch], NULL, 16)) { CharMatch++; }
        }

        if (CharMatch == ConverBufCounter) {
            // CharMatch = 0;
            printf("Match founded at %d.\n", i);
            // something(len of LookFor_str)
            printf("Match founded: Starts at %d.\n", i - ConverBufCounter + 1);
        }
        
    }
    
    for (int i = 0; i < Example_arrSize; i++) {
        printf("%s\n", Example_arr[i]); 
    }
    printf("After\n");

    memmove(&Example_arr[0],&Example_arr[1], (Example_arrSize - 1) * 3 * sizeof(char));
    strcpy(Example_arr[Example_arrSize - 1], "23");

    for (int i = 0; i < Example_arrSize; i++) {
        printf("%s\n", Example_arr[i]); 
    }

        
    



    

    

    return 0;
}