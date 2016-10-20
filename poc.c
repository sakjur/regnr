#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_ROW 8
#define ROW_BUFFER 6000

int main(int argc, char* argv[]) {
    FILE* input;
    input = fopen(argv[1], "rb");
    char regnr[SIZE_OF_ROW * ROW_BUFFER];
    int regnr_read = fread(regnr, SIZE_OF_ROW, ROW_BUFFER, input);
    int counter = 0;

    while (regnr_read != 0) { // End loop on EOF
        for (int i = 0; i < regnr_read; i++) {
            counter++;
        }
        regnr_read = fread(regnr, SIZE_OF_ROW, ROW_BUFFER, input);
    }
    printf("%d\n", counter);
}
