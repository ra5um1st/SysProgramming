#include "Persons.h"
#include <stdio.h>

Person** _cdecl ReadPersonsFromFile(const LPCTSTR path, UINT* size)
{
	HANDLE hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	*size = 0;
	if (hFile) {
		UINT bufferSize = 10000;
		DWORD readBytes = 0;
		LPTSTR lpBuffer = malloc((bufferSize + 1) * sizeof(TCHAR));
		if (lpBuffer) {
			lpBuffer[bufferSize] = L'\0';
			UINT lineCount = 0;
			if (ReadFile(hFile, lpBuffer, bufferSize, &readBytes, NULL)) {
				UINT i = 0;
				while (lpBuffer[i] != L'\0') {
					if (lpBuffer[i] == L'\n')
						lineCount++;
					i++;
				}
				UINT* lineIndexes = malloc((lineCount + 1) * sizeof(UINT));

				if (lineIndexes) {
					i = 0;
					UINT j = 1;
					lineIndexes[0] = 0;
					while (lpBuffer[i] != L'\0') {
						if (lpBuffer[i] == L'\n')
						{
							lineIndexes[j] = i;
							j++;
						}
						i++;
					}
				}

				Person** persons = malloc(lineCount * sizeof(Person*));
				if (persons) {
					i = 0;
					UINT atributeCount = 4;
					UINT atributeSize = 50;
					LPTSTR tempBuffer = lpBuffer;

					while (i < lineCount)
					{
						tempBuffer = lpBuffer + lineIndexes[i] + 1;

						if (i != lineCount - 1) {
							lpBuffer[lineIndexes[i + 1]] = L'\0';
						}

						persons[i] = malloc(sizeof(Person));
						if (persons[i]) {
							persons[i]->Name = malloc((atributeSize + 1) * sizeof(TCHAR));
							persons[i]->Surname = malloc((atributeSize + 1) * sizeof(TCHAR));
							persons[i]->Patronymic = malloc((atributeSize + 1) * sizeof(TCHAR));
							if (persons[i]) {
								persons[i]->Name[atributeSize] = L'\0';
								persons[i]->Surname[atributeSize] = L'\0';
								persons[i]->Patronymic[atributeSize] = L'\0';
								swscanf_s(tempBuffer, L"%[^;];%[^;];%[^;];%d\r", persons[i]->Name, atributeSize, persons[i]->Surname, atributeSize, persons[i]->Patronymic, atributeSize, &persons[i]->Age);
								(*size)++;
							}
						}
						if (i != lineCount - 1) {
							lpBuffer[lineIndexes[i + 1]] = L'\n';
						}
						i++;
					}
					CloseHandle(hFile);
					free(lineIndexes);
					free(lpBuffer);
					return persons;
				}
				free(lineIndexes);
			}
			CloseHandle(hFile);
			free(lpBuffer);
			return NULL;
		}
		CloseHandle(hFile);
		return NULL;
	}
	else
	{
		return NULL;
	}
}

Person** _cdecl FindPersons(const Person** persons, const UINT size, UINT* new_size, PersonsSearchParameter searchParameter, const BOOL(*Predicate)(LPTSTR))
{
	switch (searchParameter)
	{
	case Name:
	{
		*new_size = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (Predicate(persons[i]->Name)) {
				(*new_size)++;
			}
		}
		Person** _persons = malloc((*new_size) * sizeof(Person*));
		if (_persons) {
			for (size_t i = 0; i < *new_size; i++)
			{
				_persons[i] = malloc(sizeof(Person));
			}
			for (size_t i = 0, j = 0; i < size; i++)
			{
				if (_persons[j]) {
					if (Predicate(persons[i]->Name)) {
						_persons[j]->Name = persons[i]->Name;
						_persons[j]->Surname = persons[i]->Surname;
						_persons[j]->Patronymic = persons[i]->Patronymic;
						_persons[j]->Age = persons[i]->Age;
						j++;
					}
				}
			}
		}
		return _persons;
		break;
	}
	case Surname:
	{
		*new_size = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (Predicate(persons[i]->Surname)) {
				(*new_size)++;
			}
		}
		Person** _persons = malloc((*new_size) * sizeof(Person*));

		if (_persons) {
			for (size_t i = 0; i < *new_size; i++)
			{
				_persons[i] = malloc(sizeof(Person));
			}

			for (size_t i = 0, j = 0; i < size; i++)
			{
				if (_persons[j]) {

					if (Predicate(persons[i]->Name)) {
						_persons[j]->Name = persons[i]->Name;
						_persons[j]->Surname = persons[i]->Surname;
						_persons[j]->Patronymic = persons[i]->Patronymic;
						_persons[j]->Age = persons[i]->Age;
						j++;
					}
				}
			}
		}
		return _persons;
		break;
	}
	case Patronymic:
	{
		*new_size = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (Predicate(persons[i]->Patronymic)) {
				(*new_size)++;
			}
		}
		Person** _persons = malloc((*new_size) * sizeof(Person*));

		if (_persons) {
			for (size_t i = 0; i < *new_size; i++)
			{
				_persons[i] = malloc(sizeof(Person));
			}
			for (size_t i = 0, j = 0; i < size; i++)
			{
				if (_persons[j]) {
					if (Predicate(persons[i]->Patronymic)) {
						_persons[j]->Name = persons[i]->Name;
						_persons[j]->Surname = persons[i]->Surname;
						_persons[j]->Patronymic = persons[i]->Patronymic;
						_persons[j]->Age = persons[i]->Age;
						j++;
					}
				}
			}
		}
		return _persons;
		break;
	}
	case Age:
	{
		*new_size = 0;
		UINT bufferSize = 3;
		LPTSTR tempBuffer = malloc((bufferSize + 1) * sizeof(TCHAR));
		if (tempBuffer) {
			tempBuffer[bufferSize] = L'\0';

			for (size_t i = 0; i < size; i++)
			{
				swprintf_s(tempBuffer, bufferSize, L"%d", persons[i]->Age);
				if (Predicate(tempBuffer)) {
					(*new_size)++;
				}
			}

			Person** _persons = malloc((*new_size) * sizeof(Person*));

			if (_persons) {
				for (size_t i = 0; i < *new_size; i++)
				{
					_persons[i] = malloc(sizeof(Person));
				}
				for (size_t i = 0, j = 0; i < size; i++)
				{
					if (_persons[j]) {
						swprintf_s(tempBuffer, bufferSize, L"%d", persons[i]->Age);
						if (Predicate(tempBuffer)) {
							_persons[j]->Name = persons[i]->Name;
							_persons[j]->Surname = persons[i]->Surname;
							_persons[j]->Patronymic = persons[i]->Patronymic;
							_persons[j]->Age = persons[i]->Age;
							j++;
						}
					}
				}
			}
			free(tempBuffer);
			return _persons;
			break;
		}
		else
		{
			return NULL;
			break;
		}
	}
	default:
		return NULL;
		break;
	}
}

FLOAT _cdecl AveragePersonsAge(const Person** persons, const UINT size)
{
	FLOAT result = 0;
	if (persons) {
		for (size_t i = 0; i < size; i++)
		{
			if (persons[i]) 
				result += persons[i]->Age;
		}
		result /= size;
	}
	return result;
}

BOOL _cdecl WritePersonsToFile(const LPCTSTR path, const Person** persons, const UINT size)
{
	HANDLE hFile = CreateFile(path, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile) {
		DWORD bytes = 0;
		UINT bufferSize = 10000;
		LPTSTR lpBuffer = malloc((bufferSize + 1) * sizeof(TCHAR));
		if (lpBuffer) {
			lpBuffer[bufferSize] = L'\0';
			UINT writtenSize = 0;
			for (size_t i = 0; i < size; i++)
			{
				if (i != size - 1) {
					writtenSize += swprintf_s(lpBuffer + writtenSize, bufferSize - writtenSize, L"%s;%s;%s;%d\n", persons[i]->Name, persons[i]->Surname, persons[i]->Patronymic, persons[i]->Age);
				}
				else
				{
					writtenSize += swprintf_s(lpBuffer + writtenSize, bufferSize - writtenSize, L"%s;%s;%s;%d", persons[i]->Name, persons[i]->Surname, persons[i]->Patronymic, persons[i]->Age);
				}
			}
			LPSTR lpWideCharBuffer = malloc((writtenSize + 1) * sizeof(CHAR));
			lpWideCharBuffer[writtenSize] = '\0';
			lpBuffer[writtenSize + 1] = L'\0';
			WideCharToMultiByte(CP_ACP, 0, lpBuffer, writtenSize, lpWideCharBuffer, writtenSize, NULL, NULL);
			if (WriteFile(hFile, lpWideCharBuffer, writtenSize, &bytes, NULL)) {
				free(lpBuffer);
				CloseHandle(hFile);
				return 1;
			}
			else
			{
				free(lpBuffer);
				CloseHandle(hFile);
				return 0;
			}
		}
		free(lpBuffer);
		CloseHandle(hFile);
		return 0;
	}
	else
	{
		return 0;
	}
}