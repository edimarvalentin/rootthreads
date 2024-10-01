//
// Created by evalentin on 9/30/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define DATASIZE 10000

void *getData() {
    int *status = malloc(sizeof(int));
    FILE *data = fopen("data.txt", "r");
    if (data == NULL) {
        *status = 0;
        data = fopen("data.txt", "w");
        int i = 0;
        srand(time(NULL));
        while (i < DATASIZE) {
            __uint8_t v = rand() % 256;
            fprintf(data, "%u\n", v);
            i++;
        }
        fclose(data);
    }else {
        *status = 1;
    }
    pthread_exit(status);
}
