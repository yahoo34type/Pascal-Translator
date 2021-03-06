#pragma once
#include "InOut.h"
#include "Symbols.h"
unsigned symbol; /* ��� ������� */
struct textposition token; /* ������� ������� */
int nmb_int; /* ����� ��������� */
long double nmb_float; /* ������������ ��������� */
char one_symbol; /* ���������� ��������� */
char nmb_str[MAX]; /* ��������� ��������� */
bool nmb_bool;
unsigned hashresult; /* hash-������� ��� ��������� ����� */
char *addrname; /* ����� ����� � ������� ���� */
char name[MAX_IDENT];
unsigned lname;
bool lcommentfound = false;
char **nlist = new char*;
int n = 0;
int len = 0;
bool negativeflag = false; bool tpflg = false;
bool nextsym()
{
	if (tpflg)
	{
		token.charnumber = positionnow.charnumber - 1;
		token.linenumber = positionnow.linenumber;
		symbol = twopoints;
		tpflg = false;
		nextch();
	}
	else
	{
	if (!lcommentfound)
		if (!IN.eof() || positionnow.charnumber != LastInLine)
		{
			while ((ch == ' ' || ch == '\t') && (!IN.eof() || positionnow.charnumber < LastInLine))
				nextch();
			if (IN.eof() && positionnow.charnumber == (LastInLine))
			{
				symbol = eofile;
				return 0;
			}
			else
			{
				token.linenumber = positionnow.linenumber;
				token.charnumber = positionnow.charnumber;
				switch (ch)
				{
				case '\'': nextch();  len = 0;
					if (ch != '\'')
					{
						char s = ch;
						nmb_str[len++] = ch;
						nextch();
						if (ch == '\'')
						{
							one_symbol = s;
							symbol = charc;
							cout << "One char: " << s << endl;
						}
						else
						{
							while (ch != '\'' && (positionnow.charnumber != LastInLine))
							{
								nmb_str[len++] = ch;
								nextch();
							}
							if (ch == '\'')
							{
								symbol = stringc;
								nmb_str[len] = '\0';
								cout << "string: " << nmb_str << endl;
							}
							else
							{
								error(76, positionnow);
							}
						}

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
					nextch(); nextsym();
					break;
				case '&':
					error(6, positionnow);
					nextch(); nextsym();
					break;
				case '%':
					error(6, positionnow);
					nextch(); nextsym();
					break;
				case '$':
					error(6, positionnow);
					nextch(); nextsym();
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
				case '-': symbol = minus; nextch();
					/*if (ch >= '0' && ch <= '9')
					{
						negativeflag = true;
						nextsym();
					}
					else
					{
						symbol = minus;
					}*/
					break;
				case '*': nextch(); //+
					if (ch == ')')
					{
						symbol = rcomment; nextch();
					}
					else
						symbol = star;
					break;
				case '/':
					nextch();
					if (ch == '/')
					{
						symbol = olcomment;
						int cn = positionnow.linenumber;
						while (positionnow.linenumber == cn)
							nextch();
						nextsym();
					}
					else
					{
						symbol = slash;
					}
					break;
				case '=': symbol = equal;//+
					nextch();
					break;
				case '(': nextch(); //+
					if (ch == '*')
					{
						symbol = lcomment;
						nextch();
						lcommentfound = true;
						nextsym();
					}
					else
						symbol = leftpar;
					break;
				case ')': symbol = rightpar;//+
					nextch();
					break;
				case '{': symbol = flpar; //+
					while (ch != '}' && (!IN.eof() || positionnow.charnumber != LastInLine))
						nextch();
					if (IN.eof() && positionnow.charnumber == LastInLine)
						error(86, positionnow);
					nextsym();
					break;
				case '}': symbol = frpar;//+
					nextch();
					nextsym();
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
						bool efound = false; bool ejustfound = false; bool pjustfound = false;
						bool errflag = false;
						string num = "";
						while (ch >= '0' && ch <= '9' || ch == '.' && !(pfound) || ch == 'e' && !(efound) || ch == '-' && ejustfound || ch == '+' && ejustfound)
						{

							num += ch;
							if (ch == '.' && !(pfound))
							{
								pfound = true; pjustfound = true;
							}
							else if (ch == 'e' && !(efound))
							{
								efound = true;
								ejustfound = true;
								pjustfound = false;
							}
							else if (ch == '-' && ejustfound || ch == '+' && ejustfound)
							{
								ejustfound = false; pjustfound = false;
							}
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
								ejustfound = false;
								pjustfound = false;
							}
							nextch();
						}
						if (pjustfound && ch == '.')
						{
							nmb_int = stoi(num);
							symbol = intc;
							tpflg = true;
							cout << "Number: " << nmb_int << endl;
						}
						/*if (ch != ' ' && ch != ';')
						{
							error(1, positionnow); nextch();
						}*/
						else
							if (!pfound && !efound)
							{
								symbol = intc;
								if (errflag)
								{
									error(203, positionnow);
								}
								else
								{
									if (negativeflag)
										nmb_int = stoi(num);
									cout << "Number: " << nmb_int << endl;
								}
							}
							else
							{
								nmb_float = stold(num);
								if (nmb_float > 0 && nmb_float < 1.5e-45 || nmb_float > 3.4e38 || nmb_float < 0 && nmb_float > -1.5e-45 || nmb_float < -3.4e38)
									error(50, positionnow);
								else
								{
									symbol = floatc;
									cout << "Num: " << nmb_float << endl;
								}
							}
						nmb_int = 0;
						nmb_float = 0;
						num = "";
						negativeflag = false;
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
						if (name == "false" || name == "true")
						{
							symbol = booleanc;
							if (name == "false")
								nmb_bool = false;
							else
								nmb_bool = true;
							cout << "bool value: " << nmb_bool << endl;
						}
						else if (symbol == ident)
						{
							bool found = 0;
							for (int i = 0; i < icount && !found; i++)
							{
								if (strcmp(itable[i], name) == 0)
								{
									found = 1;
									addrname = itable[i];
								}
							}
							if (!found)
							{
								itable[icount] = new char[MAX];
								strcpy_s(itable[icount], MAX, name);
								addrname = itable[icount++];
							}
							cout << "id: " << addrname << endl;
						}
					}
					else
					{
						cout << "unknown symbol: " << ch << endl;
						error(6, positionnow);
						nextch();
					}
				}
				}
				return 1;
			}
		}
		else
		{
			symbol = eofile;
			return 0;
		}
	else
	{
		if (!IN.eof() || positionnow.charnumber != LastInLine)
		{
			bool rcommentfound = 0;
			while (!rcommentfound && (!IN.eof() || positionnow.charnumber != LastInLine))
			{
				while (ch != '*' && (!IN.eof() || positionnow.charnumber != LastInLine))
				{
					nextch();
				}
				token.linenumber = positionnow.linenumber;
				token.charnumber = positionnow.charnumber;
				if (!IN.eof() || positionnow.charnumber != LastInLine)
					nextch();
				if (ch == ')')
				{
					symbol = rcomment;
					nextch();
					rcommentfound = 1;
					lcommentfound = 0;
					nextsym();
				}
			}
			if (!IN.eof() || positionnow.charnumber != LastInLine)
				return 1;
			else
			{
				error(86, positionnow);
				return 0;
			}
		}
		else
		{
			error(86, positionnow);
			return 0;
		}
	}
	cout << symbol << " in position " << token.linenumber << "," << token.charnumber << "\n";
}
}