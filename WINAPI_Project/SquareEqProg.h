#pragma once
#include "SquareEq.h"
#include "FileProc.h"

int StartProgram() {
	LPCTSTR readPath = L"Коэффициенты.txt";
	LPCTSTR writePath = L"Result.txt";
	HANDLE hFileRead = CreateFile(readPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	HANDLE hFileWrite = CreateFile(writePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD size_i = 0;
	DWORD size_j = 3;
	FLOAT** coefs = ReadSquareEqFromFile(hFileRead, &size_i, size_j);
	if (coefs) {
		FLOAT* descriminants = calloc(size_i, sizeof(FLOAT));;
		FLOAT** roots = calloc(size_i, sizeof(FLOAT*));
		if (roots && descriminants) {
			for (size_t i = 0; i < size_i; i++)
			{
				roots[i] = CalcSquareEq(coefs[i][0], coefs[i][1], coefs[i][2]);
				descriminants[i] = CalcDiscriminant(coefs[i][0], coefs[i][1], coefs[i][2]);
			}
			if (WriteSquareEqToFile(hFileWrite, ", ", roots, size_i, size_j - 1, descriminants)) {
				CloseHandle(hFileRead);
				CloseHandle(hFileWrite);
				return 0;
			}
			else
			{
				CloseHandle(hFileRead);
				CloseHandle(hFileWrite);
				return 1;
			}
		}
		else
		{
			CloseHandle(hFileRead);
			CloseHandle(hFileWrite);
			return 1;
		}
	}
	else
	{
		CloseHandle(hFileRead);
		CloseHandle(hFileWrite);
		return 1;
	}
}