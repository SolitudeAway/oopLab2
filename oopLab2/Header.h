#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//структура запису розкладу руху поїздів
struct TTimeTable
{
	int number;			//номер рейсу
	char direction[30];	//напрямок руху
	int hourDep;		//година відправлення
	int minuteDep;		//хвилина відправлення
	int hourArr;		//година прибуття
	int minuteArr;		//хвилина прибуття
};

void choice(string);			  //вибір між створенням і доповненням файлу введених даних
void fileInput(ofstream&);		  //введення файлу
TTimeTable structInput();		  //введення окремого запису розкладу руху
void fileOutput(string);		  //виведення файлу
void fileCreate(string, string);  //створення файлу відповідно до задачі
bool timeCheck(TTimeTable);		  //перевірка часу структури на відповідність умові задачі
