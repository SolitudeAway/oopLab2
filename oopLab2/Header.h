#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//��������� ������ �������� ���� �����
struct TTimeTable
{
	int number;			//����� �����
	char direction[30];	//�������� ����
	int hourDep;		//������ �����������
	int minuteDep;		//������� �����������
	int hourArr;		//������ ��������
	int minuteArr;		//������� ��������
};

void choice(string);			  //���� �� ���������� � ����������� ����� �������� �����
void fileInput(ofstream&);		  //�������� �����
TTimeTable structInput();		  //�������� �������� ������ �������� ����
void fileOutput(string);		  //��������� �����
void fileCreate(string, string);  //��������� ����� �������� �� ������
bool timeCheck(TTimeTable);		  //�������� ���� ��������� �� ���������� ���� ������
