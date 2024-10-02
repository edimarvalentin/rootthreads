//
// Created by evalentin on 9/30/24.
//
#include <pthread.h>
#include "data.h"
#include "root.h"

int main() {
    pthread_t getDataPID, readDataPID, processDataPID, storeDataPID;
    pthread_create(&getDataPID, NULL, getData, NULL);
    pthread_join(getDataPID, NULL);
    pthread_create(&readDataPID, NULL, readData, NULL);
    pthread_create(&processDataPID, NULL, processData, NULL);
    pthread_create(&storeDataPID, NULL, storeData, NULL);
    pthread_join(readDataPID, NULL);
    pthread_join(processDataPID, NULL);
    pthread_join(storeDataPID, NULL);
    return 0;
}
