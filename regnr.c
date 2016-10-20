/**
 * (C) Emil Tullstedt <emiltu@kth.se> 2016-10-20
 *
 * Developed for the "Develop your way to Silicon Valley" competition by
 * Comsid <http://www.consid.se/program-your-way-to-silicon-valley/>
 *
 * Very simple, straight forward, single function, standard library C99
 * code submission reading the filename for the input file from argv[1]
 *
 * Refers to a complete registration plate mapping on the heap to detect
 * collissions
 *
 * Feel free to use this code however you want. Refer to the MIT license or
 * CC0 if one is needed :)
 */

#define _DEFAULT_SOURCE 1
#include <stdio.h>
#include <stdlib.h>

#define ACTOI(c) ((int) c - 'A')
#define ICTOI(c) ((int) c - '0')
#define REGVAL(str) (676000*ACTOI(str[0]) + 26000*ACTOI(str[1])\
        + 1000*ACTOI(str[2]) + 100*ICTOI(str[3]) + 10*ICTOI(str[4]) +\
        ICTOI(str[5]));

#define LOOKUP(str,n) (lookup[(int) str[n]])
#define REGVAL2(str) (676*LOOKUP(str, 0) + 100 * LOOKUP(str, 3) \
        + 26*LOOKUP(str, 1) + 10 * LOOKUP(str, 4) \
        + LOOKUP(str, 2) + LOOKUP(str, 5))

// CHANGE TO 7 IF USING UNIX LINE ENDINGS
#define SIZE_OF_ROW 8
#define ROW_BUFFER 6000
#define NUMBER_OF_PLATES 17576000

int lookup[] = {
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 1, 2, 3,    4, 5, 6, 7,    8, 9, 0, 0,    0, 0, 0, 0,
    0, 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000,
        9000, 10000, 11000, 12000, 13000, 14000,
    15000, 16000, 17000, 18000, 19000, 20000, 21000,
        22000, 23000, 24000, 25000, 26000,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0
};

int main(int argc, char* argv[]) {
    FILE* input;
    input = fopen(argv[1], "rb");
    char* d = (char*) calloc(1, NUMBER_OF_PLATES);
    char regnr[SIZE_OF_ROW * ROW_BUFFER];
    int regnr_read = fread(regnr, SIZE_OF_ROW, ROW_BUFFER, input);
    int value = 0;

    /**
     * O(N) lookup for duplicates
     */
    while (regnr_read != 0) { // End loop on EOF
        for (int i = 0; i < regnr_read; i++) {
            value = REGVAL2((regnr + i*SIZE_OF_ROW));
            d[value] = d[value] ^ 1;
            if (!d[value]) {
                printf("Dubbletter\n");
                goto exit; // Yes, I did!
            }
        }
        // Buffer up next ROW_BUFFER rows of plates
        regnr_read = fread(regnr, SIZE_OF_ROW, ROW_BUFFER, input);
    }

    printf("Ej dubblett\n");
exit:
    free(d);
    fclose(input);
    return 0;
}
