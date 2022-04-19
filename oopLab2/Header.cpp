#include "Header.h"

//���� �� ���������� � ����������� ����� �������� �����
void choice(string fileName)
{
	cout << "Enter 1 for new file or 2 to add to previous: ";
	bool flag = true;
	char s;
	ofstream fileOut;	//�������� ������ �� ����� �����
	while (flag)
	{
		flag = false;
		cin >> s;
		switch (s)
		{
		case '1': //�������� �������� �����
		{
			fileOut.open(fileName, ios::binary);
			fileInput(fileOut);
			break;
		}
		case '2': //�������� �������� ����� �� ������� � ����� �����
		{
			fileOut.open(fileName, ios::binary | ios::app);
			fileInput(fileOut);
			break;
		}
		default: //������� ������������ �����
		{
			cout << "Wrong input. Please, try again: ";
			flag = true;
		}
		}
	}
	fileOut.close();	//�������� ������ �� ����� �����
}

//�������� �����
void fileInput(ofstream& fileOut)
{
	char s;
	bool flag = true;
	while (flag)
	{
		TTimeTable data = structInput(); //�������� �������� ������ �������� ����
		fileOut.write((char*)&data, sizeof(TTimeTable)); //����� ��������� � ����
		cout << "Enter + if you want to continue or any other symbol if don't: ";
		cin >> s;
		if (s != '+')
			flag = false;	//��������� ��������, ���� �������� ������ �� ����		
	}
}

//�������� �������� ������ �������� ����
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
	//����������� ������� "12:34" � ��� ������� �����
	data.hourDep = stoi(str.substr(0, str.find(':')));
	data.minuteDep = stoi(str.substr(str.find(':') + 1, 2));
	cout << "Input time of arrival in format \"12:34\": ";
	cin.ignore();
	cin >> str;
	//����������� ������� "12:34" � ��� ������� �����
	data.hourArr = stoi(str.substr(0, str.find(':')));
	data.minuteArr = stoi(str.substr(str.find(':') + 1, 2));

	return data;
}

//��������� �����
void fileOutput(string fileName)
{
	TTimeTable data;
	ifstream fileOut(fileName, ios::binary); //�������� �������� ����� �� �������
	int i = 1;
	cout << "\nFile " << fileName << '\n';
	//������������ ���������� �����
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

//��������� ����� �������� �� ������
void fileCreate(string fileInName, string fileOutName)
{
	TTimeTable data;
	ifstream fileIn(fileInName, ios::binary);	//�������� ����� �������� ����� �� �������
	ofstream fileOut(fileOutName, ios::binary);	//�������� ����� ���������� �� �����
	while (fileIn.read((char*)&data, sizeof(TTimeTable)))
	{
		if (timeCheck(data)) //���� ���������� ����� �������� �� ������
		{
			fileOut.write((char*)&data, sizeof(TTimeTable)); //����� ��������� � ���� ����������
		}
	}
	fileIn.close();
	fileOut.close();
}

//�������� ���� ��������� �� ���������� ���� ������
bool timeCheck(TTimeTable data)
{
	bool flag;
	float dep = data.hourDep + float(data.minuteDep) / 100;
	float arr = data.hourArr + float(data.minuteArr) / 100;
	if (dep < arr) //���� ����������� � �������� ����������� � ����� ������ ���
		flag = (dep <= 10 && arr <= 10) || (dep >= 18 && arr >= 18);
	else		   //���� ����������� � �������� ����������� � ��� ��
		flag = dep >= 18 && arr <= 10;
	return flag;
}