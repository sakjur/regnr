#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER_OF_PLATES 17576000 
#define ACTOI(c) ((int) c - 'A')
#define ICTOI(c) ((int) c - '0')
#define REGVAL(str) (26*26*1000*ACTOI(str[0]) + 26*1000*ACTOI(str[1])\
        + 1000*ACTOI(str[2]) + 100*ICTOI(str[3]) + 10*ICTOI(str[4]) +\
        ICTOI(str[5]));
#define SIZE_OF_ROW 8
#define ROW_BUFFER 6000

// Unused
//int ctoi(char c) {
//    int rv = (int) c - 'A';
//    return rv;
//}
//
//int regval(char* str) {
//    return 26*26*1000*ctoi(str[0]) + 26*1000*ctoi(str[1]) + 1000*ctoi(str[2])
//        + atoi(str + 3);
//}

int main(int argc, char* argv[]) {
    FILE* input;
    input = fopen(argv[1], "r");
    char* d = (char*) calloc(1, NUMBER_OF_PLATES);
    char regnr[SIZE_OF_ROW * ROW_BUFFER];
    int regnr_read = fread(regnr, SIZE_OF_ROW, ROW_BUFFER, input);
    int value = 0;

    // CHANGE TO 7 IF USING UNIX LINE ENDINGS
    while (regnr_read != 0) {
        for (int i = 0; i < regnr_read; i++) {
            value = REGVAL((regnr + i*8)); 
            if (d[value] == 1) {
                printf("Dubbletter\n");
                goto exit;
            }
            d[value] = 1;
        }
        regnr_read = fread(regnr, SIZE_OF_ROW, ROW_BUFFER, input);
    }

    printf("Ej dubblett\n");
exit:
    free(d);
    fclose(input);
    return 0;
}
