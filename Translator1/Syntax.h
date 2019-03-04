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