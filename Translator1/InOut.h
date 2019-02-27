#pragma once
#include "Header.h"
#include "errDesc.h"
void ListThisLine()
{
	OUT << "  " << setw(2) << setfill('0') << positionnow.linenumber << "  ";
	OUT << line << endl;
}
void ImportErrors()
{
	char *s = new char[MAXLINE];
		string temp1 = "", temp2 = "", temp3 = "";
	int cur = 0;
	while (!ERIN.eof())
	{
		ERIN.getline(s, MAXLINE);
		while (s[cur] != ',')
			temp1 += s[cur++];
		cur++;
		while (s[cur] != ',')
			temp2 += s[cur++];
		cur++;
		while (cur < strlen(s))
			temp3 += s[cur++];
		textposition t = { stoi(temp1),stoi(temp2) };
		lineErrors t1 = { t,stoi(temp3) };
		errLst.push_back(t1);
		cur = 0;
		temp1 = ""; temp2 = ""; temp3 = "";
	}
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
bool GetErrors()
{
	for each (lineErrors v in ErrList)
	{
		if (v.errorposition.linenumber == positionnow.linenumber)
		{
			return 1;
		}
	}
	return 0;
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
		cout << "Adding an error\nPositionnow:" << position.linenumber << "," << position.charnumber << endl;
		++ErrInx;
		ErrList[ErrInx].errorcode = errorcode;
		ErrList[ErrInx].errorposition.linenumber
			= position.linenumber;
		ErrList[ErrInx].errorposition.charnumber
			= position.charnumber;
	}
}