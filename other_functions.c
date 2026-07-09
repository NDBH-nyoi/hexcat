// This is not for compilation
// no include directives should get in

void PRINT_HELP() {
    printf("Usage: hexcat.exe [flags] <args>...\n");
    printf("\n");
    printf("-i <arg>: File input.\n");
    printf("-o <arg>: File output.\n");
    printf("-p <arg>: Specify index padding. Also is padding for match positions. "
        "Default is 8.\n");
    printf("-caps: Capitalizes hex characters.\n");
    printf("\n");
    printf("-st --stats: At the end of cat-ting, "
        "returns a table with the frequency of each byte.\n");

    printf("flags that support --stats:\n");
    printf("    -st-p <arg_num>: "
        "Specify the stats frequency padding. Default is 4.\n");
    printf("    -st-sp <arg_num>: "
        "Specify the whitespace padding between columns. Default is 4.\n");
    printf("    -st-c <arg_num>: "
        "Specify the number of columns. Default is 8.\n");
    printf("    -st-v: Stats verbose. Will print hexs that have 0 occurence. "
        "Default hides this.\n");
    printf("    -fr --freq: Display stats table from highest to lowest frequency order.\n");
    printf("\n");
    printf("-m --match \"num1 num2 ...\": Return the starting position of sequences that matches "
        "the sequence given.\n");
    printf("%*sString should be under quotes and seperated by spaces.\n",28,"");

    printf("flags that support --match:\n");
    printf("    -m-p <arg_num>: Specify match index padding. Default is 2.\n");
    
    printf("\n");

    printf("-sec <line_num1> <line_num2>: Print section from lnum1 to lnum2."
        " Input will rounded down to the smallest line number\n");
    printf("%*s(e.g 3d4 will go to 3d0).\n", 30, "");

    printf("flags derived from -sec:\n");
    printf("    -l --line <line_num>: Print line line_num.\n");
    printf("    -se1 <line_num>: Print section 1 line up and 1 line down from current line.\n");

    printf("\n");
    printf("-sil --silent: Silent mode. Do not print hexdump.\n");
    printf("-ref: Displays useful references for control characters.\n");
    printf("-h --help: Show this list.\n");
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

void PRINT_REFERENCE(){
    printf("\n");
    printf("Useful references: \n");
    printf("All characters from 00 to 1f and 7f are control characters.\n");
    printf("Especially important characters:\n");
    printf("0a: Line feed/ new line.\n");
    printf("0d: Carriage return.\n");
}