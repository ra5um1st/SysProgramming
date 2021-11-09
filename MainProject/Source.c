#include "Threads.h"
#include <Windows.h>
#include <stdio.h>
#define THREADS_COUNT 2

int main() {
	size_t fib_size = 10;
	size_t fact_size = 5;

	HANDLE* hThreads = calloc(THREADS_COUNT, sizeof(HANDLE));
	if (hThreads) {
		hThreads[0] = CreateThread(0, 0, PrintFibonacciNumbers, &fib_size, 0, 0);
		hThreads[1] = CreateThread(0, 0, PrintFactNumbers, &fact_size, 0, 0);
		WaitForMultipleObjects(THREADS_COUNT, hThreads, TRUE, INFINITE);
		free(hThreads);
	}
	return 0;
}