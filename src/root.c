//
// Created by evalentin on 9/30/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATASIZE 10000

__uint128_t *input_buffer;
int n_read_values = 0;

void *readData() {
    FILE *data = fopen("data.txt", "r");
    if (data != NULL) {
        input_buffer = malloc(sizeof(__uint128_t) * DATASIZE);
        char cNumber[3];
        while (fgets(cNumber, 4, data) != NULL) {
            if (cNumber[0] == '\n') {
                continue;
            }
            size_t size = strlen(cNumber);
            if (size > 0 && cNumber[size - 1] == '\n') {
                cNumber[size - 1] = '\0';
            }
            __uint8_t value = (__uint8_t) strtoul(cNumber, NULL, 10);
            input_buffer[n_read_values] = value;
            i++;
        }
    }
    return NULL;
}

void *processData() {

}

