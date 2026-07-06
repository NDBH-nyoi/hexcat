// This is not for compilation

void PRINT_HELP() {
    printf("Usage: hexcat.exe [flags] <args>...\n");
    printf("-i <arg>: File input.\n");
    printf("-p --padding <arg>: Specify index padding. Default is 8.\n");
    printf("-caps: Capitalizes hex characters.\n");
    
    printf("--stats: At the end of cat-ting, "
        "returns a table with the frequency of each byte.\n");

    printf("flags that support --stats:\n");
    printf("    -st-p --stats-padding <arg_num>: "
        "Specify the frequency padding. Default is 4.\n");
    printf("    -st-sp --stats-space <arg_num>: "
        "Specify the whitespace padding between columns. Default is 4.\n");
    printf("    -st-c --stats-colnum <arg_num>: "
        "Specify the number of columns. Default is 8.\n");
    printf("    -st-v --stats-verbose: Will print hexs that have 0 occurence. "
        "Default hides this.\n");
    printf("    -fr --freq: Display stats table from highest to lowest frequency order.\n");

    printf("-h --help: Show this list.\n");
}

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