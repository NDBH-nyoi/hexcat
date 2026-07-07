
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

#define CLI_1ARGSERR(flag) printf("Error: " flag " requires an argument.\n"); 

// if (counter + 2 >= argc) { 
//     printf("Error: " flag " requires 2 arguments.\n"); 
//     return 1; 
// } 
// arg1 = argv[counter+1];
// arg2 = argv[counter+2];
// counter+=3; 
