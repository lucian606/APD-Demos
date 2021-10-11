#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 4

typedef struct {
	long x;
    long y;
    long id;
} params;

void *f(void *args) {
	params p = *(params *)args;
	printf("Thread: %ld has the point (%ld, %ld)\n", p.id, p.x, p.y);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    params args[NUM_THREADS];
	int r;
    long id;
    void *status;

    for (id = 0; id < NUM_THREADS; id++) {
		params p = {id * 2, id * (-5), id};
		args[id] = p;
		r = pthread_create(&threads[id], NULL, f, (void *)&args[id]);

		if (r) {
	  		printf("Eroare la crearea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	}

  	for (id = 0; id < NUM_THREADS; id++) {
		r = pthread_join(threads[id], &status);

		if (r) {
	  		printf("Eroare la asteptarea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	}

  	pthread_exit(NULL);
}