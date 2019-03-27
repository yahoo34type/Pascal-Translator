#pragma once
#include "Lexical.h"
#include "Syntaxh.h"
#include "StartFollow.h"
bool ff = false;
void idknextsym()
{
	//nextsym();
}
bool belong(unsigned symbol, unsigned followers[])
{
	bool res;
	for (int i = 1; i <= followers[0]; i++)
		if (followers[i] == symbol)
			return 1;
	return 0;
}
void dis(unsigned one[], unsigned two[], unsigned *&res)
{
	res = new unsigned[50];
	res[0] = 0;
	for (int i = 1; i <= one[0]; i++)
		if (!belong(one[i], res))
		{
			res[++res[0]] = one[i];
		}
	for (int i = 1; i <= two[0]; i++)
		if (!belong(two[i], res))
		{
			res[++res[0]] = two[i];
		}
}
void skipto(unsigned followers[])
{
	while (!belong(symbol, followers) && (!IN.eof() || positionnow.charnumber != LastInLine))
	{
		nextsym(); //cout << "lul\n";
	}
}
void skipto2(unsigned starters[], unsigned followers[])
{
	while (!belong(symbol, starters) && !belong(symbol, followers) && (!IN.eof() || positionnow.charnumber != LastInLine))
	{
		nextsym();
	}
}
void accept(unsigned symbolexpected
/* код ожидаемого символа */)
{
	cout << "Waiting: " << symbolexpected << ", Symbol: " << symbol << endl;
	if (symbol == symbolexpected)
	{
		nextsym();
	}
	else 
	{ 
		error(symbolexpected, token); 
		idknextsym(); 
	}
}
void block(unsigned *followers)
/* анализ конструкции <блок> */
{
	unsigned *s;
	if (!belong(symbol, codes_block))
	{
		error(18, token);
		skipto2(codes_block, followers);
	}
	if (belong(symbol, codes_block))
	{
		labelpart();
		dis(codes_typepart, followers, s);
		constpart(s);
		dis(codes_varpart, followers, s);
		typepart(s);
		dis(codes_procfuncpart, followers, s);
		varpart(s);
		procfuncpart(s);
		statementpart(followers);
	}
}
void programme()
/* анализ конструкции <программа> */
{
	unsigned p[50] = { 1, point };
	accept(programsy);
	accept(ident);
	if (symbol == leftpar)
	{
		accept(leftpar);
		accept(ident);
		while (symbol == comma)
		{
			accept(comma);
			accept(ident);
		}
		accept(rightpar);
	}
	accept(semicolon);
	block(p); /* анализ конструкции <блок> */
	accept(point);
}
void constant(unsigned *followers)
{
	unsigned *s;
	if (!belong(symbol, codes_constant))
	{
		error(18, token);
		skipto2(codes_constant, followers);
	}
	if (belong(symbol, codes_constant))
	{
		if (symbol == intc || symbol == charc || symbol == floatc || symbol == stringc || symbol == booleanc || symbol == minus || symbol == plus || symbol == ident)
		{
			switch (symbol)
			{
			case intc:
				accept(intc);
				break;
			case charc:
				accept(charc);
				break;
			case floatc:
				accept(floatc);
				break;
			case stringc:
				accept(stringc);
				break;
			case booleanc:
				accept(booleanc);
				break;
			case minus:
				accept(minus);
				if (symbol == intc || symbol == floatc || symbol == ident)
				{
					switch (symbol)
					{
					case intc:
						accept(intc);
						break;
					case floatc:
						accept(floatc);
						break;
					case ident:
						accept(ident);
						break;
					}
				}
				break;
			case plus:
				accept(plus);
				if (symbol == intc || symbol == floatc || symbol == ident)
				{
					switch (symbol)
					{
					case intc:
						accept(intc);
						break;
					case floatc:
						accept(floatc);
						break;
					case ident:
						accept(ident);
						break;
					}
				}
				break;
			case ident:
				accept(ident);
				break;
			}
		}
		else
		{
			error(50, token); idknextsym();
		}
		if (!belong(symbol, followers))
		{
			error(6, token);
			skipto(followers);
		}
	}
}
void whilestatement(unsigned *followers)
/* анализ конструкции <цикл с предусловием> */
{
	accept(whilesy); 
	expression(codes_do);
	accept(dosy); 
	statement(followers);
}
void forstatement(unsigned *followers)
/* анализ конструкции <цикл с параметром> */
{
	accept(forsy); 
	accept(ident);
	accept(assign);
	expression(codes_todownto);
	if (symbol == tosy || symbol == downtosy)
	{
		if (symbol == tosy)
			accept(tosy);
		else
			accept(downtosy);
	}
	expression(codes_do); 
	accept(dosy);
	statement(followers);
}
void repeatstatement(unsigned *followers)
/* анализ конструкции <цикл с параметром> */
{
	accept(repeatsy);
	statement(acodes_repeat);
	while (symbol == semicolon)
	{
		accept(semicolon);
		if (symbol != untilsy)
			statement(acodes_repeat);
	}
	accept(untilsy); 
	expression(followers);
}
void compoundstatement(unsigned *followers)
/* анализ конструкции <составной оператор> */
{
	accept(beginsy); 
	statement(acodes_compcase);
	while (symbol == semicolon)
	{
		accept(semicolon); 
		statement(acodes_compcase);
	}
	accept(endsy);
	if (!belong(symbol, followers))
	{
		error(6, token); /* запрещенный символ */
		skipto(followers);
	}
}
void varpart(unsigned *followers)
/* анализ конструкции <раздел переменных> */
{
	unsigned *s;
	if (!belong(symbol, codes_varpart))
	{
		error(18, token); /* ошибка в разделе описаний */
		skipto2(codes_varpart, followers);
	}
	if (symbol == varsy)
	{
		accept(varsy);
		dis(aftervar, followers, s);
		do
		{
			vardeclaration(s);
			accept(semicolon);
		} while (symbol == ident);
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void vardeclaration(unsigned *followers)
/* анализ конструкции
<описание однотипных переменных> */
{
	if (!belong(symbol, codes_idstart))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_idstart, followers);
	}
	if (symbol == ident)
	{
		accept(ident);
		while (symbol == comma)
		{
			accept(comma);
			accept(ident);
		}
		accept(colon);
		type(followers);
	}
}
void type(unsigned *followers)
/* тип */
{
	if (!belong(symbol, codes_typ))
	{
		error(10, token); /* должно идти имя */
		skipto2(codes_typ, followers);
	}
	if (belong(symbol, codes_typ))
	{
		switch (symbol)
		{
		case leftpar: //перечисляемый
			simpletype(followers);
			break;
		case intc:	//ограниченный
			simpletype(followers);
			break;
		case charc:	//ограниченный
			simpletype(followers);
			break;
		case ident: //простой
			simpletype(followers);
			break;
		case arraysy: //регулярный
			unpackedcompositetype(followers);
			break;
		case recordsy:	//комбинированный
			unpackedcompositetype(followers);
			break;
		case setsy:	// множественный
			unpackedcompositetype(followers);
			break;
		case filesy: //файловый
			unpackedcompositetype(followers);
			break;
		case packedsy:	//упакованный
			accept(packedsy);
			unpackedcompositetype(followers);
			break;
		case arrow:	//ссылочный
			accept(arrow);
			accept(ident);
			break;
		default:
			error(10, token);
			idknextsym();
		}
		if (!belong(symbol, followers))
		{
			error(10, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void simpletype(unsigned *followers)
{
	switch (symbol)
	{
	case leftpar: //перечисляемый
		numtype(followers);
		break;
	case intc:	//ограниченный
		accept(intc);
		limtype(followers);
		break;
	case charc:	//ограниченный
		accept(charc);
		limtype(followers);
		break;
	case floatc:
		accept(floatc);
		limtype(followers);
		break;
	case stringc:
		accept(stringc);
		limtype(followers);
		break;
	case booleanc:
		accept(booleanc);
		limtype(followers);
		break;
	case minus:
		accept(minus);
		limtype(followers);
		break;
	case plus:
		accept(plus);
		limtype(followers);
		break;
	case ident: //простой
		accept(ident);
		if (symbol == twopoints)
			limtype(followers);
		break;
	}
}
void unpackedcompositetype(unsigned *followers)
{
	switch (symbol)
	{
	case arraysy: //регулярный
		regtype(followers);
		break;
	case recordsy:	//комбинированный
		combtype(followers);
		break;
	case setsy:	// множественный
		multipletype(followers);
		break;
	case filesy: //файловый
		accept(filesy);
		accept(ofsy);
		type(followers);
		break;
	}
}
void numtype(unsigned *followers)
{
	accept(leftpar);
	accept(ident);
	while (symbol == comma)
	{
		accept(comma);
		accept(ident);
	}
	accept(rightpar);
}
void multipletype(unsigned *followers)
{
	accept(setsy);
	accept(ofsy);
	simpletype(followers);
}
void limtype(unsigned *followers)
{
	accept(twopoints);
	constant(followers);
}
void regtype(unsigned *followers)
{
	accept(arraysy);
	accept(lbracket);
	simpletype(acodes_simpletype);
	while (symbol == comma)
	{
		nextsym();
		simpletype(acodes_simpletype);
	}
	accept(rbracket);
	accept(ofsy);
	type(followers);
}
void combtype(unsigned *followers)
{
	accept(recordsy);
	fieldlist(codes_end);
	accept(endsy);
}
void fieldlist(unsigned *followers)
{
	if (!belong(symbol, codes_field))
	{
		error(6, token); /* должно идти имя */
		skipto2(codes_field, followers);
	}
	if (belong(symbol, codes_field))
	{
		unsigned *s;
		if (symbol == ident)
		{
			dis(codes_semicase, followers, s);
			recordsection(s);
			while (symbol == semicolon)
			{
				accept(semicolon);
				recordsection(s);
			}
			if (symbol == casesy)
			{
				variativesection(followers);
			}
		}
		else if (symbol == casesy)
		{
			variativesection(followers);
		}
		else
			cout << "Some weird ass shit happened there:C\n";
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void variativesection(unsigned *followers)
{
	if (!belong(symbol, codes_case))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_case, followers);
	}
	if (belong(symbol, codes_case))
	{
		unsigned *s;
		accept(casesy);
		accept(ident);
		accept(colon);
		accept(ident);
		accept(ofsy);
		dis(aftervar, followers, s);
		variant(s);
		while (symbol == semicolon)
		{
			accept(semicolon);
			variant(s);
		}
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void variant(unsigned *followers)
{
	constant(acodes_2constant);
	while (symbol == comma)
	{
		accept(comma);
		constant(acodes_2constant);
	}
	accept(colon);
	accept(leftpar);
	fieldlist(codes_rightpar);
	accept(rightpar);
	if (!belong(symbol, followers))
	{
		error(6, token); /* запрещенный символ */
		skipto(followers);
	}
}
void recordsection(unsigned *followers)
{
	if (!belong(symbol, codes_idstart))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_idstart, followers);
	}
	if (belong(symbol, codes_idstart))
	{
		accept(ident);
		while (symbol == comma)
		{
			accept(comma);
			accept(ident);
		}
		accept(colon);
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void variable(unsigned *followers)
/* анализ конструкции <переменная> */
{
	if (!belong(symbol, codes_idstart))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_idstart, followers);
	}
	if (belong(symbol, codes_idstart))
	{
		accept(ident);
		while (symbol == lbracket || symbol == point || symbol == arrow)
			switch (symbol)
			{
			case lbracket:
				accept(lbracket);
				expression(acodes_simpletype);
				while (symbol == comma)
				{
					accept(comma);
					expression(acodes_simpletype);
				}
				accept(rbracket);
				break;
			case point:
				accept(point);
				accept(ident);
				break;
			case arrow:
				accept(arrow);
				break;
			}
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void ifstatement(unsigned *followers)
/* анализ конструкции <условный оператор> */
{
	if (!belong(symbol, codes_if))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_if, followers);
	}
	if (belong(symbol, codes_if))
	{
		unsigned *s;
		accept(ifsy);
		expression(acodes_iftrue);
		accept(thensy);
		dis(acodes_iffalse, followers, s);
		statement(s);
		if (symbol == elsesy)
		{
			accept(elsesy);
			statement(followers);
		}
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void casestatement(unsigned *followers)
{
	if (!belong(symbol, codes_case))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_case, followers);
	}
	if (belong(symbol, codes_case))
	{
		accept(casesy);
		expression(acodes_case1);
		accept(ofsy);
		caseelement(acodes_compcase);
		while (symbol == semicolon)
		{
			accept(semicolon);
			caseelement(acodes_compcase);
		}
		accept(endsy);
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void caseelement(unsigned *followers)
{
	if (symbol != endsy)
	{
		constant(acodes_2constant);
		while (symbol == comma)
		{
			accept(comma);
			constant(acodes_2constant);
		}
		accept(colon);
		statement(followers);
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void labelpart()
/* анализ конструкции <раздел меток> */
{
	if (symbol == labelsy)
	{
		accept(labelsy);
		accept(ident);
		while (symbol == comma)
		{
			accept(comma);
			accept(ident);
		}
		accept(semicolon);
	}
}
void statementpart(unsigned *followers)
/* раздел операторов */
{
	if (!belong(symbol, codes_begin))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_begin, followers);
	}
	if (symbol == beginsy)
	{
		accept(beginsy);
		statement(acodes_compcase);
		while (symbol == semicolon)
		{
			accept(semicolon);
			if (symbol != endsy)
				statement(acodes_compcase);
		}
		accept(endsy);
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void statement(unsigned *followers)
/* раздел оператора */
{
	if (symbol != endsy)
	{
		if (!belong(symbol, codes_statement))
		{
			error(6, token); /* должно идти имя */
			skipto2(codes_statement, followers);
		}
		if (belong(symbol, codes_statement))
		{
			if (symbol == ident)
			{
				accept(ident);
				while (symbol == lbracket || symbol == point || symbol == arrow)
					switch (symbol)
					{
					case lbracket:
						accept(lbracket); 
						expression(acodes_simpletype);
						while (symbol == comma)
						{
							accept(comma); 
							expression(acodes_simpletype);
						}
						accept(rbracket);
						break;
					case point:
						accept(point); 
						accept(ident);
						break;
					case arrow:
						accept(arrow);
						break;
					}
				if (symbol == colon)
				{
					/*accept(colon);
					unmarkedstatement();*/
				}
				else
				{
					switch (symbol)
					{
					case assign:
						accept(assign);
						expression(followers);
						break;
					case leftpar:
						accept(leftpar);
						expression(acodes_factparam);//fp
						while (symbol == comma)
						{
							accept(comma);
							expression(acodes_factparam);//fp
						}
						accept(rightpar);
						break;
					}
				}
			}
			else
			{
				switch (symbol)
				{
				case gotosy:
					accept(gotosy);
					accept(ident);
					break;
				case ifsy:
					ifstatement(followers);
					break;
				case beginsy:
					accept(beginsy);
					statement(acodes_compcase);
					ff = (symbol == endsy);
					while (symbol == semicolon && !ff)
					{
						accept(semicolon);
						if (symbol != endsy)
						{
							statement(acodes_compcase);
						}
						ff = (symbol == endsy);
					}
					accept(endsy);
					break;
				case casesy:
					casestatement(followers);
					break;
				case whilesy:
					cyclestatement(followers);
					break;
				case repeatsy:
					cyclestatement(followers);
					break;
				case forsy:
					cyclestatement(followers);
					break;
				case withsy:
					connstatement(followers);
					break;
				default:
					cout << "WTF?\n";
					nextsym();
					break;
				}
			}
			if (!belong(symbol, followers))
			{
				error(6, token); /* запрещенный символ */
				skipto(followers);
			}
		}
	}
	else
	{
		//nextsym();
	}
}
void connstatement(unsigned *followers)
{
	if (!belong(symbol, codes_with))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_with, followers);
	}
	if (symbol == withsy)
	{
		accept(withsy);
		variable(acodes_wiwifor);
		while (symbol == comma)
		{
			accept(comma);
			variable(acodes_wiwifor);
		}
		accept(dosy);
		statement(followers);
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void cyclestatement(unsigned *followers)
{
	switch (symbol)
	{
	case forsy:
		forstatement(followers);
		break;
	case repeatsy:
		repeatstatement(followers);
		break;
	case whilesy:
		whilestatement(followers);
		break;
	}
	if (!belong(symbol, followers))
	{
		error(6, token); /* запрещенный символ */
		skipto(followers);
	}
}
void expression(unsigned *followers)
{
	if (!belong(symbol, codes_express))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_express, followers);
	}
	if (belong(symbol, codes_express))
	{
		unsigned *s;
		dis(codes_comp, followers, s);
		simpleexpression(s);
		if (symbol == equal || symbol == latergreater || symbol == later || symbol == laterequal || symbol == greaterequal ||
			symbol == greater || symbol == insy)
		{
			switch (symbol)
			{
			case equal:
				accept(equal);
				break;
			case latergreater:
				accept(latergreater);
				break;
			case later:
				accept(later);
				break;
			case laterequal:
				accept(laterequal);
				break;
			case greaterequal:
				accept(greaterequal);
				break;
			case greater:
				accept(greater);
				break;
			case insy:
				accept(insy);
				break;
			}
			simpleexpression(followers);
		}
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void simpleexpression(unsigned *followers)
{
	if (!belong(symbol, codes_simpleexpress))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_simpleexpress, followers);
	}
	if (belong(symbol, codes_simpleexpress))
	{
		if (symbol == minus || symbol == plus)
		{
			if (symbol == minus)
				accept(minus);
			else
				accept(plus);
		}
		unsigned *s;
		dis(followers, codes_pmo, s);
		addend(s);
		while (symbol == plus || symbol == minus || symbol == orsy)
		{
			if (symbol == plus)
				accept(plus);
			else if (symbol == minus)
				accept(minus);
			else
				accept(orsy);
			addend(s);
		}
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void addend(unsigned *followers)
{
	if (!belong(symbol, codes_mult))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_mult, followers);
	}
	if (belong(symbol, codes_mult))
	{
		unsigned *s;
		dis(acodes_mult, followers, s);
		mult(s);
		while (symbol == star || symbol == slash || symbol == divsy || symbol == modsy || symbol == andsy)
		{
			switch (symbol)
			{
			case star:
				accept(star);
				break;
			case slash:
				accept(slash);
				break;
			case divsy:
				accept(divsy);
				break;
			case modsy:
				accept(modsy);
				break;
			case andsy:
				accept(andsy);
				break;
			}
			mult(s);
		}
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void mult(unsigned *followers)
{
	if (!belong(symbol, codes_mult))
	{
		error(6, token); /* должно идти имя */
		skipto2(codes_mult, followers);
	}
	if (belong(symbol, codes_mult))
	{
		switch (symbol)
		{
		case ident:
			accept(ident);
			if (symbol == leftpar || symbol == point || symbol == arrow || symbol == lbracket)
			{
				switch (symbol)
				{
				case leftpar:
					accept(leftpar);
					expression(acodes_factparam);//fp
					while (symbol == comma)
					{
						accept(comma);
						expression(acodes_factparam);//fp
					}
					accept(rightpar);
					break;
				case point:
					while (symbol == lbracket || symbol == point || symbol == arrow)
						switch (symbol)
						{
						case lbracket:
							accept(lbracket); 
							expression(acodes_simpletype);
							while (symbol == comma)
							{
								accept(comma);
								expression(acodes_factparam);
							}
							accept(rbracket);
							break;
						case point:
							accept(point); accept(ident);
							break;
						case arrow:
							accept(arrow);
							break;
						}
					break;
				case arrow:
					while (symbol == lbracket || symbol == point || symbol == arrow)
						switch (symbol)
						{
						case lbracket:
							accept(lbracket);
							expression(acodes_simpletype);
							while (symbol == comma)
							{
								accept(comma);
								expression(acodes_simpletype);
							}
							accept(rbracket);
							break;
						case point:
							accept(point); accept(ident);
							break;
						case arrow:
							accept(arrow);
							break;
						}
					break;
				case lbracket:
					while (symbol == lbracket || symbol == point || symbol == arrow)
						switch (symbol)
						{
						case lbracket:
							accept(lbracket); 
							expression(acodes_simpletype);
							while (symbol == comma)
							{
								accept(comma); 
								expression(acodes_simpletype);
							}
							accept(rbracket);
							break;
						case point:
							accept(point); accept(ident);
							break;
						case arrow:
							accept(arrow);
							break;
						}
					break;
				}
			}
			break;
		case intc:
			if (nmb_int >= 0)
			{
				accept(intc);
			}
			else
			{
				error(50, token); idknextsym();
			}
			break;
		case floatc:
			if (nmb_float >= 0)
			{
				accept(floatc);
			}
			else
			{
				error(50, token); idknextsym();
			}
			break;
		case stringc:
			accept(stringc);
			break;
		case charc:
			accept(charc);
			break;
		case nilsy:
			accept(nilsy);
			break;
		case lbracket:
			accept(lbracket);
			if (symbol != rbracket)
			{
				expression(acodes_3const);
				if (symbol == twopoints)
					expression(acodes_simpletype);
				while (symbol == comma)
				{
					accept(comma);
					expression(acodes_3const);
					if (symbol == twopoints)
						expression(acodes_simpletype);
				}
			}
			accept(rbracket);
			break;
		case notsy:
			accept(notsy);
			mult(followers);
			break;
		case leftpar:
			accept(leftpar);
			expression(codes_rightpar);
			accept(rightpar);
			break;
		default:
			error(322, token); idknextsym();
		}
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void constpart(unsigned *followers)
{
	if (!belong(symbol, codes_const))
	{
		error(18, token);
		skipto2(codes_const, followers);
	}
	if (symbol == constsy)
	{
		accept(constsy);
		while (symbol == ident)
		{
			accept(ident);
			accept(equal);
			constant(aftervar);
			accept(semicolon);
		}
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void typepart(unsigned *followers)
{
	if (!belong(symbol, codes_type))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_type, followers);
	}
	if (symbol == typesy)
	{
		accept(typesy);
		while (symbol == ident)
		{
			accept(ident);
			accept(equal);
			type(aftervar);
			accept(semicolon);
		}
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void procfuncpart(unsigned *followers)
{
	if (!belong(symbol, codes_procfuncpart))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_procfuncpart, followers);
	}
	if (belong(symbol, codes_procfuncpart))
	{
		while (symbol == proceduresy || symbol == functionsy)
		{
			if (symbol == proceduresy)
			{
				procedureheader(codes_block);
				block(aftervar);
			}
			else
			{
				functionheader(codes_block);
				block(aftervar);
			}
			accept(semicolon);
		}
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void procedureheader(unsigned *followers)
{
	unsigned pr[] = { 1,proceduresy };
	if (!belong(symbol,pr))
	{
		error(2, token); /* должно идти имя */
		skipto2(pr, followers);
	}
	if (belong(symbol, pr))
	{
		accept(proceduresy);
		accept(ident);
		if (symbol == leftpar)
		{
			accept(leftpar);
			fparametermodule(codes_semiright);
			while (symbol == semicolon)
			{
				accept(semicolon);
				fparametermodule(codes_semiright);
			}
			accept(rightpar);
		}
		accept(semicolon);
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void functionheader(unsigned *followers)
{
	unsigned pr[] = { 1, functionsy };
	if (!belong(symbol, pr))
	{
		error(2, token); /* должно идти имя */
		skipto2(pr, followers);
	}
	if (belong(symbol, pr))
	{
		accept(functionsy);
		accept(ident);
		if (symbol == leftpar)
		{
			accept(leftpar);
			fparametermodule(codes_semiright);
			while (symbol == semicolon)
			{
				accept(semicolon);
				fparametermodule(codes_semiright);
			}
			accept(rightpar);
		}
		accept(colon);
		accept(ident);
		accept(semicolon);
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void fparametermodule(unsigned *followers)
{
	if (!belong(symbol, codes_fpmodule))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_fpmodule, followers);
	}
	if (belong(symbol, codes_fpmodule))
	{
		switch (symbol)
		{
		case ident:
			paramgroup(followers);
			break;
		case varsy:
			accept(varsy);
			paramgroup(followers);
			break;
		case functionsy:
			accept(functionsy);
			paramgroup(followers);
			break;
		case proceduresy:
			accept(proceduresy);
			accept(ident);
			while (symbol == comma)
			{
				accept(comma);
				accept(ident);
			}
			break;
		default:
			error(7, token);
			idknextsym();
		}
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
void paramgroup(unsigned *followers)
{
	if (!belong(symbol, codes_idstart))
	{
		error(2, token); /* должно идти имя */
		skipto2(codes_idstart, followers);
	}
	if (belong(symbol, codes_idstart))
	{
		accept(ident);
		while (symbol == comma)
		{
			accept(comma);
			accept(ident);
		}
		accept(colon);
		accept(ident);
		if (!belong(symbol, followers))
		{
			error(6, token); /* запрещенный символ */
			skipto(followers);
		}
	}
}
/*void factparameter(unsigned *followers)
{
	//cout << "fparam\n";
		expression();
}*/