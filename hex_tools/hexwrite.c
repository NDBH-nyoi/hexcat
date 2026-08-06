#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <regex.h>
#include <limits.h>

// weird stuff
// #include "..\other_functions.c"

#define REGEX_MATCHES_PREALLOC 256
#define TEMP_FILE_NAME "TEMPORARY_FILE__.txt"
char Command[64] = "";
char TokensBuf[32][96]; // enough to contain <num1,num2,...> type of strings
unsigned char TokensCount = 0;
char *Token;

enum edit_mode {
    replace = 0,
    pushback = 1,
    delete = 2,
    append = 3
};

typedef struct {
    unsigned long long int position;
    unsigned char hex_arr[32];
    unsigned char hex_len; // < 32 ok
    enum edit_mode mode;
} edit_buffer;

int edit_buf_ascending_comp(const void* a, const void* b) {
    const edit_buffer *BufferA = (const edit_buffer *) a;
    const edit_buffer *BufferB = (const edit_buffer *) b;
    return (BufferA->position - BufferB->position);
}

// 4 main commands i guess
// r: replace
// pb: push back
// d: delete
// ap: append // do something with this I guess

// for now
int is_escape_char(char ch) {
    if ((ch >= 0 && ch <= 31) || ch == 127 || ch == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

int is_alphanum(char ch){
    if (ch >= 0x20 && ch <= 0x7e) {
        return 1;
    }
    else return 0;
}

void PRINT_REFERENCE(){
    printf("\n");
    printf("Useful references: \n");
    printf("All characters from 00 to 1f and 7f are control characters.\n");
    printf("Especially important characters:\n");
    printf("0a: Line feed/ new line.\n");
    printf("0d: Carriage return.\n");
}

// required for hexcat
// char *inFileName = ""; //this is not needed
char outFileName[64] = "";
char OUTPUT_FLAG = 0;

char SAVE_FLAG = 0;

FILE *OUTPUT_FILE;

char HELP_FLAG = 0; // false. Also the "\0" character.
char CAPITAL_FLAG = 0;

unsigned char PaddingSize = 8; // default padding size

char STATS_FLAG = 0;
char STATS_FREQ_FLAG = 0; // not implemented
char STATS_VERBOSE_FLAG = 0;
unsigned char STATS_PADDING = 4; // Haven't done any work yet
unsigned char STATS_SPACEPADDING = 4;
unsigned char COLUMN_NUMBER = 8;

// needs to be here

char TEXT_FLAG = 0;
char STRING_FLAG =0;

unsigned int byteStats[256] = {0}; // each index represent the value of that byte e.g 0x10 is at index 16

char MATCH_STRING[64]=""; // promotion to 64 
char RETURN_MATCH_STR[96] = "";
char MATCH_FLAG = 0;
unsigned char MatchIndexPadding = 3; // 3 now

char SILENT_FLAG = 0;
char REFERENCE_FLAG = 0;


// LOOK HERE FOR DIRECTIVES!!!
int ch;

// char *_Format = "%.2x ";
// int HexPerLine = 16;


unsigned long long int SECTION_START = 0;
unsigned long long int SECTION_END = 0;
char SECTION_PRINT_MARKER = 0;
char SECTION_FLAG = 0;

char REPLACE_FLAG = 0;
char PUSHBACK_FLAG = 0;
char DELETE_FLAG = 0;
char APPEND_FLAG = 0;


int temp_max_len = 0; // temp aight
int temp_increment = 0;

// you can't just strcpy into a pointer!
char REGEX_STRING[96]=""; 
char REGEX_FLAG = 0;

volatile sig_atomic_t breakout_flag = 1;

void interrput_handler(int sig) {
    breakout_flag = 0;
    printf("\n\nInterrupt detected. To exit program type \"exit\".\n");
}

void print_help() {
printf("Usage: (hxc) <command> <args>...\n");
printf("General commands:\n");
printf("file: Display the current loaded file.\n");
printf("o <arg>: Save the current buffer into a file. The save file's name can not be the loaded file. ");
printf("Also the save file's name can not have any spaces.\n");
printf("ocl: Clears the current output buffer.\n");
printf("save: Writes the current buffer into a file with the same name.\n");
printf("savecl: Resets the save option.\n");
printf("\n");
printf("Reading commands:\n");
printf("p: Starts printing hexdump.\n");
printf("sil: Silent mode. Hides hexdump until turned off. Use again to turn off.\n");
printf("\n");
printf("m <num1,num2,...>: Find positions of matches to the hexadecimal string <num1,num2,...>.\n");
printf("mcl: Clears the matches buffer.\n");
printf("\n");
printf("E <str>: Find positions of matches to the text string <str> based on ERE regex.\n");
printf("Ecl: Clears the regex buffer.\n");
printf("\n");
printf("s <arg1> <arg2>: Prints only the section from <arg1> to <arg2>. <arg1> and <arg2> are rounded ");
printf("to the nearest \"tens\" place. Example: 4d2 will become 4d0.\n");
printf("l <arg>: Prints only the line <arg>.\n");
printf("scl: Clears the section buffer.\n");
printf("\n");
printf("Editing commands:\n");
printf("re <position> <num1,num2,...>: Replaces from <position> with <num1,num2,...>.\n");
printf("pb <position> <num1,num2,...>: Pushes back from <position> with <num1,num2,...>.\n");
printf("dl <position> <num>: delete from <position> <num> times.\n");
printf("ap <num1,num2,...>: Appends <num1,num2,...> to the end of the file.\n");
printf("dp: Display current active edit buffers.\n");
printf("db <num>: Delete buffer at <num>. Position is shown in \"dp\".\n");
printf("\n");
printf("Formatting and other commands:\n");
printf("pad <num>: Specify padding for index. Default is 8.\n");
printf("caps: Turn on capital letters for hex. Use again to turn off.\n");
printf("st: Turn on stats. Display the number of occurences of each byte value. Use again to turn off.\n");
printf("cls: Clears screen. Note: This is a shell macro.\n");
printf("exit: Exit program.\n");
printf("help: Display help.\n");
}


int main(int argc, char *argv[])
{

    if (argc != 2) {
        return 1;
    }
    char *inFileName = argv[1];
    FILE *INPUT_FILE = fopen(inFileName, "rb");
    printf("Loaded file(-i): %s\n", inFileName);

    // creating the main buffer, raised up to 64 buffers
    edit_buffer editor_buf[64];
    unsigned char editor_counter = 0;
    unsigned char editor_increment = 0;


    
    while (strcmp(Command, "exit") != 0 && strcmp(Command, "q") != 0) 
    {
        TokensCount = 0;
        
        char PRINT_FLAG = 0;

        for (int i=0; i < 32; i++) {
            TokensBuf[i][16] = '\0';
        }
        // memset to 0!

        printf("(hxc) ");
        fgets(Command, 64, stdin);
        Command[strcspn(Command, "\n")] = '\0';

        // printf("Command: %s", Command);
        
        Token = strtok(Command, " ");

        while (Token != NULL) {
            // printf("%s\n", Token);
            strcpy(TokensBuf[TokensCount], Token);

            Token = strtok(NULL, " ");
            TokensCount++;
        }
        // for debugging
        // for (int i = 0; i < TokensCount; i++) {
        //     printf("tok %d: %s\n",i, TokensBuf[i]);
        // }
        // printf("Total tokens: %d\n", TokensCount);
        int i = 0;
        while (i < TokensCount)
        {
            if (strcmp("re", TokensBuf[i])==0) // re for replace
            {
                if (TokensBuf[i+2][0] == '\0') { 
                    printf("Error: " "re" " requires 2 arguments.\n");
                }
                else {
                    edit_buffer temp;
                    unsigned char temp_edit_arr[32];
                    char temp_counter=0;
                    temp.position = strtol(TokensBuf[i+1], NULL, 16);

                    printf("Replacement string: %s", TokensBuf[i+2]);

                    unsigned char *hex_tok = strtok(TokensBuf[i+2], ",");
                    while (hex_tok != NULL) {
                        if (strtol(hex_tok, NULL, 16) >= 0xff) {
                            printf("\nError: bad input, exceeded 0xff.\n");
                            break;
                        }
                        temp_edit_arr[temp_counter] = strtol(hex_tok, NULL, 16);

                       

                        temp_counter++;
                        hex_tok = strtok(NULL, ",");
                    }
                    memcpy(temp.hex_arr, temp_edit_arr, sizeof(temp_edit_arr));
                    temp.hex_len = temp_counter;

                    printf("(length: +%u), start pos: 0x%x\n", temp.hex_len, temp.position);

                    temp.mode = replace;
                    
                    editor_buf[editor_counter] = temp;
                    editor_counter++;

                    //sort editor buffer
                    qsort(editor_buf, editor_counter, sizeof(edit_buffer), edit_buf_ascending_comp);

                }
                i+=3;
            }

            else if (strcmp("pb", TokensBuf[i])==0)
            {
                if (TokensBuf[i+2][0] == '\0') { 
                    printf("Error: " "pb" " requires 2 arguments.\n");
                }
                else {
                    edit_buffer temp;
                    unsigned char temp_edit_arr[32];
                    char temp_counter=0;
                    temp.position = strtol(TokensBuf[i+1], NULL, 16);

                    printf("Push back string: %s", TokensBuf[i+2]);

                    unsigned char *hex_tok = strtok(TokensBuf[i+2], ",");
                    while (hex_tok != NULL) {
                        if (strtol(hex_tok, NULL, 16) >= 0xff) {
                            printf("\nError: bad input, exceeded 0xff.\n");
                            break;
                        }
                        temp_edit_arr[temp_counter] = strtol(hex_tok, NULL, 16);

                       

                        temp_counter++;
                        hex_tok = strtok(NULL, ",");
                    }
                    memcpy(temp.hex_arr, temp_edit_arr, sizeof(temp_edit_arr));
                    temp.hex_len = temp_counter;

                    printf("(length: +%u), start pos: 0x%x\n", temp.hex_len, temp.position);

                    temp.mode = pushback;
                    
                    editor_buf[editor_counter] = temp;
                    editor_counter++;

                    //sort editor buffer
                    qsort(editor_buf, editor_counter, sizeof(edit_buffer), edit_buf_ascending_comp);

                }
                i+=3;
            }

            else if (strcmp("ap", TokensBuf[i])==0)
            {
                if (TokensBuf[i+1][0] == '\0') { 
                    printf("Error: " "ap" " requires an argument.\n");
                }
                else {
                    edit_buffer temp;
                    unsigned char temp_edit_arr[32];
                    char temp_counter=0;
                    temp.position = 0xffff;
                    /*
                    max value
                    since I've already declared it to be unsigned long long
                    can likely be demoted to save space
                    */

                    printf("Append string: %s", TokensBuf[i+1]);

                    unsigned char *hex_tok = strtok(TokensBuf[i+1], ",");
                    while (hex_tok != NULL) {
                        if (strtol(hex_tok, NULL, 16) >= 0xff) {
                            printf("\nError: bad input, exceeded 0xff.\n");
                            break;
                        }
                        temp_edit_arr[temp_counter] = strtol(hex_tok, NULL, 16);

                        temp_counter++;
                        hex_tok = strtok(NULL, ",");
                    }
                    memcpy(temp.hex_arr, temp_edit_arr, sizeof(temp_edit_arr));
                    temp.hex_len = temp_counter;

                    printf("(length: +%u)\n", temp.hex_len);

                    temp.mode = append;
                    
                    editor_buf[editor_counter] = temp;
                    editor_counter++;

                    //sort editor buffer
                    qsort(editor_buf, editor_counter, sizeof(edit_buffer), edit_buf_ascending_comp);

                }
                i+=2;
            }

            else if (strcmp("dl", TokensBuf[i])==0)
            {
                if (TokensBuf[i+2][0] == '\0') { 
                    printf("Error: " "dl" " requires 2 arguments.\n");
                }
                else {
                    
                    edit_buffer temp;
                    unsigned char temp_edit_arr[32];
                    // char temp_counter=0;
                    temp.position = strtol(TokensBuf[i+1], NULL, 16);
                    temp.hex_len = strtol(TokensBuf[i+2], NULL, 10);
                    memset(temp_edit_arr, 0, temp.hex_len);
                    memcpy(temp.hex_arr, temp_edit_arr, sizeof(temp_edit_arr));



                    printf("Delete: (length: +%u), start pos: 0x%x\n", temp.hex_len, temp.position);

                    temp.mode = delete;
                    
                    editor_buf[editor_counter] = temp;
                    editor_counter++;

                    //sort editor buffer
                    qsort(editor_buf, editor_counter, sizeof(edit_buffer), edit_buf_ascending_comp);

                }
                i+=3;
            }


            else if (strcmp("dp", TokensBuf[i])==0)
            {
                for (int k = 0; k < editor_counter; k++)
                {
                    printf("Edit buffer %d\n", k);
                    printf("Start pos: %x\n", editor_buf[k].position);
                    printf("String: ");
                    for (int j = 0; j < editor_buf[k].hex_len; j++)
                    {
                        printf("%x ",editor_buf[k].hex_arr[j]);
                    }
                    printf("\n");
                    printf("Length: +%u\n", editor_buf[k].hex_len);
                    switch (editor_buf[k].mode)
                    {
                    case replace:
                    printf("Mode: Replace\n");
                        break;
                    case pushback:
                    printf("Mode: Pushback\n");
                        break;
                    case delete:
                    printf("Mode: Delete\n");
                        break;
                    case append:
                    printf("Mode: Append\n");
                        break;
                    }
                    
                    printf("\n");
                }
                if (editor_counter==0)
                {
                    printf("No edit buffers created.\n");
                }

                i+=1;
            }

            else if (strcmp("db", TokensBuf[i])==0) // db for delete buffer
            {
                if (TokensBuf[i+1][0] == '\0') { 
                    printf("Error: " "db" " requires an argument.\n");
                }
                
                else
                {
                    int buf_index = strtol(TokensBuf[i+1], NULL, 10); // probably doesnt need to be int
                    if (buf_index < editor_counter) 
                    {
                    printf("Deleted buffer at index %d.\n", buf_index);
                    memmove(&editor_buf[buf_index],&editor_buf[buf_index+1], (editor_counter - buf_index - 1)*sizeof(edit_buffer));
                    editor_counter-=1;
                    }
                    else {
                        printf("index outside of possible values.\n");
                    }
                }
                i+=2;
            }

            else if (strcmp("exit", TokensBuf[i])==0 ||
                    strcmp("q", TokensBuf[i])==0)
            {
                printf("Exit detected. Program exiting");
                i+=1;
            }
            else if (strcmp("cls", TokensBuf[i])==0) 
            {
                system("cls");
                printf("\n");
                i+=1;
            }

            else if (strcmp("file", TokensBuf[i])==0)
            {
                printf("Loaded file(-i): %s\n", inFileName);
                i+=1;
            }

            else if (strcmp("caps", TokensBuf[i])==0)
            {
                if (CAPITAL_FLAG == 0)
                {
                    printf("Capital flag: On.\n");
                    CAPITAL_FLAG = 1;
                }
                else
                {
                    printf("Capital flag: Off.\n");
                    CAPITAL_FLAG = 0;
                }
                i+=1;
            }

            else if (strcmp("st", TokensBuf[i])==0)
            {
                if (STATS_FLAG == 0)
                {
                    printf("Statistics flag: On.\n");
                    STATS_FLAG = 1;
                }
                else
                {
                    printf("Statistics flag: Off.\n");
                    STATS_FLAG = 0;
                }
                i+=1;
            }

            else if (strcmp("pad", TokensBuf[i])==0)
            {
                if (TokensBuf[i+1][0] == '\0') 
                { 
                    printf("Error: " "pad" " requires an argument.\n");
                }
                else
                {
                    PaddingSize = atoi(TokensBuf[i+1]);
                    printf("New padding size: %d.\n", PaddingSize);
                }
                i+=2;
            }

            else if (strcmp("sil", TokensBuf[i])==0)
            {
                if (SILENT_FLAG == 0)
                {
                    printf("Silent flag: On.\n");
                    SILENT_FLAG = 1;
                }
                else
                {
                    printf("Silent flag: Off.\n");
                    SILENT_FLAG = 0;
                }
                i+=1;
            }

            else if (strcmp("s", TokensBuf[i])==0)
            {
                if (TokensBuf[i+2][0] == '\0') 
                { 
                    printf("Error: " "s" " requires 2 arguments.\n");
                }
                else
                {
                SECTION_START = strtol(TokensBuf[i+1], NULL, 16);
                SECTION_END = strtol(TokensBuf[i+2], NULL, 16);
            // bit manip magic lmao
                if (SECTION_START > SECTION_END) {
                    printf("Error: " "Start can not be larger than end.\n");    
                }
                SECTION_START = SECTION_START & ~0xf;
                SECTION_END = SECTION_END & ~0xf;
                
                SECTION_FLAG = 1;
                printf("Print section from 0x%x to 0x%x.\n", SECTION_START, SECTION_END);
                }
                i+=3;
            }

            else if (strcmp("l", TokensBuf[i])==0)
            {
                if (TokensBuf[i+1][0] == '\0') 
                { 
                    printf("Error: " "l" " requires an argument.\n");
                }
                else
                {
                SECTION_START = strtol(TokensBuf[i+1], NULL, 16);
                SECTION_END = strtol(TokensBuf[i+1], NULL, 16);
            // bit manip magic lmao
                // if (SECTION_START > SECTION_END) {
                //     printf("Error: " "Start can not be larger than end.\n");    
                // }
                SECTION_START = SECTION_START & ~0xf;
                SECTION_END = SECTION_END & ~0xf;
                
                SECTION_FLAG = 1;
                printf("Print section from 0x%x to 0x%x.\n", SECTION_START, SECTION_END);
                }
                i+=2;
            }
            

            else if (strcmp("scl", TokensBuf[i])==0)
            {
                printf("Reset section from %x to %x.\n", SECTION_START, SECTION_END);
                SECTION_START = 0;
                SECTION_END = 0;
                SECTION_FLAG = 0;
                i+=1;
            }
    
            else if (strcmp("m", TokensBuf[i])==0)
            {
                if (TokensBuf[i+1][0] == '\0') 
                { 
                    printf("Error: " "m" " requires an argument.\n");
                }
                else
                {
                    strcpy(MATCH_STRING, TokensBuf[i+1]);
                    
                    strcpy(RETURN_MATCH_STR, MATCH_STRING);
                    MATCH_FLAG = 1;
                    printf("Matching to string: %s.\n", MATCH_STRING);
                }
                i+=2;
            }
            else if (strcmp("mcl", TokensBuf[i])==0)
            {
                printf("Reset matching string: %s.\n", RETURN_MATCH_STR);
                strcpy(MATCH_STRING, "");
                MATCH_FLAG = 0;
                i+=1;
            }
            else if (strcmp("E", TokensBuf[i])==0)
            {
                if (TokensBuf[i+1][0] == '\0') 
                { 
                    printf("Error: " "E" " requires an argument.\n");
                }
                else
                {
                    strcpy(REGEX_STRING, TokensBuf[i+1]);
                    
                    // strcpy(RETURN_MATCH_STR, MATCH_STRING);
                    REGEX_FLAG = 1;
                    printf("Matching to regex pattern: %s.\n", REGEX_STRING);
                }
                i+=2;
            }// E cl maybe?
            else if (strcmp("Ecl", TokensBuf[i])==0)
            {
                
                printf("Reset regex pattern: %s.\n", REGEX_STRING);
                strcpy(REGEX_STRING, "");
                
                // strcpy(RETURN_MATCH_STR, MATCH_STRING);
                REGEX_FLAG = 0;
                
                
                i+=1;
            }

            // save for now 
            else if (strcmp("save", TokensBuf[i])==0)
            {
                // a file temporary file name to act as placeholder
                OUTPUT_FILE = fopen(TEMP_FILE_NAME, "ab");
                // printf("Output file(-o): %s.\n", outFileName);
                printf("Use \"savecl\" to clear the choice to save.\n");
                printf("use p to commit the save.\n");
                SAVE_FLAG = 1;


                i+=1;
            }

            else if (strcmp("savecl", TokensBuf[i])==0)
            {
                
                fclose(OUTPUT_FILE);
                printf("Disabled option to save.\n");
                SAVE_FLAG = 0;

                i+=1;
            }

            else if (strcmp("o", TokensBuf[i])==0)
            {
                if (TokensBuf[i+1][0] == '\0') 
                { 
                    printf("Error: " "o" " requires an argument.\n");
                }
                else
                {   
                    
                    strcpy(outFileName, TokensBuf[i+1]);
                    

                    if (strcmp(inFileName, outFileName)==0) 
                    {
                    printf("Input and output files can not be the same.\n");
                    strcpy(outFileName, "");
                    OUTPUT_FLAG = 0;
                    }
                    else {
                    OUTPUT_FILE = fopen(outFileName, "ab");
                    printf("Output file(-o): %s.\n", outFileName);
                    printf("Use \"ocl\" to clear the output file choice.\n");
                    OUTPUT_FLAG = 1;
                    }
                }
                i+=2;
            }
            else if (strcmp("ocl", TokensBuf[i])==0)
            {
                
                printf("Reset output file: %s.\n", outFileName);
                strcpy(outFileName, "");
                fclose(OUTPUT_FILE);
                // strcpy(RETURN_MATCH_STR, MATCH_STRING);
                OUTPUT_FLAG= 0;
                
                
                i+=1;
            }
            
            else if (strcmp("help", TokensBuf[i])==0)
            {
                print_help();
                i+=1;
            }
            

            else if (strcmp("p", TokensBuf[i])==0)
            {
                signal(SIGINT, interrput_handler); 
                int Buf_forChars16[16]; // chances are this will be malloc

                int Hex_Counter = 16;
                unsigned long long int LineNum = 0; 
                unsigned char ConversionBuf[32];
                unsigned char ConverBufCounter = 0;
                unsigned char ComparisonBuf[32];

                unsigned char CompareCounter = 0;
                long long int matchesPosition[128]; 
                unsigned char PositionCounter = 0;
                unsigned char EqualCounter = 0;
                
                unsigned char temp_editor_count = 0;

                int next_ch = 0;
                

                // match string is going to be decimated
                // so a backup copy is needed
                strcpy(MATCH_STRING, RETURN_MATCH_STR);

                // edit_buffer temp = {0};
                // if (editor_counter != 0)
                // {
                //     temp = editor_buf[0];
                // }
                regex_t regex;
                regmatch_t matches[REGEX_MATCHES_PREALLOC];
                unsigned char matches_index = 0;
                regmatch_t match;
                char regex_checker[32] = ""; 
                unsigned char reg_check_index = 0;

                unsigned char regex_offset = 0;

                if (REGEX_FLAG==1)
                {
                    if (regcomp(&regex, REGEX_STRING, REG_EXTENDED)!=0)
                    {
                        printf("Error: Regcomp failed.\n");
                        return 1;

                    }
                }

                if (PaddingSize > 16 || PaddingSize == 0 || PaddingSize == 1) 
                {
                    printf("Padding size is invalid or too large: %d.", PaddingSize);
                    return 1;
                }
                char *_FormatIndex = "%0*x  ";
                char *_FormatHexChar = "%.2x ";

                if (CAPITAL_FLAG == 1) {
                    _FormatIndex = "%0*X  ";
                    _FormatHexChar = "%.2X ";
                }

                if (MATCH_FLAG == 1) // match will use commas here
                {
                    char *Token = strtok(MATCH_STRING, ",");
                    // So its seem there's some conflict on whether to use " " or ",".
                    while (Token != NULL) {

                        ConversionBuf[ConverBufCounter] = strtol(Token, NULL, 16);

                        ConverBufCounter++;
                        Token = strtok(NULL, ",");
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

                // main printing logic, had to push back a bit
                
                while (( (ch = fgetc(INPUT_FILE)) != EOF && breakout_flag == 1 ) || APPEND_FLAG == 1)
        {
           

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
            
            // lookahead for EOF, the moment next_ch becomes EOF, the conditional locks.

            if (next_ch != EOF)
            {
                next_ch = fgetc(INPUT_FILE);
                ungetc(next_ch, INPUT_FILE);
            }
            
            // adding editor_counter != 0 worked...
            // the code is still really poor to look at
            if (next_ch == EOF && editor_buf[editor_increment].mode == append && editor_counter != 0)
            {
                // printf("ACCESS\n");
                APPEND_FLAG = 1;
                temp_max_len = editor_buf[editor_increment].hex_len;
                DELETE_FLAG = 0;
                PUSHBACK_FLAG = 0;
                REPLACE_FLAG = 0;
                temp_increment = 0;

                // editor_increment++;
            }
            
            if (ch == EOF && APPEND_FLAG == 1 && editor_counter != 0)
            {
                // printf("ACCESS\n");
                if (temp_increment != temp_max_len)
                {
                    ch = editor_buf[editor_increment-1].hex_arr[temp_increment];
                    temp_increment++;
                }

                if (temp_increment == temp_max_len)
                {
                    // editor_increment++;
                    APPEND_FLAG = 0;
                    temp_max_len = 0;
                    temp_increment = 0;
                    editor_increment++;
                }
            }

            if (editor_buf[editor_increment].position == (LineNum-16)+Hex_Counter && editor_counter != 0)
            {
                

                if (editor_buf[editor_increment].mode == replace)
                {
                    REPLACE_FLAG = 1;
                    temp_max_len = editor_buf[editor_increment].hex_len;
                    DELETE_FLAG = 0;
                    PUSHBACK_FLAG = 0;
                    APPEND_FLAG = 0;
                    temp_increment = 0;
                }

                else if (editor_buf[editor_increment].mode == delete)
                {
                    DELETE_FLAG = 1;
                    temp_max_len = editor_buf[editor_increment].hex_len;
                    REPLACE_FLAG = 0;
                    PUSHBACK_FLAG = 0;
                    APPEND_FLAG = 0;
                    temp_increment = 0;
                }
                else if (editor_buf[editor_increment].mode == pushback)
                {
                    PUSHBACK_FLAG = 1;
                    temp_max_len = editor_buf[editor_increment].hex_len;
                    DELETE_FLAG = 0;
                    REPLACE_FLAG = 0;
                    APPEND_FLAG = 0;
                    temp_increment = 0;

                }

                editor_increment++;
            }

            if (REPLACE_FLAG == 1)
            {
                if (temp_increment != temp_max_len) 
                {
                
                ch = editor_buf[editor_increment - 1].hex_arr[temp_increment];
                temp_increment++;
                }
                else
                {
                    // editor_increment++;
                    REPLACE_FLAG = 0;
                    temp_max_len = 0;
                    temp_increment = 0;
                }
            }

            if (DELETE_FLAG ==1)
            {
            for (int i = 0; i < temp_max_len; i++)
                {
                    ch = fgetc(INPUT_FILE);
                    // printf("%c\n", ch);
                }
                DELETE_FLAG = 0;
                temp_max_len = 0;
                temp_increment = 0;
            }


            if (PUSHBACK_FLAG == 1)
            {
                if (temp_increment != temp_max_len) 
                {
                ch = ungetc(ch, INPUT_FILE);
                ch = editor_buf[editor_increment - 1].hex_arr[temp_increment];
                temp_increment++;
                }
                else
                {
                    // editor_increment++;
                    PUSHBACK_FLAG = 0;
                    temp_max_len = 0;
                    temp_increment = 0;
                }
            }

            // next_ch = fgetc(INPUT_FILE);

            // if (next_ch == EOF) {
            //     if (editor_buf[editor_increment].mode == append)
            //     {
            //         for (int i = 0; i < editor_buf[editor_increment].hex_len;i++)
            //         {
            //             ungetc(editor_buf[editor_increment].hex_arr[i], INPUT_FILE);
            //         }
            //         editor_increment++;
            //     }



            // }

            // ungetc(next_ch, INPUT_FILE);



            // section print marker switch
            
            // SILENT_FLAG != 1 && SECTION_FLAG != 1
            
            
            if ((!SILENT_FLAG && !SECTION_FLAG) || (SECTION_FLAG && SECTION_PRINT_MARKER)) {
                printf(_FormatHexChar, ch);
            }
            
            if (OUTPUT_FLAG == 1 || SAVE_FLAG == 1) {
                // fprintf(OUTPUT_FILE,"%c", ch);
                fputc(ch, OUTPUT_FILE);
            }
            if (MATCH_FLAG == 1) 
            {
                if (CompareCounter != ConverBufCounter) 
                {
                    ComparisonBuf[CompareCounter] = ch;
                    CompareCounter++;
                }
                else 
                {
                    memmove(&ComparisonBuf[0],&ComparisonBuf[1],(CompareCounter-1) * sizeof(unsigned char));
                    ComparisonBuf[CompareCounter-1] = ch;
                }   
                for (int i=0; i < ConverBufCounter;i++) 
                {           
                    if (ComparisonBuf[i] != ConversionBuf[i]) 
                    {
                        EqualCounter = 0;
                        break;
                    }
                    else {
                        EqualCounter++;
                    }
                }
                if (EqualCounter == ConverBufCounter) 
                {
                    matchesPosition[PositionCounter] = (LineNum - 16) + Hex_Counter - ConverBufCounter + 1;
                    PositionCounter++;
                    EqualCounter = 0;
                }
            }
            if (STATS_FLAG == 1) {
                byteStats[ch]++;
            }
            if (REGEX_FLAG == 1)
            {
                regex_checker[reg_check_index] = ch;
                reg_check_index++;

                if (reg_check_index==32)
                {
                    while (regexec(&regex, regex_checker + regex_offset , 1, &match, 0) == 0)
                    {
                        match.rm_so += regex_offset;
                        match.rm_eo += regex_offset;

                        regex_offset = match.rm_eo;

                        // match.rm_eo -= 1;

                        if (match.rm_so >= 0x10)
                        {
                            match.rm_so += LineNum - 16;
                            match.rm_eo += LineNum - 16;
                        }
                        else
                        {
                            match.rm_so += LineNum - 32;
                            match.rm_eo += LineNum - 32;
                        }

                        if ((matches_index - 1) != -1)
                        {
                            if (match.rm_so == matches[matches_index-1].rm_so - 0x10)
                            {       
                                matches_index--;
                            }
                        }

                        matches[matches_index] = match;                    

                        if (match.rm_so == match.rm_eo)
                        {
                            regex_offset++;
                        }
                        matches_index++;
                        if (matches_index == REGEX_MATCHES_PREALLOC)
                        {
                            printf("\n");
                            printf("Error: Regex matches exceeded buffer.\n");
                            printf("\n");
                            return 1;
                        }
                    }
                    memmove(&regex_checker[0],&regex_checker[16],(32-16) * sizeof(char));
                    reg_check_index = 16;

                    regex_offset = 0;
                }
            }
            

            Buf_forChars16[Hex_Counter] = ch;
            Hex_Counter++;

            // append needs to happen right before the next check for eof?
            

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

        if (REGEX_FLAG==1 && reg_check_index!= 32)
        {
            while (regexec(&regex, regex_checker + regex_offset , 1, &match, 0) == 0)
            {
                match.rm_so += regex_offset;
                match.rm_eo += regex_offset;

                // I had my suspicions
                regex_offset = match.rm_eo;

                if (match.rm_so >= 0x10)
                    {
                        match.rm_so += LineNum - 16;
                        match.rm_eo += LineNum - 16;
                    }
                    else
                    {
                        match.rm_so += LineNum - 32;
                        match.rm_eo += LineNum - 32;
                    }

                    if ((matches_index - 1) != -1)
                    {
                        if (match.rm_so == matches[matches_index-1].rm_so - 0x10)
                        {       
                            matches_index--;
                        }
                        if (match.rm_so == matches[matches_index-1].rm_so)
                        {       
                            matches_index--;
                        }
                    }

                    matches[matches_index] = match;

                    if (match.rm_so == match.rm_eo)
                    {
                        regex_offset++;
                    }
                matches[matches_index] = match;
                
                if (match.rm_so == match.rm_eo)
                {
                    regex_offset++;
                }
                matches_index++;
                if (matches_index == REGEX_MATCHES_PREALLOC)
                {
                    printf("\n");
                    printf("Error: Regex matches exceeded buffer.\n");
                    printf("\n");
                    return 1;
                }
            }
        }

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
        printf("Total length: %llu line(s) (%llu B).\n", (SECTION_END - SECTION_START)/16 + 1 ,16 *((SECTION_END - SECTION_START)/16 + 1));
    } 

    printf("End of file reached. Total file size: %llu B (0x%llx).\n", LineNum - (16 - Hex_Counter), LineNum - (16 - Hex_Counter));
    
    if (LineNum - (16 - Hex_Counter) == 0) {
        printf("Input was likely incorrect: %s\n", inFileName);
    }

    if (REFERENCE_FLAG == 1) {
        PRINT_REFERENCE();
    }

    // if (STRING_FLAG==1 && TEXT_FLAG!=1) printf("Detected -str: String flag -str has to be used with -txt.\n");


    if (REGEX_FLAG==1)
    {
        printf("\n");
        printf("Matches to regex pattern \"%s\": \n", REGEX_STRING);
        for (int i = 0; i < matches_index; i++)
        {
            printf("%0*d  ", MatchIndexPadding ,i+1);
            printf("%0*x - %0*x\n",PaddingSize, matches[i].rm_so, PaddingSize, matches[i].rm_eo - 1);
            // if ((i+1) % 4 == 0) {
            //     printf("\n");
            // }
            
        }
        if (matches_index == 0) {
            printf("No regex matches founded.\n");
        }
        printf("\n" "Total regex match count: %d.\n", matches_index);
        
    }

    if (MATCH_FLAG == 1) {
        printf("\n");
        // printf("Displaying start positions.\n");
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
        if (OUTPUT_FLAG == 1) {
            printf("Stream to output file has closed.\n");
            fclose(OUTPUT_FILE);
            OUTPUT_FLAG = 0;
        }

        if (SAVE_FLAG == 1)
        {
            /*
            close the file, 
            then remove and rename, 
            then re-open the file
            */

            printf("File has been saved.\n");
            fclose(OUTPUT_FILE);
            fclose(INPUT_FILE); 

            SAVE_FLAG = 0;

            remove(inFileName);
            rename(TEMP_FILE_NAME, inFileName);

            INPUT_FILE = fopen(inFileName, "rb");
        }

            rewind(INPUT_FILE);
            breakout_flag = 1;
            editor_increment = 0;
            i+=1;
            }

            else
            {
                printf("Invalid input. Type \"help\" for help.\n");
                break;
            }
        }

            
        

    }


    fclose(INPUT_FILE);
    return 0;
}