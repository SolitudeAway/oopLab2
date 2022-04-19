#include "Header.h"

//вибір між створенням і доповненням файлу введених даних
void choice(string fileName)
{
	cout << "Enter 1 for new file or 2 to add to previous: ";
	bool flag = true;
	char s;
	ofstream fileOut;	//відкриття потоку на запис файлу
	while (flag)
	{
		flag = false;
		cin >> s;
		switch (s)
		{
		case '1': //відкриття бінарного файлу
		{
			fileOut.open(fileName, ios::binary);
			fileInput(fileOut);
			break;
		}
		case '2': //відкриття бінарного файлу на дозапис в кінець файлу
		{
			fileOut.open(fileName, ios::binary | ios::app);
			fileInput(fileOut);
			break;
		}
		default: //обробка некоректного вводу
		{
			cout << "Wrong input. Please, try again: ";
			flag = true;
		}
		}
	}
	fileOut.close();	//закриття потоку на запис файлу
}

//введення файлу
void fileInput(ofstream& fileOut)
{
	char s;
	bool flag = true;
	while (flag)
	{
		TTimeTable data = structInput(); //введення окремого запису розкладу руху
		fileOut.write((char*)&data, sizeof(TTimeTable)); //запис структури в файл
		cout << "Enter + if you want to continue or any other symbol if don't: ";
		cin >> s;
		if (s != '+')
			flag = false;	//закінчення введення, якщо введений символ не плюс		
	}
}

//введення окремого запису розкладу руху
TTimeTable structInput()
{
	cout << endl;
	TTimeTable data;
	string str;
	cout << "Input the number of train: ";
	cin >> data.number;
	cin.ignore();
	cout << "Input the direction of train: ";
	cin >> data.direction;
	cout << "Input time of departure in format \"12:34\": ";
	cin.ignore();
	cin >> str;
	//переведення формату "12:34" в два окремих числа
	data.hourDep = stoi(str.substr(0, str.find(':')));
	data.minuteDep = stoi(str.substr(str.find(':') + 1, 2));
	cout << "Input time of arrival in format \"12:34\": ";
	cin.ignore();
	cin >> str;
	//переведення формату "12:34" в два окремих числа
	data.hourArr = stoi(str.substr(0, str.find(':')));
	data.minuteArr = stoi(str.substr(str.find(':') + 1, 2));

	return data;
}

//виведення файлу
void fileOutput(string fileName)
{
	TTimeTable data;
	ifstream fileOut(fileName, ios::binary); //відкриття бінарного файлу на читання
	int i = 1;
	cout << "\nFile " << fileName << '\n';
	//поструктурне зчитування файлу
	while (fileOut.read((char*)&data, sizeof(TTimeTable)))
	{
		cout << "#" << setw(5) << left << i << right
			<< setw(5) << data.number
			<< setw(30) << data.direction << "   "
			<< setw(2) << setfill('0') << data.hourDep
			<< ':' << setw(2) << data.minuteDep << "  "
			<< setw(2) << data.hourArr
			<< ':' << setw(2) << data.minuteArr << setfill(' ') << "\n";
		i++;
	}
	fileOut.close();
}

//створення файлу відповідно до задачі
void fileCreate(string fileInName, string fileOutName)
{
	TTimeTable data;
	ifstream fileIn(fileInName, ios::binary);	//відкриття файлу введених файлів на читання
	ofstream fileOut(fileOutName, ios::binary);	//відкриття файлу результату на запис
	while (fileIn.read((char*)&data, sizeof(TTimeTable)))
	{
		if (timeCheck(data)) //якщо виконується умова відповідно до задачі
		{
			fileOut.write((char*)&data, sizeof(TTimeTable)); //запис структури у файл результатів
		}
	}
	fileIn.close();
	fileOut.close();
}

//перевірка часу структури на відповідність умові задачі
bool timeCheck(TTimeTable data)
{
	bool flag;
	float dep = data.hourDep + float(data.minuteDep) / 100;
	float arr = data.hourArr + float(data.minuteArr) / 100;
	if (dep < arr) //якщо відправлення і прибуття відбуваються в межах одного дня
		flag = (dep <= 10 && arr <= 10) || (dep >= 18 && arr >= 18);
	else		   //якщо відправлення і прибуття відбуваються в різні дні
		flag = dep >= 18 && arr <= 10;
	return flag;
}