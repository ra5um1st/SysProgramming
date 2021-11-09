#pragma once
#include <Windows.h>
#define EXPORT __declspec(dllexport)

typedef struct Person {
	LPTSTR Name;
	LPTSTR Surname;
	LPTSTR Patronymic;
	UINT  Age;
}Person;

typedef enum PersonsSearchParameter {
	Name,
	Surname,
	Patronymic,
	Age
}PersonsSearchParameter;

EXPORT Person** _cdecl ReadPersonsFromFile(CONST LPCTSTR path, UINT* size);
EXPORT Person** _cdecl FindPersons(CONST Person** persons, CONST UINT size, UINT* new_size, PersonsSearchParameter searchParameter, CONST BOOL(*Predicate)(LPTSTR));
EXPORT FLOAT _cdecl AveragePersonsAge(CONST Person** persons, CONST UINT size);
EXPORT BOOL _cdecl WritePersonsToFile(CONST LPCTSTR path, CONST Person** persons, CONST UINT size);
