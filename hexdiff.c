#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "useful_macros.c"
#include "other_functions.c"


// this file will be merged with subcommand diff
// place this program infront of the current main
// and make it return 0 before it can reach the current main


char *Input_Name1 = "";
char *Input_Name2 = "";
char OPEN_FLAG = 0;
const char *NonExistReturn = "   ";
// "nl "
int OFFSET1 = 0;
int OFFSET2 = 0;
int Matcher = 0; // have to start at one cuz of something
int main(int argc, char *argv[]) {
    int i = 1;

    if (argc == 1) {
        printf("No input was specified.\n");
        return 1;
    }

    while (i < argc) {
        if (strcmp(argv[i] ,"-i") == 0) {
            CLI_2ARGS(i, "-i", Input_Name1, Input_Name2);
        }
        // else if (strcmp(argv[i] ,"-i2") == 0) {
        //     CLI_1ARGS(i, "-i2", Input_Name2);
        // }
        else if (strcmp(argv[i] ,"-op") == 0 || strcmp(argv[i] ,"--open") == 0) {
            CLI_0ARGS(i, "-op", OPEN_FLAG);
        }
        else if (strcmp(argv[i] ,"-of1") == 0 || strcmp(argv[i] ,"--offset1") == 0) {
            if (i + 1 >= argc) { 
                printf("Error: " "-of1" " requires an argument.\n"); 
                return 1; 
            } 
            OFFSET1 = atoi(argv[i+1]);
            i+=2; 
        }
        else if (strcmp(argv[i] ,"-of2") == 0 || strcmp(argv[i] ,"--offset2") == 0) {
            if (i + 1 >= argc) { 
                printf("Error: " "-of2" " requires an argument.\n"); 
                return 1; 
            } 
            OFFSET2 = atoi(argv[i+1]);
            i+=2; 
        }
        else {
            printf("Unknown command or missing arguments: %s.\n", argv[i]);
            printf("Type -h or --help for usage help.\n");
            return 1;
        }
    }
    FILE *INPUT_FILE1 = fopen(Input_Name1, "rb");
    FILE *INPUT_FILE2 = fopen(Input_Name2, "rb");
    int ch1 = 0;
    int ch2 = 0;
    unsigned long long int LineNum = 0;
    unsigned char hexCounter = 0;
    unsigned char HexperLine = 16;

    unsigned long int FILE1_Size = 0; // for now its just unsigned long int
    unsigned long int FILE2_Size = 0;

    char BREAKAT_1_FLAG = 0;
    
    int Buf_forChars16_f1[16];
    int Buf_forChars16_f2[16];

    for (int i = 0; i < OFFSET1; i++) {
        ch1 = fgetc(INPUT_FILE1);
    }
    for (int i = 0; i < OFFSET2; i++) {
        ch2 = fgetc(INPUT_FILE2);
    }
    
    while (ch1 != EOF || ch2 != EOF) {
        if (OPEN_FLAG == 1) {
            printf("\n"); // A seperator option
        } 
        printf("%08x  ", LineNum);
        LineNum+=HexperLine;
        for (int i = 0; i < HexperLine; i++) {
            ch1 = fgetc(INPUT_FILE1);
            Buf_forChars16_f1[hexCounter] = ch1;
            if (ch1 == EOF) {
                printf(NonExistReturn);
            }
            else {
                printf("%.2x ", ch1);
                FILE1_Size++;
            }
            hexCounter++;
        }

        // This for padding purposes
        if (hexCounter != 16) {
            printf("%*s", 3 * (16 - hexCounter), "");
        }
        // replaced with hexCounter instead of just 16 to avoid printing garbage
        for (int i = 0; i < hexCounter; i++) {
            if (is_escape_char(Buf_forChars16_f1[i]) == 1) {
                printf(".");
            }
            else {
                printf("%c", Buf_forChars16_f1[i]);
            }
        }
        if (hexCounter == 16) {
            hexCounter = 0;
            printf("\n");
            printf("%*s  ",8, "->");
        }
        
        for (int i = 0; i < HexperLine; i++) {
            ch2 = fgetc(INPUT_FILE2);
            Buf_forChars16_f2[hexCounter] = ch2;
            if (ch2 == EOF) {
                printf(NonExistReturn);
            }
            else {
                printf("%.2x ", ch2);
                FILE2_Size++;
            }
            hexCounter++;
        }

        if (hexCounter != 16) {
            printf("%*s", 3 * (16 - hexCounter), "");
        }
        // replaced with hexCounter instead of just 16 to avoid printing garbage
        for (int i = 0; i < hexCounter; i++) {
            if (is_escape_char(Buf_forChars16_f2[i]) == 1) {
                printf(".");
            }
            else {
                printf("%c", Buf_forChars16_f2[i]);
            }
        }
        if (hexCounter == 16) {
            hexCounter = 0;
            printf("\n");
        }

        // comparing the two files for match percentage
        for (int i = 0; i < 16; i++) {
            if ((Buf_forChars16_f1[i] == Buf_forChars16_f2[i]) && Buf_forChars16_f1[i] != EOF) {
                Matcher++;
            }
        }
    }  

    // printf("\n");
    printf("End of file reached. Total file size: File 1: %lu B. File 2: %lu B. ", FILE1_Size, FILE2_Size);
    printf("Total match count: %d.\n", Matcher);
    printf("\n");
    if (OFFSET1 != 0 || OFFSET2 != 0) {
        printf("Offset of file 1: %d.\n", OFFSET1);
        printf("Offset of file 2: %d.\n", OFFSET2);
    }
    // printf("Note: nl/NL(Null) means there were no bytes at that position.\n");
    
    

    fclose(INPUT_FILE1);
    fclose(INPUT_FILE2);
    return 0;
}