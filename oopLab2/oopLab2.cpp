#include "header.h"

int main()
{
	string fileIn = "input.txt";	//назва файлу введених даних (№1)
	string fileOut = "output.txt";	//назва кінцевого файлу (№2)
	choice(fileIn);					//введення даних у файл
	fileOutput(fileIn);				//виведення файлу №1
	fileCreate(fileIn, fileOut);	//створення файлу №2 відповідно до завдання
	fileOutput(fileOut);			//виведення файлу №2
	system("pause");
}