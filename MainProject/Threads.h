#pragma once
#include <Windows.h>
#include <stdio.h>

DWORD WINAPI PrintFibonacciNumbers(LPVOID lpParameter) {
	size_t count = *(size_t*)lpParameter;
	size_t* fibNumbers = calloc(3, sizeof(size_t));
	if (fibNumbers) {
		fibNumbers[0] = 0;
		fibNumbers[1] = 1;
		for (size_t i = 0; i <= count; i++)
		{
			if (i == 0)
				printf_s("i = %zd\tfib number = %zd\n", i, fibNumbers[0]);
			else if (i == 1)
				printf_s("i = %zd\tfib number = %zd\n", i, fibNumbers[1]);
			else
			{
				fibNumbers[2] = fibNumbers[0] + fibNumbers[1];
				printf_s("i = %zd\tfib number = %zd\n", i, fibNumbers[2]);
				fibNumbers[0] = fibNumbers[1];
				fibNumbers[1] = fibNumbers[2];
			}
		}
		free(fibNumbers);
	}
	ExitThread(0);
}

DWORD WINAPI PrintFactNumbers(LPVOID lpParameter) {
	size_t count = *(size_t*)lpParameter;
	size_t value = 1;
	for (size_t i = 1; i <= count; i++)
	{
		value *= i;
		printf_s("i = %zd\t!number = %zd\n", i, value);
	}
	ExitThread(0);
}