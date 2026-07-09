#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#include "useful_macros.c"
#include "other_functions.c"

#include "declarations.c" // includes most of the variables' name
// Go here to define new ones



int main(int argc, char *argv[]) {
    
    if (argc == 1) {
        HELP_FLAG = 1;
    
    }
    else {
        SubCommand = argv[1];
    }
    int i = 1; // No subcommands for now. Yes subcommands
    
    if (strcmp(SubCommand, "diff") == 0) {
        printf("Diff sub is here.\n");
        // DIFF_SUB_FLAG = 1;
        int i = 2;
        return 0; // for now, 
    }
    else if (strcmp(SubCommand, "cnv") == 0) {
        printf("Convert sub is here.\n");
        int i = 2;
        return 0; // for now
    }
    else if (strcmp(SubCommand, "w") == 0) {
        printf("Write sub is here.\n");
        // WRITE_SUB_FLAG = 1;
        int i = 2;
        return 0; // for now
    }

    

    
    // ofc if subcommands were passed, this functions should continue over here

    while (i < argc) {
        // standard
        if (strcmp(argv[i], "-i") == 0) {
            CLI_1ARGS(i, "-i", inFileName, ); // note the final empty arg is necessary
        }
        else if (strcmp(argv[i], "-o") == 0) {
            CLI_1ARGS(i, "-o", outFileName, );
            OUTPUT_FLAG = 1;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            CLI_0ARGS(i, "-h", HELP_FLAG);
        }
        else if (strcmp(argv[i], "-caps") == 0) {
            CLI_0ARGS(i, "-caps", CAPITAL_FLAG);
        }
        else if (strcmp(argv[i], "-p") == 0) {
            CLI_1ARGS(i, "-p", PaddingSize, atoi);
        }
        else if (strcmp(argv[i], "--silent") == 0 || strcmp(argv[i], "-sil") == 0) {
            CLI_0ARGS(i, "-sil", SILENT_FLAG);
        }
        else if (strcmp(argv[i], "-ref") == 0) {
            CLI_0ARGS(i, "-ref", REFERENCE_FLAG);
        }
        // statistics
        else if (strcmp(argv[i], "--stats") == 0 || strcmp(argv[i], "-st") == 0) {
            CLI_0ARGS(i, "-stats", STATS_FLAG);
        }
        else if (strcmp(argv[i], "-st-c") == 0) {
            CLI_1ARGS(i, "-st-c", COLUMN_NUMBER, atoi);
        }
        else if (strcmp(argv[i], "-st-p") == 0) {
            CLI_1ARGS(i, "-st-c", STATS_PADDING, atoi);
        }
        else if (strcmp(argv[i], "-st-sp") == 0) {
             CLI_1ARGS(i, "-st-c", STATS_SPACEPADDING, atoi);
        }
        else if (strcmp(argv[i], "--freq") == 0) {
            CLI_0ARGS(i, "--freq", STATS_FREQ_FLAG);
        }
        else if (strcmp(argv[i], "-st-v") == 0) {
            CLI_0ARGS(i, "-st-v", STATS_VERBOSE_FLAG);
        }
        // matching
        else if (strcmp(argv[i], "--match") == 0 || strcmp(argv[i], "-m") == 0) {
            CLI_1ARGS(i, "-m", MATCH_STRING, );
            MATCH_FLAG = 1;
        }

        else if (strcmp(argv[i], "-m-p") == 0) {
             CLI_1ARGS(i, "-st-c", MatchIndexPadding, atoi);
        }
        // section
        else if (strcmp(argv[i], "-sec") == 0) {
            if (i + 2 >= argc) { 
                printf("Error: " "-sec" " requires 2 arguments.\n"); 
                return 1; 
            } 
            SECTION_START = strtol(argv[i+1], NULL, 16);
            SECTION_END = strtol(argv[i+2], NULL, 16);
            // bit manip magic lmao
            if (SECTION_START > SECTION_END) {
                printf("Error: " "Start can not be larger than end.\n");
                return 1;
            }
            SECTION_START = SECTION_START & ~0xf;
            SECTION_END = SECTION_END & ~0xf;
            
            SECTION_FLAG = 1;
            i+=3; 
        }
        else if (strcmp(argv[i], "--line") == 0 || strcmp(argv[i], "-l") == 0) {
            if (i + 1 >= argc) { 
                CLI_1ARGSERR("-l");
                return 1; } 
            SECTION_START = strtol(argv[i+1], NULL, 16);
            SECTION_END = strtol(argv[i+1], NULL, 16); 
            SECTION_START = SECTION_START & ~0xf;
            SECTION_END = SECTION_END & ~0xf; 
            SECTION_FLAG = 1;
            i+=2;
        }
        else if (strcmp(argv[i], "-se1") == 0) {
            if (i + 1 >= argc) { 
                CLI_1ARGSERR("-se1");
                return 1; } 
            SECTION_START = strtol(argv[i+1], NULL, 16);
            SECTION_END = strtol(argv[i+1], NULL, 16); 
            SECTION_START = (SECTION_START & ~0xf) - 16;
            SECTION_END = (SECTION_END & ~0xf) + 16;
            SECTION_FLAG = 1;
            i+=2;
        }
        // ending
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

    if (strcmp(inFileName, outFileName)==0) {
        printf("Input and output files can not be the same.\n");
        return 1;
    }

    strcpy(RETURN_MATCH_STR, MATCH_STRING);

    if (MATCH_FLAG == 1) {
        char *Token = strtok(MATCH_STRING, " ");
        // So its seem there's some conflict on whether to use " " or ",".
        while (Token != NULL) {

            ConversionBuf[ConverBufCounter] = strtol(Token, NULL, 16);
            // printf("%d\n",(int)strtol(Token, NULL, 16));
            // implement error handling for strtol here
            ConverBufCounter++;
            Token = strtok(NULL, " ");
        }
    }
    if (ConverBufCounter > 32 && MATCH_FLAG == 1) {
        printf("Exceed matching string's buffer.\n");
        return 1;
    }

    printf("\n");
    printf("%*s", PaddingSize + 2,"");
    for (int i = 0; i < 16; i++) {
        printf(_FormatHexChar, i);
    }
    for (int i = 0; i < 16; i++) {
        printf("%x", i);
    }
    printf("\n");
    

    FILE *INPUT_FILE  = fopen(inFileName, "rb");
    FILE *OUTPUT_FILE;
    if (OUTPUT_FLAG == 1) {
        OUTPUT_FILE = fopen(outFileName, "ab");
    }
    
    while ((ch = fgetc(INPUT_FILE)) != EOF) {
        // printf("%c", ch);
        if (Hex_Counter == 16) {
            Hex_Counter = 0;
            // this code is making crine...
            LineNum+=16;

            if ((LineNum-16) == SECTION_START && SECTION_FLAG == 1) {
            SECTION_PRINT_MARKER = 1;
            }
            if ((LineNum-16) == (SECTION_END+16) && SECTION_FLAG == 1) {
                SECTION_PRINT_MARKER = 0;
            }

            LineNum-=16;
            // was SILENT_FLAG != 1
            if ((!SILENT_FLAG && !SECTION_FLAG) || (SECTION_FLAG && SECTION_PRINT_MARKER)) {
                printf("\n");
                printf(_FormatIndex, PaddingSize ,LineNum); // %08x could be changed
            }
            LineNum+=16;
        }
        // section print marker switch
        
        // SILENT_FLAG != 1 && SECTION_FLAG != 1
        if ((!SILENT_FLAG && !SECTION_FLAG) || (SECTION_FLAG && SECTION_PRINT_MARKER)) {
            printf(_FormatHexChar, ch);
        }
        if (OUTPUT_FLAG == 1) {
            fprintf(OUTPUT_FILE,"%c", ch);
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

        if (Hex_Counter == 16) {
            // printf(" "); // separator, is actually 2 spaces cuz of "%.2x " you know.
            //All of these was replaced from SILENT_FLAG == 1
            if ((!SILENT_FLAG && !SECTION_FLAG) || (SECTION_FLAG && SECTION_PRINT_MARKER)) {
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

    if ((!SILENT_FLAG && !SECTION_FLAG) || (SECTION_FLAG && SECTION_PRINT_MARKER)) {
        for (int i = 0; i < 16 - Hex_Counter; i++) {
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
    if (SECTION_FLAG == 1) {
        printf("\n");
        printf("End of section reached. From %0*x to %0*x. ",PaddingSize,SECTION_START,PaddingSize,SECTION_END);
        printf("Total length: %llu line(s).\n", (SECTION_END - SECTION_START)/16 + 1);
    } 

    printf("End of file reached. Total file size: %llu B.\n", LineNum - (16 - Hex_Counter));
    
    if (LineNum - (16 - Hex_Counter) == 0) {
        printf("Input was likely incorrect: %s\n", inFileName);
    }

    if (REFERENCE_FLAG == 1) {
        PRINT_REFERENCE();
    }

    if (MATCH_FLAG == 1) {
        printf("\n");
        printf("Displaying start positions.\n");
        printf("Matches to %s (length +%d): \n", RETURN_MATCH_STR, ConverBufCounter);

        for (int i = 0; i < PositionCounter; i++) {
            printf("%0*d  ", MatchIndexPadding ,i+1); // this will act as an index
            printf("%0*x    ", PaddingSize ,matchesPosition[i]);
            if ((i+1) % 4 == 0) {
                printf("\n");
            }
            // changed to print spaces instead of newlines
        }
        if (PositionCounter == 0) {
            printf("No matches founded.\n");
        }
        printf("\n" "Total match count: %d.\n", PositionCounter);
    }
    // these are stats support
    if (STATS_FREQ_FLAG == 1 && STATS_FLAG == 0) {
        printf("Frequency flag --freq has to be used with --stats.\n");
        return 1;}

    if (STATS_PADDING > 16 || STATS_PADDING == 0) {
        printf("Stats padding size is invalid or too large: %d.", STATS_PADDING);
        return 1;}

    if (STATS_SPACEPADDING > 16 || STATS_SPACEPADDING == 0) {
        printf("Stats space padding size is invalid or too large: %d.", STATS_SPACEPADDING);
        return 1;}

    if (COLUMN_NUMBER > 16 || COLUMN_NUMBER == 0) {
        printf("Column number is invalid or too large: %d.", COLUMN_NUMBER);
        return 1;}

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
    if (OUTPUT_FLAG == 1) {
        fclose(OUTPUT_FILE);
    }
    return 0;
}