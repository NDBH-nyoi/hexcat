#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "useful_macros.c"
#include "other_functions.c"


// this file will be merged with subcommand diff
// place this program infront of the current main
// and make it return 0 before it can reach the current main


typedef struct
{
    long long int address;
    unsigned char offset_num;
} rel_offset;

int rel_offset_ascending_comp(const void* a, const void* b) {
    const rel_offset *BufferA = (const rel_offset *) a;
    const rel_offset *BufferB = (const rel_offset *) b;
    return (BufferA->address - BufferB->address);
}

char *Input_Name1 = "";
char *Input_Name2 = "";
char OPEN_FLAG = 0;
const char *NonExistReturn = "   ";
// "nl "
int OFFSET1 = 0;
int OFFSET2 = 0;
int Matcher = 0; // have to start at one cuz of something

// relative offset (1) implementation

char *Rel_string1 = "";

rel_offset relative_offset1[32];
char temp_storage1[32][16];


unsigned char RelOffset1_index = 0;
unsigned relOffset1_increment = 0;
char RELATIVE_1_FLAG = 0;

// copypaste!

char *Rel_string2 = "";

rel_offset relative_offset2[32];
char temp_storage2[32][16];


unsigned char RelOffset2_index = 0;
unsigned relOffset2_increment = 0;
char RELATIVE_2_FLAG = 0;

int main(int argc, char *argv[]) {
    int i = 1;

    if (argc == 1) {
        printf("No input was specified.\n");
        return 1;
    }

    while (i < argc) {
        if (strcmp(argv[i] ,"-i") == 0) {
            CLI_2ARGS(i, "-i", Input_Name1, Input_Name2, );
        }
        // else if (strcmp(argv[i] ,"-i2") == 0) {
        //     CLI_1ARGS(i, "-i2", Input_Name2);
        // }
        else if (strcmp(argv[i] ,"-op") == 0 || strcmp(argv[i] ,"--open") == 0) {
            CLI_0ARGS(i, "-op", OPEN_FLAG);
        }
        else if (strcmp(argv[i] ,"-of1") == 0 || strcmp(argv[i] ,"--offset1") == 0) {
            CLI_1ARGS(i, "-of1", OFFSET1, atoi);
            
        }
        else if (strcmp(argv[i] ,"-of2") == 0 || strcmp(argv[i] ,"--offset2") == 0) {
            CLI_1ARGS(i, "-of1", OFFSET2, atoi);
        }

        else if (strcmp(argv[i] ,"-r1") == 0) {
            CLI_1ARGS(i, "-r1", Rel_string1, );
            RELATIVE_1_FLAG = 1;
        }
        else if (strcmp(argv[i] ,"-r2") == 0) {
            CLI_1ARGS(i, "-r2", Rel_string2, );
            RELATIVE_2_FLAG = 1;
        }

        else {
            printf("Unknown command or missing arguments: %s.\n", argv[i]);
            printf("Type -h or --help for usage help.\n");
            return 1;
        }
    }
    if (RELATIVE_1_FLAG == 1)
    {
    char *Token = strtok(Rel_string1, " ");

    while (Token != NULL)
    {
        strcpy(temp_storage1[RelOffset1_index], Token);
        RelOffset1_index++;
        Token = strtok(NULL, " ");
    }
    // printf("%d\n", RelOffset1_index);
    for (int i = 0; i < RelOffset1_index; i++)
    {
        char *Token_slash = strtok(temp_storage1[i], "/");

        while (Token_slash != NULL)
        {
            relative_offset1[i].address = strtol(Token_slash, NULL, 16);
            Token_slash = strtok(NULL, "/");
            relative_offset1[i].offset_num = strtol(Token_slash, NULL, 10);
            Token_slash = strtok(NULL, "/");
        }
        
    }

    qsort(relative_offset1, RelOffset1_index, sizeof(rel_offset), rel_offset_ascending_comp);
    }

    if (RELATIVE_2_FLAG == 1)
    {
    char *Token = strtok(Rel_string2, " ");

    while (Token != NULL)
    {
        strcpy(temp_storage2[RelOffset2_index], Token);
        RelOffset2_index++;
        Token = strtok(NULL, " ");
    }
    // printf("%d\n", RelOffset2_index);
    for (int i = 0; i < RelOffset2_index; i++)
    {
        char *Token_slash = strtok(temp_storage2[i], "/");

        while (Token_slash != NULL)
        {
            relative_offset2[i].address = strtol(Token_slash, NULL, 16);
            Token_slash = strtok(NULL, "/");
            relative_offset2[i].offset_num = strtol(Token_slash, NULL, 10);
            Token_slash = strtok(NULL, "/");
        }
        
    }

    qsort(relative_offset2, RelOffset2_index, sizeof(rel_offset), rel_offset_ascending_comp);
    }


    // for (int i =0; i < RelOffset1_index;i++)
    // {
    //     printf("%d\n", relative_offset1[i].address);
    //     printf("%d\n", relative_offset1[i].offset_num);
    // }

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

            if (RELATIVE_1_FLAG == 1)
            {
            if (hexCounter+LineNum-16 == relative_offset1[relOffset1_increment].address)
            {
                for (int i = 0; i < relative_offset1[relOffset1_increment].offset_num;i++)
                {
                    ch1 = fgetc(INPUT_FILE1);
                }
                relOffset1_increment++;
            }
            }
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
            if (RELATIVE_2_FLAG == 1)
            {
            if (hexCounter+LineNum-16 == relative_offset2[relOffset2_increment].address)
            {
                for (int i = 0; i < relative_offset2[relOffset2_increment].offset_num;i++)
                {
                    ch2 = fgetc(INPUT_FILE2);
                }
                relOffset2_increment++;
            }
            }
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
    printf("End of file reached. Total file size: File 1: %lu B. File 2: %lu B. ", FILE1_Size+OFFSET1, FILE2_Size+OFFSET2);
    printf("Total match count: %d.\n", Matcher);
    printf("\n");
    if (OFFSET1 != 0 || OFFSET2 != 0) {
        printf("Offset of file 1: %d.\n", OFFSET1);
        printf("Offset of file 2: %d.\n", OFFSET2);
    }

    if (RELATIVE_1_FLAG==1)
    {
        int TOTAL_OFFSET = 0;
        printf("Relative offset 1:\n");
        for (int i =0; i < RelOffset1_index;i++)
        {
            printf("%08x: %d\n", relative_offset1[i].address, relative_offset1[i].offset_num);
            TOTAL_OFFSET+=relative_offset1[i].offset_num;
        }
        printf("Total offset: %d\n", TOTAL_OFFSET);
    }

    if (RELATIVE_2_FLAG==1)
    {
        int TOTAL_OFFSET = 0;
        printf("Relative offset 2:\n");
        for (int i =0; i < RelOffset2_index;i++)
        {
            printf("%08x: %d\n", relative_offset2[i].address, relative_offset2[i].offset_num);
            TOTAL_OFFSET+=relative_offset1[i].offset_num;
        }
        printf("Total offset: %d\n", TOTAL_OFFSET);
    }

    // printf("Note: nl/NL(Null) means there were no bytes at that position.\n");
    
    

    fclose(INPUT_FILE1);
    fclose(INPUT_FILE2);
    return 0;
}