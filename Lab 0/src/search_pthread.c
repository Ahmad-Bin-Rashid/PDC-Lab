#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 100000000
#define TARGET 42
#define NUM_THREADS 4
int *arr;
int found_index = -1;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void* search_chunk(void* arg) {
long start = *(long*)arg;
long end = start + N/NUM_THREADS;
if (start == (NUM_THREADS-1)*N/NUM_THREADS) end = N; // last chunk
for (long i = start; i < end; i++) {
// Check if target already found by another thread
pthread_mutex_lock(&lock);
int stop = (found_index != -1);
pthread_mutex_unlock(&lock);
if (stop) break;
if (arr[i] == TARGET) {
pthread_mutex_lock(&lock);
if (found_index == -1) found_index = i; // first thread to find sets index
pthread_mutex_unlock(&lock);
break;
}
}
return NULL;
}
