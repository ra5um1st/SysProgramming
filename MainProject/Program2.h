#pragma once
#include <stdio.h>

int sum(int, int);
int dif(int, int);
int mul(int, int);
float div(int, int);

int sum(int a, int b) {
	return a + b;
}

int dif(int a, int b) {
	return a - b;
}

int mul(int a, int b) {
	return a * b;
}

float div(int a, int b) {
	return a / b;
}

char* concat(char* s1, char* s2) {
	int i = 0;
	int j = 0;
	for (; s1[i] != '\0'; i++);
	for (; s2[i] != '\0'; i++);
	char* s = malloc(i * sizeof(char) + 1);
	s[i] = '\0';
	i = 0;
	for (; s1[i] != '\0'; i++)
	{
		s[i] = s1[i];
	}
	for (; s2[j] != '\0'; i++, j++)
	{
		s[i] = s2[j];
	}
	return s;
}

char* IntToString(int value) {
	int size = 0;
	int multiplier = 10;
	int temp = value;
	for (; temp != 0; size++)
	{
		temp = temp - temp % multiplier;
		multiplier *= 10;
	}

	char* str = malloc(size * sizeof(char) + 1);
	*(str + size) = '\0';
	multiplier = 10;
	temp = value;

	for (int i = size - 1; i >= 0; i--)
	{
		int _temp = 0;
		_temp = (temp % multiplier - temp % (multiplier / 10)) / (multiplier / 10);
		switch (_temp)
		{
		case 0:
			*(str + i) = 48;
			break;
		case 1:
			*(str + i) = 49;
			break;
		case 2:
			*(str + i) = 50;
			break;
		case 3:
			*(str + i) = 51;
			break;
		case 4:
			*(str + i) = 52;
			break;
		case 5:
			*(str + i) = 53;
			break;
		case 6:
			*(str + i) = 54;
			break;
		case 7:
			*(str + i) = 55;
			break;
		case 8:
			*(str + i) = 56;
			break;
		case 9:
			*(str + i) = 57;
			break;
		default:
			break;
		}
		multiplier *= 10;
	}

	return str;
}

int StringToInt(char* str) {
	int value = 0;
	for (int i = 0; *(str + i) != '\0'; i++)
	{
		switch (*(str + i))
		{
		case 48:
			value *= 10;
			break;
		case 49:
			value *= 10;
			value += 1;
			break;
		case 50:
			value *= 10;
			value += 2;
			break;
		case 51:
			value *= 10;
			value += 3;
			break;
		case 52:
			value *= 10;
			value += 4;
			break;
		case 53:
			value *= 10;
			value += 5;
			break;
		case 54:
			value *= 10;
			value += 6;
			break;
		case 55:
			value *= 10;
			value += 7;
			break;
		case 56:
			value *= 10;
			value += 8;
			break;
		case 57:
			value *= 10;
			value += 9;
			break;
		default:
			break;
		}
	}
	return value;
}