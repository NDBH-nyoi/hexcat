
// Input segment
char *inFileName = "";
char HELP_FLAG = 0; // false. Also the "\0" character.
char CAPITAL_FLAG = 0;

unsigned char PaddingSize = 8; // default padding size

char STATS_FLAG = 0;
char STATS_FREQ_FLAG = 0;
char STATS_VERBOSE_FLAG = 0;
unsigned char STATS_PADDING = 4; // Haven't done any work yet
unsigned char STATS_SPACEPADDING = 4;
unsigned char COLUMN_NUMBER = 8;

unsigned int byteStats[256] = {0}; // each index represent the value of that byte e.g 0x10 is at index 16

char *MATCH_STRING="";
char RETURN_MATCH_STR[96] = "";
char MATCH_FLAG = 0;
unsigned char MatchIndexPadding = 2;

char SILENT_FLAG = 0;
char REFERENCE_FLAG = 0;
// Can probably do a comparision, and do a stats print with order most frequent to least frequent.
// if you want, you can make it so bytes with no appearance doesn't get printed.


// LOOK HERE FOR DIRECTIVES!!!
int ch;

// char *_Format = "%.2x ";
int HexPerLine = 16;
int Buf_forChars16[16]; // chances are this will be malloc

int Hex_Counter = 16; // will be resetted to 0 later for hex counter = hexperline
unsigned long long int LineNum = 0; 

// Note this was on line 122
unsigned char ConversionBuf[32]; // streamed into from input
unsigned char ConverBufCounter = 0; // counter for conversion buf, also length of conversion buf
unsigned char ComparisonBuf[32]; // streamed into from fgetc, is int also
// Max length should be equal to length of conversion buf, 
//when that happens, we start doing memmove stuff 
unsigned char CompareCounter = 0;
long long int matchesPosition[128]; // holds matches position, this is really easy to overflow if the file is too large.
unsigned char PositionCounter = 0;
unsigned char EqualCounter = 0;
// Also do it so if ConverBufCounter, ComparisonCounter > 32 then exit