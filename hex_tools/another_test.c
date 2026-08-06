#include <stdio.h>

char *filename = ".\\hexwrite.c";

int main()
{
    FILE *INPUT_FILE = fopen(filename, "r");

    int character;

    while (character != EOF)
    {
        character = fgetc(INPUT_FILE);

        printf("%.2x ", character);

    }

    fclose(INPUT_FILE);

    return 0;
}