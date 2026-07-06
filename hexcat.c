#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#include "useful_macros.c"
#include "other_functions.c"


// Input segment
char *inFileName = "";
char HELP_FLAG = 0; // false. Also the "\0" character.
char CAPITAL_FLAG = 0;

unsigned char PaddingSize = 8; // default padding size

char STATS_FLAG = 0;
char STATS_FREQ_FLAG = 0;
char STATS_VERBOSE_FLAG = 0;
unsigned char STATS_PADDING = 4; // Haven't done any work yet
unsigned char STATS_SPACEPADDING = 4;
unsigned char COLUMN_NUMBER = 8;

unsigned int byteStats[256] = {0}; // each index represent the value of that byte e.g 0x10 is at index 16

char *MATCH_STRING="";
char RETURN_MATCH_STR[96] = "";
char MATCH_FLAG = 0;

char SILENT_FLAG = 0;

// Can probably do a comparision, and do a stats print with order most frequent to least frequent.
// if you want, you can make it so bytes with no appearance doesn't get printed.


// LOOK HERE FOR DIRECTIVES!!!

int ch;

// char *_Format = "%.2x ";
int HexPerLine = 16;
int Buf_forChars16[16]; // chances are this will be malloc

int Hex_Counter = 16; // will be resetted to 0 later for hex counter = hexperline
unsigned long long int LineNum = 0; 

int main(int argc, char *argv[]) {
    int i = 1; // No subcommands for now

    if (argc == 1) {
        HELP_FLAG = 1;
    }

    while (i < argc) {
        if (strcmp(argv[i], "-i") == 0) {
            CLI_1ARGS(i, "-i", inFileName);
        }

        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            CLI_0ARGS(i, "-h", HELP_FLAG);

        }
        else if (strcmp(argv[i], "-caps") == 0) {
            CLI_0ARGS(i, "-caps", CAPITAL_FLAG);
        }
        else if (strcmp(argv[i], "--stats") == 0) {
            CLI_0ARGS(i, "-stats", STATS_FLAG);
        }
        else if (strcmp(argv[i], "--padding") == 0 || strcmp(argv[i], "-p") == 0) {
            if (i + 1 >= argc) { 
                printf("Error: " "-p" " requires an argument.\n"); 
                return 1; 
                } 
                PaddingSize = atoi(argv[i+1]); 
                i+=2; 
        }

        else if (strcmp(argv[i], "--stats-colnum") == 0 || strcmp(argv[i], "-st-c") == 0) {
            if (i + 1 >= argc) { 
                printf("Error: " "-st-c" " requires an argument.\n"); 
                return 1; 
                } 
                COLUMN_NUMBER = atoi(argv[i+1]); 
                i+=2; 
        }

        else if (strcmp(argv[i], "--stats-padding") == 0 || strcmp(argv[i], "-st-p") == 0) {
            if (i + 1 >= argc) { 
                printf("Error: " "-st-p" " requires an argument.\n"); 
                return 1; 
                } 
                STATS_PADDING = atoi(argv[i+1]); 
                i+=2; 
        }
        else if (strcmp(argv[i], "--stats-space") == 0 || strcmp(argv[i], "-st-sp") == 0) {
            if (i + 1 >= argc) { 
                printf("Error: " "-st-space" " requires an argument.\n"); 
                return 1; 
                } 
                STATS_SPACEPADDING = atoi(argv[i+1]); 
                i+=2; 
        }
        else if (strcmp(argv[i], "--freq") == 0) {
            CLI_0ARGS(i, "--freq", STATS_FREQ_FLAG);
        }
        else if (strcmp(argv[i], "--stats-verbose") == 0 || strcmp(argv[i], "-st-v") == 0) {
            CLI_0ARGS(i, "-st-v", STATS_VERBOSE_FLAG);
        }
        else if (strcmp(argv[i], "--match") == 0 || strcmp(argv[i], "-m") == 0) {
            CLI_1ARGS(i, "-m", MATCH_STRING);
            MATCH_FLAG = 1;
        }

        else if (strcmp(argv[i], "--silent") == 0 || strcmp(argv[i], "-sil") == 0) {
            CLI_0ARGS(i, "-sil", SILENT_FLAG);
        }

        else {
            printf("Unknown command or missing arguments: %s.\n", argv[i]);
            printf("Type -h or --help for usage help.\n");
            return 1;
        }
    }

    if (PaddingSize > 16 || PaddingSize == 0 || PaddingSize == 1) {
        printf("Padding size is invalid or too large: %d.", PaddingSize);
        return 1;
    }

    char *_FormatIndex = "%0*x  ";
    char *_FormatHexChar = "%.2x ";

    if (CAPITAL_FLAG == 1) {
        _FormatIndex = "%0*X  ";
        _FormatHexChar = "%.2X ";
    }
    if (HELP_FLAG == 1) {
        PRINT_HELP(); // Go to print help to write additional help
        if (strcmp(inFileName, "") == 0) {
            return 1;
        }
    }

    unsigned char ConversionBuf[32]; // streamed into from input
    unsigned char ConverBufCounter = 0; // counter for conversion buf, also length of conversion buf
    unsigned char ComparisonBuf[32]; // streamed into from fgetc, is int also
    // Max length should be equal to length of conversion buf, 
    //when that happens, we start doing memmove stuff 
    unsigned char CompareCounter = 0;
    long long int matchesPosition[32]; // holds matches position
    unsigned char PositionCounter = 0;
    unsigned char EqualCounter = 0;
    // Also do it so if ConverBufCounter, ComparisonCounter > 32 then exit

    strcpy(RETURN_MATCH_STR, MATCH_STRING);

    if (MATCH_FLAG == 1) {
        char *Token = strtok(MATCH_STRING, ",");
        while (Token != NULL) {

            ConversionBuf[ConverBufCounter] = strtol(Token, NULL, 16);
            // printf("%d\n",(int)strtol(Token, NULL, 16));
            // implement error handling for strtol here
            ConverBufCounter++;
            Token = strtok(NULL, ",");
        }
    }
    if (ConverBufCounter > 32 && MATCH_FLAG == 1) {
        printf("Exceed matching string's buffer.\n");
        return 1;
    }

    FILE *INPUT_FILE  = fopen(inFileName, "rb");

    while ((ch = fgetc(INPUT_FILE)) != EOF) {
        // printf("%c", ch);

        if (Hex_Counter == HexPerLine) {
            Hex_Counter = 0;
            if (SILENT_FLAG != 1) {
                printf("\n");
                printf(_FormatIndex, PaddingSize ,LineNum); // %08x could be changed
            }
            LineNum+=HexPerLine;
        }
        
        if (SILENT_FLAG != 1) {
            printf(_FormatHexChar, ch);
        }

        if (MATCH_FLAG == 1) {
            if (CompareCounter != ConverBufCounter) {
                ComparisonBuf[CompareCounter] = ch;
                CompareCounter++;
            }
            else {
                memmove(&ComparisonBuf[0],&ComparisonBuf[1],(CompareCounter-1) * sizeof(unsigned char));
                ComparisonBuf[CompareCounter-1] = ch;
            }   
            for (int i=0; i < ConverBufCounter;i++) {
                if (ComparisonBuf[i] != ConversionBuf[i]) {
                    EqualCounter = 0;
                    break;
                }
                else { EqualCounter++; }
            }
            if (EqualCounter == ConverBufCounter) {
                matchesPosition[PositionCounter] = (LineNum - 16) + Hex_Counter - ConverBufCounter + 1;
                PositionCounter++;
                EqualCounter = 0;
            }
        }
        if (STATS_FLAG == 1) {
            byteStats[ch]++;
        }

        Buf_forChars16[Hex_Counter] = ch;
        Hex_Counter++;

        if (Hex_Counter == HexPerLine) {
            // printf(" "); // separator, is actually 2 spaces cuz of "%.2x " you know.
            if (SILENT_FLAG != 1) {
                for (int i = 0; i < 16; i++) {
                    if (is_escape_char(*(Buf_forChars16+i)) == 1) {
                        printf(".");
                    }
                    else {
                        printf("%c", *(Buf_forChars16+i));
                    }
                }
            } 
        }
    }
    // this part is for dealing with the residue characters
    // that weren't printed

    if (SILENT_FLAG != 1) {
        for (int i = 0; i < HexPerLine - Hex_Counter; i++) {
            printf("   ");
        }
        for (int i = 0; i < Hex_Counter; i++) {
            if (is_escape_char(*(Buf_forChars16+i)) == 1) {
                printf(".");
            }
            else {
                printf("%c", *(Buf_forChars16+i));
            }
        }
    }
    printf("\n");

    printf("End of file reached. Total file size: %llu B.\n", LineNum - (HexPerLine - Hex_Counter));
    
    if (LineNum - (HexPerLine - Hex_Counter) == 0) {
        printf("Input was likely incorrect: %s\n", inFileName);
    }
    if (MATCH_FLAG == 1) {
        printf("\n");
        printf("Matches to %s (length +%d): \n", RETURN_MATCH_STR, ConverBufCounter);

        for (int i = 0; i < PositionCounter; i++) {
            printf("Match starting at position %x.\n", matchesPosition[i]);
        }
        if (PositionCounter == 0) {
            printf("No matches founded.\n");
        }
    }
    if (STATS_FREQ_FLAG == 1 && STATS_FLAG == 0) {
        printf("Frequency flag --freq has to be used with --stats.\n");
        return 1;
    }
    if (STATS_PADDING > 16 || STATS_PADDING == 0) {
        printf("Stats padding size is invalid or too large: %d.", STATS_PADDING);
        return 1;
    }
    if (STATS_SPACEPADDING > 16 || STATS_SPACEPADDING == 0) {
        printf("Stats space padding size is invalid or too large: %d.", STATS_SPACEPADDING);
        return 1;
    }
    if (COLUMN_NUMBER > 16 || COLUMN_NUMBER == 0) {
        printf("Column number is invalid or too large: %d.", COLUMN_NUMBER);
        return 1;
    }
    if (STATS_FLAG == 1) {
        printf("\n");
        printf("Byte frequency: \n");
        if (STATS_VERBOSE_FLAG == 1) {
            for (int i = 0; i < 256; i++) {
                if (i % COLUMN_NUMBER == 0) {
                    printf("\n");
                }
                printf("%.2x: %.*u", i, STATS_PADDING, byteStats[i]);
                printf("%*s", STATS_SPACEPADDING, "");
            }
        }
        else {
            printf("Hex with 0 occurences are hidden.\n");
            int Hidden_ColumnCounter = 0;
            for (int i = 0; i < 256; i++) {
                if (Hidden_ColumnCounter % (COLUMN_NUMBER+1) == 0) {
                    printf("\n");
                    Hidden_ColumnCounter++;
                }
                if (byteStats[i] != 0) {
                    printf("%.2x: %.*u", i, STATS_PADDING, byteStats[i]);
                    printf("%*s", STATS_SPACEPADDING, "");
                    Hidden_ColumnCounter++;
                }                      
            }
        }
    }
    
    printf("\n");
    
    fclose(INPUT_FILE);
    return 0;
}