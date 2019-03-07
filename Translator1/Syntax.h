#pragma once
#include "Lexical.h"
void accept(unsigned symbolexpected
/* код ожидаемого символа */)
{
	if (symbol == symbolexpected)
		nextsym();
	else error(symbolexpected, token);
}
void programme()
/* анализ конструкции <программа> */
{
	accept(programsy);
	accept(ident);
	accept(semicolon);
	block(); /* анализ конструкции <блок> */
	accept(point);
}
void block()
/* анализ конструкции <блок> */
{
	labelpart(); 
	constpart();
	typepart(); 
	varpart();
	procfuncpart(); 
	statementpart();
}
void constant()
{
	if (symbol == intc || symbol == charc || symbol == floatc || symbol == stringc || symbol == booleanc)
		nextsym();
	else
		error(50, token);
}
void whilestatement()
/* анализ конструкции <цикл с предусловием> */
{
	accept(whilesy); expression();
	accept(dosy); statement();
}
void forstatement()
/* анализ конструкции <цикл с параметром> */
{
	accept(forsy); accept(ident);
	accept(assign); expression();
	if (symbol == tosy || symbol == downtosy)
		nextsym();
	expression(); accept(dosy);
	statement();
}
void repeatstatement()
/* анализ конструкции <цикл с параметром> */
{
	accept(repeatsy);
	statement();
	while (symbol == semicolon)
	{
		nextsym();
		statement();
	}
	accept(untilsy); expression();
}
void compoundstatement()
/* анализ конструкции <составной оператор> */
{
	accept(beginsy); statement();
	while (symbol == semicolon)
	{
		nextsym(); statement();
	}
	accept(endsy);
}
void varpart()
/* анализ конструкции <раздел переменных> */
{
	if (symbol == varsy)
	{
		accept(varsy);
		do
		{
			vardeclaration();
			accept(semicolon);
		} while (symbol == ident);
	}
}
void vardeclaration()
/* анализ конструкции
<описание однотипных переменных> */
{
	accept(ident);
	while (symbol == comma)
	{
		nextsym();
		accept(ident);
	}
	accept(colon);
	type();
}
void type()
/* тип */
{
	switch (symbol)
	{
	case leftpar : //перечисл€емый
		simpletype();
		break;
	case intc:	//ограниченный
		simpletype();
		break;
	case charc:	//ограниченный
		simpletype();
		break;
	case ident: //простой
		simpletype();
		break;
	case arraysy: //регул€рный
		unpackedcompositetype();
		break;
	case recordsy:	//комбинированный
		unpackedcompositetype();
		break;
	case setsy:	// множественный
		unpackedcompositetype();
		break;
	case filesy: //файловый
		unpackedcompositetype(); 
		break;
	case packedsy:	//упакованный
		nextsym();
		unpackedcompositetype();
		break;
	case arrow:	//ссылочный
		nextsym();
		accept(ident);
		break;
	default:
		error(10, token);
	}
}
void simpletype()
{
	switch (symbol)
	{
	case leftpar: //перечисл€емый
		numtype();
		break;
	case intc:	//ограниченный
		limtype(1);
		break;
	case charc:	//ограниченный
		limtype(0);
		break;
	case ident: //простой
		break;
	}
}
void unpackedcompositetype()
{
	switch (symbol)
	{
	case arraysy: //регул€рный
		regtype();
		break;
	case recordsy:	//комбинированный
		combtype();
		break;
	case setsy:	// множественный
		multipletype();
		break;
	case filesy: //файловый
		break;
	}
}
void numtype()
{
	nextsym();
	accept(ident);
	while (symbol == comma)
	{
		nextsym();
		accept(ident);
	}
	accept(rightpar);
}
void multipletype()
{
	nextsym();
	accept(ofsy);
	simpletype();
}
void limtype(bool flag)
{
	nextsym();
	accept(twopoints);
	if (flag)
		accept(intc);
	else
		accept(charc);
}
void regtype()
{
	nextsym();
	accept(lbracket);
	simpletype();
	while (symbol == comma)
	{
		nextsym();
		simpletype();
	}
	accept(rbracket);
	accept(ofsy);
	type();
}
void combtype()
{
	nextsym();
	fieldlist();
	accept(endsy);
}
void fieldlist()
{
	if (symbol == ident)
	{
		recordsection();
		while (symbol == semicolon)
		{
			nextsym();
			recordsection();
		}
		if (symbol == casesy)
		{
			variativesection();
		}
	}
	else if (symbol == casesy)
	{
		variativesection();
	}
	else
		cout << "Some weird ass shit happened there:C\n";
}
void variativesection()
{
	nextsym();
	accept(ident);
	accept(colon);
	accept(ident);
	accept(ofsy);
	variant();
	while (symbol == semicolon)
	{
		nextsym();
		variant();
	}
}
void variant()
{
	constant();
	while (symbol == comma)
	{
		nextsym();
		constant();
	}
	accept(colon);
	accept(leftpar);
	fieldlist();
	accept(rightpar);
}
void recordsection()
{
	accept(ident);
	while (symbol == comma)
	{
		nextsym();
		accept(ident);
	}
	accept(colon);
}
void variable()
/* анализ конструкции <переменна€> */
{
	accept(ident);
	while (symbol == lbracket || symbol == point
		|| symbol == arrow)
		switch (symbol)
		{
		case lbracket:
			nextsym(); expression();
			while (symbol == comma)
			{
				nextsym(); expression();
			}
			accept(rbracket);
			break;
		case point:
			nextsym(); accept(ident);
			break;
		case arrow:
			nextsym();
			break;
		}
}
void ifstatement()
/* анализ конструкции <условный оператор> */
{
	accept(ifsy); expression();
	accept(thensy); statement();
	if (symbol == elsesy)
	{
		nextsym();
		statement();
	}
}
void casestatement()
{
	accept(casesy);
	expression();
	accept(ofsy);
	caseelement();
	while (symbol == semicolon)
	{
		nextsym();
		caseelement();
	}
	accept(endsy);
}
void caseelement()
{
	if (symbol != endsy)
	{
		constant();
		while (symbol == comma)
		{
			nextsym();
			constant();
		}
		accept(colon);
		statement();
	}
}
void labelpart()
/* анализ конструкции <раздел меток> */
{
	if (symbol == labelsy)
	{
		nextsym();
		accept(ident);
		while (symbol == comma)
		{
			nextsym();
			accept(ident);
		}
		accept(semicolon);
	}
}
void statementpart()
/* раздел операторов */
{
	accept(beginsy);
	statement();
	while (symbol == semicolon)
	{
		nextsym();
		statement();
	}
	accept(endsy);
}
void statement()
/* раздел оператора */
{
	if (symbol != endsy)
	{
		if (symbol == ident)
		{
			nextsym();
			if (symbol == colon)
			{
				nextsym();
				unmarkedstatement();
			}
			else 
			{
				switch (symbol)
				{
				case assign:
					nextsym();
					expression();
					break;
				case leftpar:
					nextsym();
					fparameter();
					while (symbol == comma)
					{
						nextsym();
						fparameter();
					}
					accept(rightpar);
					break;
				default:
					error(322, token);
					break;
				}
			}
		}
		else
		{
			switch (symbol)
			{
			case gotosy:
				nextsym();
				accept(ident);
				break;
			case ifsy:
				nextsym();
				ifstatement();
				break;
			case beginsy:
				nextsym();
				statement();
				while (symbol == semicolon)
				{
					nextsym();
					statement();
				}
				accept(endsy);
				break;
			case casesy:
				nextsym();
				casestatement();
				break;
			case whilesy:
				cyclestatement();
				break;
			case repeatsy:
				cyclestatement();
				break;
			case forsy:
				cyclestatement();
				break;
			case withsy:
				connstatement();
				break;
			default:
				error(322, token);
				break;
			}
		}
	}
	else
	{
		nextsym();
	}
}
void unmarkedstatement()
/* раздел оператора */
{
	if (symbol != endsy)
	{
		if (symbol == ident)
		{
			nextsym();
			switch (symbol)
			{
			case assign:
				nextsym();
				expression();
				break;
			case leftpar:
				nextsym();
				fparameter();
				while (symbol == comma)
				{
					nextsym();
					fparameter();
				}
				accept(rightpar);
				break;
			default:
				error(322, token);
				break;
			}
		}
		else
		{
			switch (symbol)
			{
			case gotosy:
				nextsym();
				accept(ident);
				break;
			case ifsy:
				nextsym();
				ifstatement();
				break;
			case beginsy:
				nextsym();
				statement();
				while (symbol == semicolon)
				{
					nextsym();
					statement();
				}
				accept(endsy);
				break;
			case casesy:
				nextsym();
				casestatement();
				break;
			case whilesy:
				cyclestatement();
				break;
			case repeatsy:
				cyclestatement();
				break;
			case forsy:
				cyclestatement();
				break;
			case withsy:
				connstatement();
				break;
			default:
				error(322, token);
				break;
			}
		}
	}
	else
	{
		nextsym();
	}
}
void fparameter()
{
	if (symbol == ident)
		nextsym();
	else
		expression();
}
void connstatement()
{
	accept(withsy);
	variable();
	while (symbol == comma)
	{
		nextsym();
		variable();
	}
	accept(dosy);
	statement();
}
void cyclestatement()
{
	switch (symbol)
	{
	case forsy:
		forstatement();
		break;
	case repeatsy:
		repeatstatement();
		break;
	case whilesy:
		whilestatement();
		break;
	}
}
void expression()
{
	simpleexpression();
	if (symbol == equal || symbol == latergreater || symbol == later || symbol == laterequal || symbol == greaterequal ||
		symbol == greater || symbol == insy)
	{
		nextsym();
		simpleexpression();
	}
}
void simpleexpression()
{
	if (symbol == minus || symbol == plus)
		nextsym();
	addend();
	while (symbol == plus || symbol == minus || symbol == orsy)
	{
		nextsym();
		addend();
	}
}
void addend()
{
	mult();
	while (symbol == star || symbol == slash || symbol == divsy || symbol == modsy || symbol == andsy)
	{
		nextsym();
		mult();
	}
}
void mult()
{
	switch (symbol)
	{
	case ident:
		nextsym();
		if (symbol == leftpar)
		{
			nextsym();
			if (symbol == ident)
			{
				nextsym();
				while (symbol == comma)
				{
					nextsym();
					if (symbol == ident)
					{
						nextsym();
					}
					else
					{
						expression();
					}
				}
			}
			else
			{
				expression();
				while (symbol == comma)
				{
					nextsym();
					if (symbol == ident)
					{
						nextsym();
					}
					else
					{
						expression();
					}
				}
			}
			accept(rightpar);
		}
		break;
	case intc:
		if (nmb_int >= 0)
		{
			nextsym();
			accept(leftpar);
			expression();
			accept(rightpar);
		}
		else
		{
			error(50, token);
		}
		break;
	case stringc:
		nextsym();
		accept(leftpar);
		expression();
		accept(rightpar);
		break;
	case charc:
		nextsym();
		accept(leftpar);
		expression();
		accept(rightpar);
		break;
	case nilsy:
		nextsym();
		accept(leftpar);
		expression();
		accept(rightpar);
		break;
	case lbracket:
		nextsym();
		expression();
		if (symbol == twopoints)
			expression();
		while (symbol == comma)
		{
			nextsym();
			expression();
			if (symbol == twopoints)
				expression();
		}
		accept(rbracket);
		break;
	case notsy:
		nextsym();
		mult();
		break;
	default:
		error(322, token);
	}
}