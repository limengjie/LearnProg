#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Thread function to generate sum of 0 to N
void* sum_runner(void* arg)
{
	long long *limit_ptr = (long long*) arg;
	long long limit = *limit_ptr;

	pthread_mutex_lock(&mutex);
	long long sum = 0;
	for (long long i = 0; i <= limit; i++) {
		sum += i;
	}

	long long *answer = malloc(sizeof(*answer));
	*answer = sum;
	pthread_mutex_unlock(&mutex);

	pthread_exit(answer);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <num 1> <num 2> ... <num-n>\n", argv[0]);
		exit(-1);
	}
	int num_args = argc - 1;

	// Launch thread
	pthread_t tids[num_args];
	for (int i = 0; i < num_args; i++) {
		long long limit = atoll(argv[i + 1]);

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, sum_runner, (void*)&limit);
	}

	// Wait until thread is done its work
	long long * res[num_args];
	for (int i = 0; i < num_args; i++) {
		//long long * res;
		pthread_join(tids[i], (void**)&res[i]);
		printf("Sum for thread %d is %lld\n",
				i, *res[i]);
		//free(res);
	}
}
