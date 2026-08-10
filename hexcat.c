#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <regex.h>

#include "useful_macros.c"
#include "other_functions.c"

#include "declarations.c" // includes most of the variables' name
// Go here to define new ones

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
((byte) & 0x80 ? '1' : '0'), \
((byte) & 0x40 ? '1' : '0'), \
((byte) & 0x20 ? '1' : '0'), \
((byte) & 0x10 ? '1' : '0'), \
((byte) & 0x08 ? '1' : '0'), \
((byte) & 0x04 ? '1' : '0'), \
((byte) & 0x02 ? '1' : '0'), \
((byte) & 0x01 ? '1' : '0')
// needs to be move to decl. later

#define REGEX_MATCHES_PREALLOC 256

int main(int argc, char *argv[]) {
    
    if (argc == 1) {
        printf("Unknown command or missing arguments.\n");
        printf("Type -h or --help for usage help.\n");
        return 1;
    
    }
    else {
        SubCommand = argv[1];
    }
    int i = 1; // No subcommands for now. Yes subcommands
    
    // if (strcmp(SubCommand, "diff") == 0) {
    //     printf("Diff sub is here.\n");
    //     // DIFF_SUB_FLAG = 1;
    //     int i = 2;
    //     return 0; // for now, 
    // }

    if (strcmp(SubCommand, "cnv") == 0) {
        if (argc != 3) {
            printf("Convert \"cnv\" requires a string.");
            return 1;
        }
        printf("Ascii to hex conversion: %s\n", argv[2]);
        for (int i =0; i < strlen(argv[2]); i++) {
            printf("%.2x ", argv[2][i]);    
        }
        printf("\n");
        return 0; // for now
    }

    // else if (strcmp(SubCommand, "w") == 0) {
    //     printf("Write sub is here.\n");
    //     // WRITE_SUB_FLAG = 1;
    //     int i = 2;
    //     return 0; // for now
    // }

    
    // ofc if subcommands were passed, this functions should continue over here

    while (i < argc) {
        // standard
        if (strcmp(argv[i], "-i") == 0) {
            CLI_1ARGS(i, "-i", inFileName, ); // note the final empty arg is necessary
            INPUT_FLAG = 1;
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
        // else if (strcmp(argv[i], "--freq") == 0) {
        //     CLI_0ARGS(i, "--freq", STATS_FREQ_FLAG);
        // }
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
        else if (strcmp(argv[i], "-s") == 0) {
            if (i + 2 >= argc) { 
                printf("Error: " "-s" " requires 2 arguments.\n"); 
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
        else if (strcmp(argv[i], "-s1") == 0) {
            if (i + 1 >= argc) { 
                CLI_1ARGSERR("-s1");
                return 1; } 
            SECTION_START = strtol(argv[i+1], NULL, 16);
            SECTION_END = strtol(argv[i+1], NULL, 16); 
            SECTION_START = (SECTION_START & ~0xf) - 16;
            SECTION_END = (SECTION_END & ~0xf) + 16;
            SECTION_FLAG = 1;
            i+=2;
        }
        else if (strcmp(argv[i], "-txt") == 0){
            CLI_0ARGS(i,"-txt", TEXT_FLAG);
        }
        else if (strcmp(argv[i], "-str") ==0) {
            CLI_0ARGS(i,"-str", STRING_FLAG);
        }
        else if (strcmp(argv[i], "-E") == 0)
        {
            CLI_1ARGS(i, "-E", REGEX_STRING, );
            REGEX_FLAG = 1;
        }

        else if (strcmp(argv[i], "--color") == 0){
            CLI_0ARGS(i,"--color", COLOR_FLAG);
        }

        else if (strcmp(argv[i], "--chunks=1") == 0){
            chunk_divide = 1;
            i+=1;
        }
        
        else if (strcmp(argv[i], "--chunks=2") == 0){
            chunk_divide = 2;
            i+=1;
        }

        else if (strcmp(argv[i], "--chunks=4") == 0){
            chunk_divide = 4;
            i+=1;
        }

        else if (strcmp(argv[i], "--chunks=8") == 0){
            chunk_divide = 8;
            i+=1;
        }

        else if (strcmp(argv[i], "--chunks=16") == 0){
            chunk_divide = 16;
            i+=1;
        }

        else if (strcmp(argv[i], "-P") == 0 || strcmp(argv[i], "--pure") == 0)
        {
            CLI_0ARGS(i, "-P", PURE_FLAG);
        }

        else if (strcmp(argv[i], "-D") == 0 || strcmp(argv[i], "--decimal") == 0)
        {
            CLI_0ARGS(i, "-D", DECIMAL_FLAG);
        }

        else if (strcmp(argv[i], "-B") == 0 || strcmp(argv[i], "--binary") == 0)
        {
            CLI_0ARGS(i, "-B", BINARY_FLAG);
        }
        else if (strcmp(argv[i], "-M") == 0 || strcmp(argv[i], "--multi") == 0)

        {
            CLI_2ARGS(i, "-M", MultiLength, Endianness, atoi);
        }

        // ending
        else {
            if (INPUT_FLAG == 0)
            {
                INPUT_FLAG = 1;
                inFileName = argv[i];
                i+=1;
            }
            else
            {
            printf("Unknown command or missing arguments: %s.\n", argv[i]);
            printf("Type -h or --help for usage help.\n");
            return 1;
            }
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

    if (DECIMAL_FLAG == 1)
    {
        _FormatHexChar = "%.3d ";

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

    FILE *INPUT_FILE  = fopen(inFileName, "rb");
    FILE *OUTPUT_FILE;
    if (OUTPUT_FLAG == 1) {
        OUTPUT_FILE = fopen(outFileName, "ab");
    }


    if (PURE_FLAG == 1 && MultiLength != 1)
    {

        int MultiByte_count = 0;
        while ((ch = fgetc(INPUT_FILE)) != EOF)
        {
        // push back onto the start
        fseek(INPUT_FILE, -1, SEEK_CUR);
        long current_position = ftell(INPUT_FILE);
        // long ending_position = current_position + MultiLength - 1;
        
        // safety measures can be handled later
        fseek(INPUT_FILE, MultiLength - 1, SEEK_CUR);

        int ending_ch = fgetc(INPUT_FILE);
        fseek(INPUT_FILE, -1, SEEK_CUR);
        
        if (ending_ch == EOF)  
        {
            fseek(INPUT_FILE, current_position, SEEK_SET);           
            
            while ((ch = fgetc(INPUT_FILE)) != EOF)
            {
            if (COLOR_FLAG == 1) printf("\033[38;5;%dm", ch);

            if (DECIMAL_FLAG == 1) printf("%.3d ", ch);
            else if (BINARY_FLAG == 1) printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(ch));
            else printf(_FormatHexChar, ch);

            if (COLOR_FLAG == 1) printf("\033[0m");
            }
            return 0;

        }
        
        char CheckCondition = 0;
        
        if (Endianness == 0) CheckCondition = (ch < ending_ch);
        else CheckCondition = (ch > ending_ch);

        if (CheckCondition == 1)
        {
        fseek(INPUT_FILE, -(MultiLength - 1), SEEK_CUR);
        for (int i = 0; i < MultiLength; i++)
            {
            ch = fgetc(INPUT_FILE);
            if (COLOR_FLAG == 1) printf("\033[38;5;%dm", ch);

            if (DECIMAL_FLAG == 1) printf("%.3d", ch);
            else if (BINARY_FLAG == 1) printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(ch));
            else printf("%.2x", ch);

            if (COLOR_FLAG == 1) printf("\033[0m");
            }
        }
        else
        {
        for (int i = 0; i < MultiLength; i++)
            {
            ending_ch = fgetc(INPUT_FILE);
            if (COLOR_FLAG == 1) printf("\033[38;5;%dm", ch);

            if (DECIMAL_FLAG == 1) printf("%.3d", ending_ch);
            else if (BINARY_FLAG == 1) printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(ending_ch));
            else printf("%.2x", ending_ch);

            if (COLOR_FLAG == 1) printf("\033[0m");
            
            if (fseek(INPUT_FILE, -2, SEEK_CUR) == -1)
                {
                    fseek(INPUT_FILE, 0, SEEK_SET);
                }
            }
        }

        printf(" ");
        MultiByte_count++;
        fseek(INPUT_FILE, MultiLength * MultiByte_count, SEEK_SET);
        }
        // how was there no return until now?
        fclose(INPUT_FILE);
        return 0;
    }

    if (PURE_FLAG == 1)
    {
        while ((ch = fgetc(INPUT_FILE)) != EOF) {
        if (Hex_Counter == 16) {
            Hex_Counter = 0;
            LineNum+=16;

            if ((LineNum-16) == SECTION_START && SECTION_FLAG == 1) {
                SECTION_PRINT_MARKER = 1;
            }
            if ((LineNum-16) == (SECTION_END+16) && SECTION_FLAG == 1) {
                SECTION_PRINT_MARKER = 0;
            }
        }

        if ((!SILENT_FLAG && !SECTION_FLAG) || (SECTION_FLAG && SECTION_PRINT_MARKER)) {
            if (COLOR_FLAG == 1) printf("\033[38;5;%dm", ch);

            if (DECIMAL_FLAG == 1) printf("%.3d ", ch);
            else if (BINARY_FLAG == 1) printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY(ch));
            else printf(_FormatHexChar, ch);

            if (COLOR_FLAG == 1) printf("\033[0m");
        }
        Hex_Counter++;
        
        }
        fclose(INPUT_FILE);
        return 0;
    }

    printf("\n");
    printf("%*s", PaddingSize + 2,"");
    for (int i = 0; i < 16; i++) {
        printf(_FormatHexChar, i);
        if ((i+1) % (16/chunk_divide) == 0 && i+1 != 16) printf(" ");
    }
    for (int i = 0; i < 16; i++) {
        printf("%x", i);   
    }
    printf("\n");

    // Entire conditional only gets access with text flag
    if (TEXT_FLAG==1) 
    {
        unsigned int textLinecount = 0;
        printf("\n");
        printf(_FormatIndex, PaddingSize, 0);
    while ((ch = fgetc(INPUT_FILE)) != EOF) {
        if (Hex_Counter == 16) {
            Hex_Counter = 0;
            LineNum+=16;

            if ((LineNum-16) == SECTION_START && SECTION_FLAG == 1) {
                SECTION_PRINT_MARKER = 1;
            }
            if ((LineNum-16) == (SECTION_END+16) && SECTION_FLAG == 1) {
                SECTION_PRINT_MARKER = 0;
            }
        }
        if ((!SILENT_FLAG && !SECTION_FLAG) || (SECTION_FLAG && SECTION_PRINT_MARKER)) {
            if (STRING_FLAG!=1) {

                if (ch == 7)  printf("."); // bel char
                else printf("%c", ch);

            } 
            else {
                if (is_alphanum(ch)==1 || ch == '\n') {
                    printf("%c", ch);
                }
            }

            if (ch == '\n') {
                printf(_FormatIndex, PaddingSize, LineNum+Hex_Counter);
                textLinecount++;
            }
        }
        Hex_Counter++;
        
    }
    printf("\n");
    printf("\n");
    printf("This was under text mode.\n");
    if (STRING_FLAG==1) printf("This was under string filtering.\n");
    printf("Note: BEL char 07 replaced with a dot.\n");
    printf("End of text section reached. Total text line(s): %u\n", textLinecount);
    if (SECTION_FLAG == 1) {
        printf("\n");
        printf("End of section reached. From %0*x to %0*x. ",PaddingSize,SECTION_START,PaddingSize,SECTION_END);
        printf("Total length: %llu line(s).\n", (SECTION_END - SECTION_START)/16 + 1);
    }
    printf("End of file reached. Total file size: %llu B (0x%llx).\n", LineNum - (16 - Hex_Counter), LineNum - (16 - Hex_Counter));
    fclose(INPUT_FILE);
    return 0;
    }
    

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
            fclose(INPUT_FILE);
            return 1;

        }
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
                // printf()
                // this needs to be check further
                printf("\n");
                printf("End of section reached. From %0*x to %0*x. ",PaddingSize,SECTION_START,PaddingSize,SECTION_END);
                printf("Total length: %llu line(s).\n", (SECTION_END - SECTION_START)/16 + 1);
                printf("Total section size: %d B.\n", SECTION_END - SECTION_START + 16);
                printf("\n");
                printf("Note: Section flags stop reading when the end of the section is reached.\n");
                printf("Flags that require file's completion will fail.\n");
                printf("\n");
                if (REGEX_FLAG == 1) regfree(&regex);
                fclose(INPUT_FILE);
                return 0;
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
            if ((Hex_Counter) % (16/chunk_divide) == 0 && Hex_Counter != 0) printf(" ");
            if (COLOR_FLAG == 1) printf("\033[38;5;%dm", ch);

            printf(_FormatHexChar, ch);

            if (COLOR_FLAG == 1) printf("\033[0m");
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
        if (REGEX_FLAG == 1)
        {
            regex_checker[reg_check_index] = ch;
            reg_check_index++;

            if (reg_check_index==32)
            {
                // Conditional jump or move depends on uninitialised value(s)

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
                        regfree(&regex);
                        fclose(INPUT_FILE);
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

        if (Hex_Counter == 16) {
            // printf(" "); // separator, is actually 2 spaces cuz of "%.2x " you know.
            //All of these was replaced from SILENT_FLAG == 1
            if ((!SILENT_FLAG && !SECTION_FLAG) || (SECTION_FLAG && SECTION_PRINT_MARKER)) {
                for (int i = 0; i < 16; i++) {
                    if (is_escape_char(*(Buf_forChars16+i)) == 1) {
                        if (COLOR_FLAG == 1) printf("\033[38;5;%dm", *(Buf_forChars16+i));
                        
                        printf(".");
                        
                        if (COLOR_FLAG == 1) printf("\033[0m");
                    }
                    else {
                        if (COLOR_FLAG == 1) printf("\033[38;5;%dm", *(Buf_forChars16+i));
                        
                        printf("%c", *(Buf_forChars16+i));
                        
                        if (COLOR_FLAG == 1) printf("\033[0m");

                    }
                }
            } 
        }     
    }

    // this part is for dealing with the residue characters
    // that weren't printed

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
                    match.rm_so += LineNum - 16 - 16;
                    match.rm_eo += LineNum - 16 - 16;
                }
                else
                {
                    match.rm_so += LineNum - 32 - 16;
                    match.rm_eo += LineNum - 32 - 16;
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
                regfree(&regex);
                fclose(INPUT_FILE);
                return 1;
            }
        }
    }

    // this part is for dealing with the residue characters
    // that weren't printed


    if ((!SILENT_FLAG && !SECTION_FLAG) || (SECTION_FLAG && SECTION_PRINT_MARKER)) {
        for (int i = 0; i < 16 - Hex_Counter; i++) {
            if ((Hex_Counter) % (16/chunk_divide) == 0 && Hex_Counter != 0) printf(" ");
            printf("   ");
        }
        for (int i = 0; i < Hex_Counter; i++) {
            if (is_escape_char(*(Buf_forChars16+i)) == 1) {
                if (COLOR_FLAG == 1) printf("\033[38;5;%dm", *(Buf_forChars16+i));
                
                printf(".");
                
                if (COLOR_FLAG == 1) printf("\033[0m");
            }
            else {
                if (COLOR_FLAG == 1) printf("\033[38;5;%dm", *(Buf_forChars16+i));
                
                printf("%c", *(Buf_forChars16+i));
                
                if (COLOR_FLAG == 1) printf("\033[0m");
            }
        }
    }


    printf("\n");
    // if (SECTION_FLAG == 1) {
    //     printf("\n");
    //     printf("End of section reached. From %0*x to %0*x. ",PaddingSize,SECTION_START,PaddingSize,SECTION_END);
    //     printf("Total length: %llu line(s).\n", (SECTION_END - SECTION_START)/16 + 1);
    // } 

    printf("End of file reached. Total file size: %llu B (0x%llx).\n", LineNum - (16 - Hex_Counter), LineNum - (16 - Hex_Counter));
    
    if (LineNum - (16 - Hex_Counter) == 0) {
        printf("Input was likely incorrect: %s\n", inFileName);
    }

    if (REFERENCE_FLAG == 1) {
        PRINT_REFERENCE();
    }

    if (STRING_FLAG==1 && TEXT_FLAG!=1) printf("Detected -str: String flag -str has to be used with -txt.\n");

    if (REGEX_FLAG==1)
    {
        printf("\n");
        printf("Matches to regex pattern \"%s\": \n", REGEX_STRING);
        for (int i = 0; i < matches_index; i++)
        {
            printf("%0*d  ", MatchIndexPadding ,i+1);
            printf("%0*x - %0*x    ",PaddingSize, matches[i].rm_so, PaddingSize, matches[i].rm_eo - 1);
            if ((i+1) % 4 == 0) {
                printf("\n");
            }
            
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
    // drop STATS_FREQ_FLAG == 1
    // if (STATS_FLAG == 0) {
    //     printf("Frequency flag --freq has to be used with --stats.\n");
    //     return 1;}

    if (STATS_PADDING > 16 || STATS_PADDING == 0) {
        printf("Stats padding size is invalid or too large: %d.", STATS_PADDING);
        regfree(&regex);
        fclose(INPUT_FILE);
        return 1;}

    if (STATS_SPACEPADDING > 16 || STATS_SPACEPADDING == 0) {
        printf("Stats space padding size is invalid or too large: %d.", STATS_SPACEPADDING);
        regfree(&regex);
        fclose(INPUT_FILE);
        return 1;}

    if (COLUMN_NUMBER > 16 || COLUMN_NUMBER == 0) {
        printf("Column number is invalid or too large: %d.", COLUMN_NUMBER);
        regfree(&regex);
        fclose(INPUT_FILE);
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

    if (REGEX_FLAG == 1) {
        regfree(&regex);
    }

    return 0;
}
