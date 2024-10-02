//
// Created by evalentin on 9/30/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define DATASIZE 10000

__uint8_t *input_buffer;
float *processed_buffer;

int n_read_values = 0;
int n_processed_values = 0;
int n_written_values = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_w = PTHREAD_COND_INITIALIZER;

/**
 * @brief Reads data from a data.txt and stores it in the input buffer.
 *
 * @return NULL
 */
void *readData() {
    clock_t t;
    t = clock();
    FILE *data = fopen("data.txt", "r");
    if (data != NULL) {
        input_buffer = malloc(sizeof(__uint8_t) * DATASIZE);
        char cNumber[4];
        while (fgets(cNumber, sizeof(cNumber), data) != NULL) {
            if (cNumber[0] == '\n') continue;
            size_t size = strlen(cNumber);
            if (size > 0 && cNumber[size - 1] == '\n') cNumber[size - 1] = '\0';
            __uint8_t value = (__uint8_t)strtoul(cNumber, NULL, 10);
            pthread_mutex_lock(&mutex);
            input_buffer[n_read_values] = value;
            n_read_values++;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
        }
        fclose(data);
    }
    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("Time taken for read thread: %f seconds\n", time_taken);
    return NULL;
}

/**
 * @brief Gets the roots of the data from the input buffer and
 * stores the results in the processed buffer.
 * @return NULL
 */
void *processData() {
    clock_t t;
    t = clock();
    processed_buffer = malloc(sizeof(float) * DATASIZE);
    while (n_processed_values != DATASIZE) {
        pthread_mutex_lock(&mutex);
        while (n_processed_values >= n_read_values) {
            pthread_cond_wait(&cond, &mutex);
        }
        if (n_processed_values >= n_read_values) {
            pthread_cond_broadcast(&cond_w);
            pthread_mutex_unlock(&mutex);
            break;
        }
        float R = input_buffer[n_processed_values];
        n_processed_values++;
        pthread_mutex_unlock(&mutex);
        float yn1 = (R == 0) ? 0 : R / 2.0f;
        for (int j = 0; j < 10 && R != 0; j++) {
            yn1 = 0.5f * (yn1 + R / yn1);
        }
        processed_buffer[n_processed_values - 1] = yn1;
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond_w);
        pthread_mutex_unlock(&mutex);
    }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("Time taken for sqrt thread: %f seconds\n", time_taken);
    return NULL;
}

/**
 * @brief Writes the processed values from the processed buffer to the file "sqrt.txt"
 * @return NULL
 */
void *storeData() {
    clock_t t;
    t = clock();
    FILE *output_file = fopen("sqrt.txt", "w");
    while (n_written_values != DATASIZE) {
        pthread_mutex_lock(&mutex);
        while (n_written_values >= n_processed_values) {
            pthread_cond_wait(&cond_w, &mutex);
        }
        if (n_written_values >= n_processed_values) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        fprintf(output_file, "%f\n", processed_buffer[n_written_values]);
        n_written_values++;
        pthread_mutex_unlock(&mutex);
    }
    fclose(output_file);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("Time taken for store thread: %f seconds\n", time_taken);
    return NULL;
}

