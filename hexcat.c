#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CLI_0ARGS(counter, flag, arg1) do {\
    arg1=1;\
    counter+=1;\
} while(0)\

#define CLI_1ARGS(counter, flag, arg1) do {\
if (counter + 1 >= argc) { \
    printf("Error: " flag " requires an argument.\n"); \
    return 1; \
} \
arg1 = argv[counter+1]; \
counter+=2; \
} while(0)\

#define CLI_2ARGS(counter, flag, arg1, arg2) do {\
    if (counter + 2 >= argc) { \
        printf("Error: " flag " requires 2 arguments.\n"); \
        return 1; \
    } \
    arg1 = argv[counter+1];\
    arg2 = argv[counter+2];\
    counter+=3; \
} while(0)\

// #define BACKGROUND_COLOR(r,g,b) "\e[48;2;" r ";" g ";" b "m"
// #define RED "\e[48;2;255;0;0m"
// #define GREEN "\e[48;2;0;255;0m"
// #define BLUE "\e[48;2;0;0;255m"
// #define YELLOW "\e[48;2;255;255;0";
// #define PURPLE "\e[48;2;128;0;128";

// #define RESET "\e[0m"

int is_escape_char(char ch) {
    switch (ch) {
        case '\n':
        case '\r':
        case '\t':
        case '\v':
        case '\b':
        case '\f':
        case '\a':
        case '\\':
        case '\'':
        case '\"':
        case '\?': 
        case '\0':
            return 1; // true
        default:
            return 0; // false
    }
}

//.\\test - Copy.exe 
//.\\shorter_example.txt

// Guess if I want to use the --highlight flag multiple times,
// the idea would be to just create a buffer write the input into the buffer
//highlight either: -hl blue or -hl 0 0 255.


// Input segment
char *inFileName = "";
char HELP_FLAG = 0; // false. Also the "\0" character.
char CAPITAL_FLAG = 0;

unsigned char PaddingSize = 8; // default padding size

int ch;

// char *_Format = "%.2x ";
int HexPerLine = 16;
int Buf_forChars16[16]; // chances are this will be malloc

int Hex_Counter = 16; // will be resetted to 0 later for hex counter = hexperline
unsigned long long int LineNum = 0; 
// this can actually be change to unsigned long and long long int for larger files


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

        else if (strcmp(argv[i], "--padding") == 0 || strcmp(argv[i], "-p") == 0) {
            if (i + 1 >= argc) { 
                printf("Error: " "-p" " requires an argument.\n"); 
                return 1; 
                } 
                PaddingSize = atoi(argv[i+1]); 
                i+=2; 
        }
        else {
            printf("Unknown command or missing arguments: %s.\n", argv[i]);
            printf("Type -h or --help for usage help.\n");
            return 1;
        }
    }

    if (PaddingSize > 16 || PaddingSize == 0 || PaddingSize == 1) {
        printf("Padding size invalid or too large: %d.", PaddingSize);
        return 1;
    }

    char *_FormatIndex = "%0*x  ";
    char *_FormatHexChar = "%.2x ";

    if (CAPITAL_FLAG == 1) {
        _FormatIndex = "%0*X  ";
        _FormatHexChar = "%.2X ";
    }
    
    if (HELP_FLAG == 1) {
        printf("Usage: hexcat.exe [flags] <args>...\n");
        printf("-i <args>: File input.\n");
        printf("-p --padding <args>: Specify index padding. Default value is 8.\n");
        printf("-caps: Capitalizes hex characters.\n");
        printf("-h --help: Show this list.\n");

        if (strcmp(inFileName, "") == 0) {
            return 1;
        }
    }

    FILE *INPUT_FILE  = fopen(inFileName, "rb");

    while ((ch = fgetc(INPUT_FILE)) != EOF) {
        // printf("%c", ch);

        if (Hex_Counter == HexPerLine) {
            Hex_Counter = 0;
            printf("\n");
            printf(_FormatIndex, PaddingSize ,LineNum); // %08x could be changed
            LineNum+=HexPerLine;
        }
        
        printf(_FormatHexChar, ch);
        

        Buf_forChars16[Hex_Counter] = ch;
        Hex_Counter++;

        if (Hex_Counter == HexPerLine) {
            // printf(" "); // separator, is actually 2 spaces cuz of "%.2x " you know.
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
    
    // this part is for dealing with the residue characters
    // that weren't printed

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

    printf("\n");

    printf("End of file reached. Total file size: %llu B.\n", LineNum - (HexPerLine - Hex_Counter));
    
    if (LineNum - (HexPerLine - Hex_Counter) == 0) {
        printf("Input was likely incorrect: %s\n", inFileName);
    }

    printf("\n");
    
    fclose(INPUT_FILE);
    return 0;
}

