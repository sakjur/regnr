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

#define REGVAL2(str) (676*lookup2[str[0]] + 100 * lookup2[str[3]] \
        + 26*lookup2[str[1]] + 10 * lookup2[str[4]] \
        + lookup2[str[2]] + lookup2[str[5]])

// CHANGE TO 7 IF USING UNIX LINE ENDINGS
#define SIZE_OF_ROW 8
#define ROW_BUFFER 6000
#define NUMBER_OF_PLATES 17576000

int lookup0[] = { 
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 100, 200, 300,    400, 500, 600, 700,    800, 900, 0, 0,    0, 0, 0, 0,
    0, 0, 676000, 1352000, 2028000, 2704000, 3380000, 4056000, 4732000, 5408000,
        6084000, 6760000, 7436000, 8112000, 8788000, 9464000,
    10140000, 10816000, 11492000, 12168000, 12844000, 13520000, 14196000, 
        14872000, 15548000, 16224000, 16900000, 17576000, 0,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0
};

int lookup1[] = {
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 10, 20, 30,    40, 50, 60, 70,    80, 90, 0, 0,    0, 0, 0, 0,
    0, 0, 26000, 52000, 78000, 104000, 130000, 156000, 182000, 208000,
        234000, 260000, 286000, 312000, 338000, 364000,
    390000, 416000, 442000, 468000, 494000, 520000, 546000,
        572000, 598000, 624000, 650000, 676000,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,
    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0
};

int lookup2[] = {
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
