
#define CLI_0ARGS(counter, flag, arg1) do {\
    arg1=1;\
    counter+=1;\
} while(0)\

#define CLI_1ARGS(counter, flag, arg1, func) do {\
if (counter + 1 >= argc) { \
    printf("Error: " flag " requires an argument.\n"); \
    return 1; \
} \
arg1 = func(argv[counter+1]); \
counter+=2; \
} while(0)\

#define CLI_2ARGS(counter, flag, arg1, arg2, func) do {\
    if (counter + 2 >= argc) { \
        printf("Error: " flag " requires 2 arguments.\n"); \
        return 1; \
    } \
    arg1 = func(argv[counter+1]);\
    arg2 = func(argv[counter+2]);\
    counter+=3; \
} while(0)\

#define CLI_1ARGSERR(flag) printf("Error: " flag " requires an argument.\n"); 

// if (counter + 2 >= argc) { 
//     printf("Error: " flag " requires 2 arguments.\n"); 
//     return 1; 
// } 
// arg1 = argv[counter+1];
// arg2 = argv[counter+2];
// counter+=3; 

// diffrences are return 1 has been changed to break
// argv and argc turned to TokensBuf and TokensCount
#define CLI_1ARGS_edit(counter, flag, arg1, func) do {\
if (counter + 1 >= TokensCount) { \
    printf("Error: " flag " requires an argument.\n"); \
    break; \
} \
arg1 = func(TokensBuf[counter+1]); \
counter+=2; \
} while(0)\

