// This is not for compilation
// no include directives should get in

void PRINT_HELP() {
printf("hexcat: A hex viewer.\n");
printf("\n");
printf("Usage: hexcat [flags] <args>...\n");
printf("\n");
printf("-i <arg>                    : (Optional) File input.\n");
printf("-o <arg>                    : File output.\n");
printf("-p <arg>                    : Specify index padding. Also is padding for match positions.\n"
       "                              Default is 8.\n");
printf("-caps                       : Capitalizes hex characters.\n");
printf("\n");
printf("-st --stats                 : At the end of cat-ting, returns a table with the\n"
       "                              the frequency of each byte.\n");

printf("\n");

printf("flags that support --stats:\n");
printf("    -st-p  <arg_num>        : Specify the stats frequency padding.\n");
printf("                              Default is 4.\n");
printf("    -st-sp <arg_num>        : Specify the whitespace padding between columns.\n");
printf("                              Default is 4.\n");
printf("    -st-c  <arg_num>        : Specify the number of columns.\n");
printf("                              Default is 8.\n");
printf("    -st-v                   : Stats verbose. Will print hexs that have 0 occurence.\n");
printf("                              Default hides this.\n");
// printf("    -fr --freq: Display stats table from highest to lowest frequency order.\n");
printf("\n");
printf("-m --match <num1 num2 ...>  : Return the starting position of sequences that matches "
"the sequence given.\n");
printf("                              String should be under quotes and seperated by spaces.\n");

printf("flags that support --match:\n");
printf("    -m-p <arg_num>          : Specify match index padding.\n");
printf("                              Default is 2.\n");
printf("\n");
printf("-E <regex_str>              : Returns the starting and ending position of matches using REGEX.\n");
printf("                              The <regex_str> should be under quotes. Syntax is extended regex\n");
printf("                              (ERE), which also is the POSIX standard and the standard for C\n");
printf("                              <regex.h> header.\n");
printf("\n");

printf("-s <line_num1> <line_num2>  : Print section from <line_num1> to <line_num2>.\n");
printf("                              Breaks out of program when <line_num2> is reached.\n");
printf("                              Input will rounded down to the smallest line number\n");
printf("                              example: 3d4 will go to 3d0.\n");

printf("flags derived from -sec:\n");
printf("    -l --line <line_num>    : Print line <line_num>.\n");
printf("    -s1       <line_num>    : Print section 1 line above and 1 line below from <line_num>.\n");

printf("\n");
printf("-txt                        : Expand the text column as well as print escape characters and\n");
printf("                              starting address column.\n");
printf("flags that support -txt:\n");
printf("-str                        : When use with -txt, restrict printing to only alphanumeric\n");
printf("                              ascii characters.\n");



printf("\n");
printf("-P --pure                   : Prints pure hex bytes, no formatting. Is affected by -s flag.\n");
printf("                              Can be used as stdout.\n");
printf("flags that support -P:\n");
printf("Note: don't support -s:\n");
printf("    -B --binary             : Binary flag, convert all bytes to binary.\n");
printf("    -M --multi <num> <0/1>  : Merges to create multi-byte numbers. <num> specifies\n");
printf("                              how many bytes to merge. <0/1> specifies endianness.\n");
printf("                              0 for little-endian (default), 1 for big-endian.\n");
printf("-D --decimal                : Decimal flag, convert all bytes to decimal. Also works on -P.\n");

printf("\n");
printf("--chunks=<num>              : Specify how many chunks to divide the hex into. Default is 2.\n");
printf("                            : Possible values are 1, 2, 4, 8, 16.\n");
printf("\n");
printf("hexcat cnv <args...>        : Converts a text string into hex based on ascii.\n");

printf("--color                     : Format bytes with 8-bit colors based on the value of the bytes.\n");
printf("-sil --silent               : Silent mode. Do not print hexdump.\n");
printf("-ref                        : Displays useful references for control characters.\n");
printf("-h --help                   : Show this list.\n");

}

// int is_escape_char(char ch) {
//     switch (ch) {
//         case '\n':
//         case '\r':
//         case '\t':
//         case '\v':
//         case '\b':
//         case '\f':
//         case '\a':
//         // case '\\':
//         // case '\'':
//         // case '\"':
//         // case '\?': 
//         case '\0':
//             return 1; // true
//         default:
//             return 0; // false
//     }
// }

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
