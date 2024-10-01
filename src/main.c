//
// Created by evalentin on 9/30/24.
//
#include <pthread.h>
#include "data.h"
#include "root.h"

int main() {
    pthread_t getDataPID, readDataPID;
    pthread_create(&getDataPID, NULL, getData, NULL);
    pthread_join(getDataPID, NULL);
    pthread_create(&readDataPID, NULL, readData, NULL);
    pthread_join(readDataPID, NULL);
    return 0;
}
