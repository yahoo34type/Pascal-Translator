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
const char* FILENAME = "C:\\Users\\YV\\Desktop\\NEW\\С чистого листа\\ФГиМТ\\Translator1\\Source2.txt";
const char* FILENAME2 = "C:\\Users\\YV\\Desktop\\NEW\\С чистого листа\\ФГиМТ\\Translator1\\List.txt";
const char* FILENAME3 = "C:\\Users\\YV\\Desktop\\NEW\\С чистого листа\\ФГиМТ\\Translator1\\ErrList.txt";
struct textposition
{
	unsigned linenumber; /*номер строки */
	unsigned charnumber; /*номер позиции
						 в строке */
};
struct lineErrors
{
	struct textposition errorposition;
	unsigned errorcode;
} ErrList[ERRMAX];
char ch;						// текущая сканируемая литера
textposition positionnow;		// текущая позиция
short LastInLine;				// длина текущей строки
char line[MAXLINE];				// текущая строка
ifstream IN(FILENAME);			// входной файл
ofstream OUT(FILENAME2);		// выходной файл
ifstream ERIN(FILENAME3);		// файл с ошибками
short ErrInx;
short ErrorOverFlow;
int errcount = 1;				// кол-во ошибок текущей строки
char **itable = new char*[MAX];
int icount = 0;

