#pragma once
#include "Header.h"
#include "InOut.h"
#include "Symbols.h"
unsigned symbol; /* код символа */
struct textposition token; /* позиция символа */
int nmb_int; /* целая константа */
float nmb_float; /* вещественная константа */
char one_symbol; /* символьная константа */
unsigned hashresult; /* hash-функция для заданного имени */
char *addrname; /* адрес имени в таблице имен */
char name[MAX_IDENT];
unsigned lname;

bool nextsym()
{
	if (!IN.eof() || positionnow.charnumber != LastInLine)
	{
		while (ch == ' ') nextch();
		token.linenumber = positionnow.linenumber;
		token.charnumber = positionnow.charnumber;
		switch (ch)
		{
		case '\'': nextch();
			if (ch != '\'')
			{
				nextch();
				if (ch == '\'')
					symbol = charc;
				else
					error(1, positionnow);
			}
			else
				error(1, positionnow);
			nextch();
			break;
		case '<': nextch(); //+
			if (ch == '=')
			{
				symbol = laterequal; nextch();
			}
			else
				if (ch == '>')
				{
					symbol = latergreater; nextch();
				}
				else
					symbol = later;
			break;
		case '>': nextch(); //+
			if (ch == '=')
			{
				symbol = greaterequal; nextch();
			}
			else
				symbol = greater;
			break;
		case '?':
			error(6, positionnow);
			nextch();
			break;
		case '&':
			error(6, positionnow);
			nextch();
			break;
		case '%':
			error(6, positionnow);
			nextch();
			break;
		case '$':
			error(6, positionnow);
			nextch();
			break;
		case ':': nextch(); //+
			if (ch == '=')
			{
				symbol = assign; nextch();
			}
			else
				symbol = colon;
			break;
		case '+': symbol = plus; //+
			nextch();
			break;
		case '-': symbol = minus;//+
			nextch();
			break;
		case '*': nextch(); //+
			if (ch == ')')
			{
				symbol = rcomment; nextch();
			}
			else
				symbol = star;
			break;
		case '/': symbol = slash;//+
			nextch();
			break;
		case '=': symbol = equal;//+
			nextch();
			break;
		case '(': nextch(); //+
			if (ch == '*')
			{
				symbol = lcomment; nextch();
			}
			else
				symbol = leftpar;
			break;
		case ')': symbol = rightpar;//+
			nextch();
			break;
		case '{': symbol = flpar;//+
			nextch();
			break;
		case '}': symbol = frpar;//+
			nextch();
			break;
		case '[': symbol = lbracket;//+
			nextch();
			break;
		case ']': symbol = rbracket;//+
			nextch();
			break;
		case '.': nextch(); //+
			if (ch == '.')
			{
				symbol = twopoints; nextch();
			}
			else
				symbol = point;
			break;
		case ',': symbol = comma;//+
			nextch();
			break;
		case '^': symbol = arrow;//+
			nextch();
			break;
		case ';': symbol = semicolon;//+
			nextch();
			break;
		default:
		{
			if (ch >= '0' && ch <= '9')
			{
				bool pfound = false;
				bool efound = false; bool ejustfound = false;
				bool errflag = false;
				nmb_int = 0;
				while (ch >= '0' && ch <= '9' || ch == '.' && !(pfound) || ch == 'e' && !(efound) || ch == '-' && ejustfound)
				{
					if (ch == '.' && !(pfound))
					{
						pfound = true;
						nextch();
					}
					else if (ch == 'e' && !(efound))
					{
						efound = true;
						ejustfound = true;
						nextch();
					}
					else if (ch == '-' && ejustfound)
						ejustfound = false;
					if (!efound && !pfound)
					{
						int digit = ch - '0';
						if (nmb_int < maxint / 10 || (nmb_int == maxint / 10 && digit <= maxint % 10))
							nmb_int = 10 * nmb_int + digit;
						else
						{
							errflag = true;
							nmb_int = 0;
						}
					}
					nextch();
				}
				if (ch != ' ' && ch != ';')
				{
					error(1, positionnow); nextch();
				}
				else if (!pfound && !efound)
				{
					symbol = intc;
					if (errflag)
						error(203, positionnow);
				}
				else
				{
					symbol = floatc;
				}


			}
			else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			{
				lname = 0;
				while (((ch >= 'a' && ch <= 'z') ||
					(ch >= 'A' && ch <= 'Z') ||
					(ch >= '0' && ch <= '9')) &&
					lname < MAX_IDENT)
				{
					name[lname++] = ch;
					nextch();
				}
				name[lname] = '\0';
				strcpy_s(keywords[last[lname]].namekey, name);
				int i = last[lname - 1] + 1;
				while (strcmp(keywords[i].namekey, name) != 0)
					i++;
				symbol = keywords[i].codekey;
			}
		}
		}
		return 1;
	}
	else
		return 0;
}