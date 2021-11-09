#pragma once
#include <Windows.h>
#include <stdio.h>

DWORD CountLines(LPSTR lpStr) {
	DWORD dwLinesCount = 0;
	for (DWORD i = 0; lpStr[i] != '\0'; i++) {
		if (lpStr[i] == '\n') dwLinesCount++;
	}
	return dwLinesCount;
}

void RemoveSpace(LPSTR str) {
	int counter = 0;
	for (size_t i = 0; str[i]; i++)
	{
		if (str[i] != ' '){
			str[counter++] = str[i];
		}
	}
	str[counter] = '\0';
}

DWORD GetFloatLenght(FLOAT fNumber) {
	size_t numberLength = snprintf(NULL, 0, "%f", fNumber);
}

LPSTR GetSquareEqStr(FLOAT* fArray, DWORD size_i, FLOAT fDiscriminant, LPSTR lpSeparator) {
	DWORD dwSize = 128;
	LPSTR lpStr;
	LPSTR lpNumber;
	LPSTR lpCounter;

	lpStr = calloc(dwSize, sizeof(CHAR));
	lpStr[dwSize - 1] = '\0';

	if (fDiscriminant > 0.0 || fDiscriminant == 0.0) {
		for (DWORD i = 0; i < size_i; i++)
		{
			size_t numberLength = snprintf(NULL, 0, "%f", fArray[i]);
			lpNumber = calloc(numberLength + 1, sizeof(CHAR));
			lpCounter = calloc(2, sizeof(CHAR));
			lpNumber[numberLength] = '\0';
			lpCounter[1] = '\0';

			snprintf(lpNumber, 10, "%f", fArray[i]);
			snprintf(lpCounter, 10, "%d", i + 1);
			strcat_s(lpStr, dwSize, "X");
			strcat_s(lpStr, dwSize, lpCounter);
			strcat_s(lpStr, dwSize, " = ");
			strcat_s(lpStr, dwSize, lpNumber);
			strcat_s(lpStr, dwSize, lpSeparator);

			free(lpNumber);
			free(lpCounter);
		}
	}
	if (fDiscriminant < 0.0) {
		strcat_s(lpStr, dwSize, "Корней нет");
		strcat_s(lpStr, dwSize, lpSeparator);
	}

	size_t numberLength = snprintf(NULL, 0, "%f", fDiscriminant);
	lpNumber = calloc(numberLength, sizeof(CHAR));

	snprintf(lpNumber, 10, "%f", fDiscriminant);
	strcat_s(lpStr, dwSize, "D = ");
	strcat_s(lpStr, dwSize, lpNumber);
	return lpStr;
}

FLOAT** ReadSquareEqFromFile(HANDLE hFile, DWORD* size_i, CONST DWORD size_j) {
	if (hFile && size_i) {
		DWORD dwBuffer = 0;
		DWORD dwBufferSize = 10000;
		LPSTR lpBuffer = malloc(dwBufferSize + 1);

		if (lpBuffer) {
			if (ReadFile(hFile, lpBuffer, dwBufferSize, &dwBuffer, NULL)) {
				lpBuffer[dwBufferSize] = '\0';

				DWORD j = 0;
				DWORD dwTempStrCounter = 0;
				DWORD dwArrayCounter = 0;
				DWORD dwTempBufferSize = 100;
				LPSTR lpTempStr = calloc(dwTempBufferSize + 1, sizeof(CHAR));
				lpTempStr[dwTempBufferSize] = '\0';

				*size_i = CountLines(lpBuffer) + 1;
				FLOAT** resArray = calloc(*size_i, sizeof(FLOAT*));
				if (resArray)
				{
					for (DWORD i = 0; i < *size_i; i++)
					{
						resArray[i] = calloc(size_j, sizeof(FLOAT));
						for (; lpBuffer[j] != '\n' && lpBuffer != '\0'; j++)
						{
							if (dwArrayCounter < size_j) {
								if (lpBuffer[j] < '0' || lpBuffer[j] > '9') {
									if (lpTempStr[0] >= '0' && lpTempStr[0] <= '9' || lpTempStr[0] == '-') {
										if (lpBuffer[j] == ' ') {
											resArray[i][dwArrayCounter++] = atof(lpTempStr);

											free(lpTempStr);
											dwTempStrCounter = 0;
											lpTempStr = calloc(dwTempBufferSize + 1, sizeof(CHAR));
											lpTempStr[dwTempBufferSize] = '\0';
										}
										if (lpBuffer[j] == '.' || lpBuffer[j] == ',') {
											lpTempStr[dwTempStrCounter++] = '.';
										}
									}
									else
									{
										if (lpBuffer[j] == '-') {
											lpTempStr[dwTempStrCounter++] = lpBuffer[j];
										}
									}
									continue;
								}
								else
								{
									lpTempStr[dwTempStrCounter++] = lpBuffer[j];
								}
							}
						}
						resArray[i][dwArrayCounter++] = atof(lpTempStr);

						free(lpTempStr);
						j++;
						dwArrayCounter = 0;
						dwTempStrCounter = 0;
						lpTempStr = calloc(dwTempBufferSize + 1, sizeof(CHAR));
						lpTempStr[dwTempBufferSize] = '\0';
					}
				}
				else
				{
					free(lpBuffer);
					free(lpTempStr);
					return NULL;
				}
				free(lpBuffer);
				free(lpTempStr);
				return resArray;
			}
			else
			{
				free(lpBuffer);
				return NULL;
			}
		}
		else 
		{
			free(lpBuffer);
			return NULL; 
		}
	}
	else return NULL;
}

BOOL WriteSquareEqToFile(HANDLE hFile, LPSTR lpSeparator, FLOAT** fRoots, DWORD size_i, DWORD size_j, FLOAT* fDescriminants) {
	DWORD dwBuffer = 0;
	DWORD dwBufferSize = 4096;
	LPSTR lpBuffer = calloc(dwBufferSize, sizeof(CHAR));

	if (hFile != NULL && fRoots != NULL && fDescriminants != NULL && lpBuffer != NULL) {
		for (size_t i = 0; i < size_i; i++)
		{
			LPSTR lpTemp = GetSquareEqStr(fRoots[i], size_j, fDescriminants[i], lpSeparator);
			strcat_s(lpBuffer, dwBufferSize, lpTemp);
			strcat_s(lpBuffer, dwBufferSize, "\n");
			free(lpTemp);
		}
		if (WriteFile(hFile, lpBuffer, strlen(lpBuffer), &dwBuffer, NULL)) {
			free(lpBuffer);
			return TRUE;
		}
	}
	else
	{
		free(lpBuffer);
		return FALSE;
	}
}