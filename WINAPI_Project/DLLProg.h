#include <Windows.h>
#include "../DLL_Project/Persons.h"

const BOOL ByName(LPTSTR name) {
	LPTSTR test = L"Иванов";
	for (size_t i = 0; name[i] != L'\0' && test[i] != L'\0'; i++)
	{
		if (name[i] != test[i])
			return 0;
		else
			return 1;
	}
}
const BOOL ByAge(LPTSTR age) {
	LPTSTR test = L"17";
	for (size_t i = 0; age[i] != L'\0' && test[i] != L'\0'; i++)
	{
		if (age[i] != test[i])
			return 0;
	}
	return 1;
}

void StartProgram() {
	HMODULE dll = LoadLibraryW(L"../MainProject/x64/Debug/DLL_Project.dll");
	if (dll) {
		typedef Person** (_cdecl* ReadPersonsFromFile)(CONST LPCTSTR path, UINT* size);
		ReadPersonsFromFile func = GetProcAddress(dll, "ReadPersonsFromFile");

		UINT size = 0;
		Person** persons = func(L"../MainProject/x64/Debug/Users.csv", &size);

		Person** (_cdecl * FindPersons)(CONST Person * *persons, CONST UINT size, UINT * new_size, PersonsSearchParameter searchParameter, CONST BOOL(*Predicate)(LPTSTR)) = GetProcAddress(dll, "FindPersons");
		BOOL(_cdecl * WritePersonsToFile)(CONST LPCTSTR path, CONST Person * *persons, CONST UINT size) = GetProcAddress(dll, "WritePersonsToFile");

		FLOAT(_cdecl * AveragePersonsAge)(CONST Person * *persons, CONST UINT size) = GetProcAddress(dll, "AveragePersonsAge");
		FLOAT avgAge = AveragePersonsAge(persons, size);

		UINT new_size = 0;
		Person** _persons = NULL;
		if (persons)
			_persons = FindPersons(persons, size, &new_size, Age, &ByAge);

		if (_persons)
			WritePersonsToFile(L"../MainProject/x64/Debug/Result.csv", _persons, new_size);
		FreeLibrary(dll);
	}
}