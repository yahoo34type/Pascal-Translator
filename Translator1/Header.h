#pragma once
#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <algorithm>
using namespace std;
const int MAXLINE = 500;
const int MAX = 500;
const int ERRMAX = 5;
const int maxint = 32767;
const int MAX_IDENT = 50;
const char* FILENAME = "C:\\Users\\YV\\Desktop\\NEW\\� ������� �����\\�����\\Translator1\\Source2.txt";
const char* FILENAME2 = "C:\\Users\\YV\\Desktop\\NEW\\� ������� �����\\�����\\Translator1\\List.txt";
const char* FILENAME3 = "C:\\Users\\YV\\Desktop\\NEW\\� ������� �����\\�����\\Translator1\\ErrList.txt";
struct textposition
{
	unsigned linenumber; /*����� ������ */
	unsigned charnumber; /*����� �������
						 � ������ */
};
struct lineErrors
{
	struct textposition errorposition;
	unsigned errorcode;
} ErrList[ERRMAX];
char ch;						// ������� ����������� ������
textposition positionnow;		// ������� �������
short LastInLine;				// ����� ������� ������
char line[MAXLINE];				// ������� ������
ifstream IN(FILENAME);			// ������� ����
ofstream OUT(FILENAME2);		// �������� ����
ifstream ERIN(FILENAME3);		// ���� � ��������
short ErrInx;
short ErrorOverFlow;
int errcount = 1;				// ���-�� ������ ������� ������
char **itable = new char*[MAX];
int icount = 0;

