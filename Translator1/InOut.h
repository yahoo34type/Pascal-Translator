#pragma once
#include "Header.h"
#include "errDesc.h"
void ListThisLine()
{
	OUT << "  " << setw(2) << setfill('0') << positionnow.linenumber << "  ";
	for (int i = 0; i < LastInLine; i++)
	{
		if (line[i] == '\t')
			line[i] = ' ';
	}
	OUT << line << endl;
}
void ListErrors()
{
	cout << "Line:" << positionnow.linenumber<< ",errors:" << ErrInx << endl;
	for (int i=1; i<=ErrInx; i++)
	{
		//if (v.errorposition.linenumber == positionnow.linenumber)
		{
			OUT << "**" << setw(2) << setfill('0') << errcount++; 
			OUT << "**";
			for (int j = 1; j < ErrList[i].errorposition.charnumber; j++)
				OUT << " ";
			OUT << "^ ошибка код " << ErrList[i].errorcode << endl;
			OUT << "******" << errorDescription[ErrList[i].errorcode] << endl;
		}
	}
}
void ReadNextLine()
{
	memset(&line[0], 0, sizeof(line));
	IN.getline(line, MAXLINE);
	line[strlen(line)] = ' ';
	LastInLine = strlen(line);
	ErrInx = 0;
}
bool nextch() // сканирование следующего символа
{
	{
		if (positionnow.charnumber == LastInLine)
		{
			ListThisLine();
			if (ErrInx > 0) //an
				ListErrors();
			ReadNextLine();
			positionnow.linenumber++;
			positionnow.charnumber = 1;
		}
		else
		{
			if (positionnow.charnumber < LastInLine)
				positionnow.charnumber++;
		}
		ch = line[positionnow.charnumber - 1];
		return 1;
	}
}
void error(unsigned errorcode,textposition position)
{
	
	if (ErrInx == ERRMAX)
		ErrorOverFlow = 1;
	else
	{
		cout << "Adding an error\nPositionnow:" << position.linenumber << "," << position.charnumber << "; errorcode: " << errorcode <<endl;
		++ErrInx;
		ErrList[ErrInx].errorcode = errorcode;
		ErrList[ErrInx].errorposition.linenumber
			= position.linenumber;
		ErrList[ErrInx].errorposition.charnumber
			= position.charnumber;
	}
}