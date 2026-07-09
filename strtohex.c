#include <stdio.h>
#include <string.h>
#include "useful_macros.c"

unsigned char *TEXTSTR = "";

int main(int argc, char * argv[]) {

    if (argc == 1) {
        printf("Nothing was inputted\n");
        return 1;
    }

    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i],"-str") == 0) {
            CLI_1ARGS(i, "-str", TEXTSTR);
        }
        else {
            printf("This is an error msg.\n");
            return 1;
        }
    }

    size_t TXTSTR_len = strlen(TEXTSTR);
    printf("String: %s\n", TEXTSTR);
    printf("Length: +%d.\n", TXTSTR_len);
    for (int i = 0; i < TXTSTR_len;i++) {
        printf("%.2x ", TEXTSTR[i]);
        
    }

    return 0;
}