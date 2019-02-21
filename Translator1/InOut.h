#pragma once
#include "Header.h"
#include "errDesc.h"

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
char ch;
textposition positionnow;
short LastInLine;
char line[MAXLINE];
ifstream IN(FILENAME);
ofstream OUT(FILENAME2);
ifstream ERIN(FILENAME3);
short ErrInx;
short ErrorOverFlow;
vector<lineErrors> errLst;
int errcount = 1;
void ListThisLine()
{
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
	for each (lineErrors v in errLst)
	{
		if (v.errorposition.linenumber == positionnow.linenumber)
		{
			OUT << "**" << setw(2) << setfill('0') << errcount++; 
			OUT << "**";
			for (int i = 1; i < v.errorposition.charnumber; i++)
				OUT << " ";
			OUT << "^ ������ ��� " << v.errorcode << endl;
			OUT << "******" << errorDescription[v.errorcode] << endl;
		}
	}
}
bool GetErrors()
{
	for each (lineErrors v in errLst)
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
	IN.getline(line, MAXLINE);
	LastInLine = strlen(line);
}
bool nextch(char &x)
{
	if ((!IN.eof() || !(positionnow.charnumber > LastInLine)))
	{
		if (positionnow.charnumber == LastInLine)
		{
			ListThisLine();
			if (GetErrors()) //an
				ListErrors();
			ReadNextLine();
			positionnow.linenumber++;
			positionnow.charnumber = 1;
		}
		else
		{
			positionnow.charnumber++;
		}
		x = line[positionnow.charnumber];
		return 1;
	}
	else
		return 0;
}
void error(unsigned errorcode,textposition position)
{
	if (ErrInx = ERRMAX)
		ErrorOverFlow = 1;
	else
	{
		++ErrInx;
		ErrList[ErrInx].errorcode = errorcode;
		ErrList[ErrInx].errorposition.linenumber
			= position.linenumber;
		ErrList[ErrInx].errorposition.charnumber
			= position.charnumber;
	}
}
void work()
{
	ImportErrors();
	positionnow.linenumber = 1;
	positionnow.charnumber = 1;
	ReadNextLine();
	OUT.close();
	char next;
	while (nextch(next))
		cout << next;
}