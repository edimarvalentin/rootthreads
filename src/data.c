//
// Created by evalentin on 9/30/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define DATASIZE 10000

/**
 * @brief Checks if a data.txt file exist or creates a new one with 10,000 unsigned 8-bit integers.
 * @return 0 for new data, 1 for already existing data
 */
void *getData() {
    clock_t t;
    t = clock();
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
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("Time taken for data thread: %f seconds\n", time_taken);
    return NULL;
    pthread_exit(status);
}
