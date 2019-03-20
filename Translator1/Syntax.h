#pragma once
#include "Lexical.h"
#include "Syntaxh.h"
bool ff = false;
void idknextsym()
{
	nextsym();
}
void accept(unsigned symbolexpected
/* код ожидаемого символа */)
{
	cout << "Waiting: " << symbolexpected << ", Symbol: " << symbol << endl;
	if (symbol == symbolexpected)
	{
		nextsym();
	}
	else { error(symbolexpected, token); idknextsym(); }
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
void programme()
/* анализ конструкции <программа> */
{
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
	block(); /* анализ конструкции <блок> */
	accept(point);
}
void constant()
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
	{
		if (symbol == tosy)
			accept(tosy);
		else
			accept(downtosy);
	}
	expression(); 
	accept(dosy);
	statement();
}
void repeatstatement()
/* анализ конструкции <цикл с параметром> */
{
	accept(repeatsy);
	statement();
	while (symbol == semicolon)
	{
		accept(semicolon);
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
		accept(semicolon); statement();
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
		accept(comma);
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
		accept(packedsy);
		unpackedcompositetype();
		break;
	case arrow:	//ссылочный
		accept(arrow);
		accept(ident);
		break;
	default:
		error(10, token);
		idknextsym();
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
		accept(intc);
		limtype(1);
		break;
	case charc:	//ограниченный
		accept(charc);
		limtype(0);
		break;
	case ident: //простой
		accept(ident);
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
	accept(leftpar);
	accept(ident);
	while (symbol == comma)
	{
		accept(comma);
		accept(ident);
	}
	accept(rightpar);
}
void multipletype()
{
	accept(setsy);
	accept(ofsy);
	simpletype();
}
void limtype(bool flag)
{
	accept(twopoints);
	if (flag)
		accept(intc);
	else
		accept(charc);
}
void regtype()
{
	accept(arraysy);
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
	accept(recordsy);
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
			accept(semicolon);
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
	accept(casesy);
	accept(ident);
	accept(colon);
	accept(ident);
	accept(ofsy);
	variant();
	while (symbol == semicolon)
	{
		accept(semicolon);
		variant();
	}
}
void variant()
{
	constant();
	while (symbol == comma)
	{
		accept(comma);
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
		accept(comma);
		accept(ident);
	}
	accept(colon);
}
void variable()
/* анализ конструкции <переменна€> */
{
	accept(ident);
	while (symbol == lbracket || symbol == point || symbol == arrow)
		switch (symbol)
		{
		case lbracket:
			accept(lbracket); expression();
			while (symbol == comma)
			{
				accept(comma); expression();
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
}
void ifstatement()
/* анализ конструкции <условный оператор> */
{
	accept(ifsy); expression();
	accept(thensy); statement();
	if (symbol == elsesy)
	{
		accept(elsesy);
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
		accept(semicolon);
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
			accept(comma);
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
void statementpart()
/* раздел операторов */
{
	accept(beginsy);
	statement();
	while (symbol == semicolon)
	{
		accept(semicolon);
		if (symbol != endsy)
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
			accept(ident);
			while (symbol == lbracket || symbol == point || symbol == arrow)
				switch (symbol)
				{
				case lbracket:
					accept(lbracket); expression();
					while (symbol == comma)
					{
						accept(comma); expression();
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
			if (symbol == colon)
			{
				accept(colon);
				unmarkedstatement();
			}
			else 
			{
				switch (symbol)
				{
				case assign:
					accept(assign);
					expression();
					break;
				case leftpar:
					accept(leftpar);
					factparameter();
					while (symbol == comma)
					{
						accept(comma);
						factparameter();
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
				ifstatement();
				break;
			case beginsy:
				accept(beginsy);
				statement();
				ff = (symbol == endsy);
				while (symbol == semicolon && !ff)
				{
					accept(semicolon);
					if (symbol != endsy)
					{
						statement();
					}						
					ff = (symbol == endsy);
				}
				accept(endsy);
				break;
			case casesy:
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
			/*default:
				error(322, token); idknextsym();
				break;*/
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
			accept(ident);
			switch (symbol)
			{
			case assign:
				accept(assign);
				expression();
				break;
			case leftpar:
				accept(leftpar);
				factparameter();
				while (symbol == comma)
				{
					accept(comma);
					factparameter();
				}
				accept(rightpar);
				break;
			default:
				error(322, token); idknextsym();
				break;
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
				ifstatement();
				break;
			case beginsy:
				accept(beginsy);
				statement();
				while (symbol == semicolon)
				{
					accept(semicolon);
					statement();
				}
				accept(endsy);
				break;
			case casesy:
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
				error(322, token); idknextsym();
				break;
			}
		}
	}
	else
	{
		nextsym();
	}
}
void connstatement()
{
	accept(withsy);
	variable();
	while (symbol == comma)
	{
		accept(comma);
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
		simpleexpression();
	}
}
void simpleexpression()
{
	if (symbol == minus || symbol == plus)
	{
		if (symbol == minus)
			accept(minus);
		else
			accept(plus);
	}
	addend();
	while (symbol == plus || symbol == minus || symbol == orsy)
	{
		if (symbol == plus)
			accept(plus);
		else if (symbol == minus)
			accept(minus);
		else
			accept(orsy);
		addend();
	}
}
void addend()
{
	mult();
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
		mult();
	}
}
void mult()
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
				factparameter();
				while (symbol == comma)
				{
					accept(comma);
					factparameter();
				}
				accept(rightpar);
				break;
			case point:
				while (symbol == lbracket || symbol == point || symbol == arrow)
					switch (symbol)
					{
					case lbracket:
						accept(lbracket); expression();
						while (symbol == comma)
						{
							accept(comma); expression();
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
						accept(lbracket); expression();
						while (symbol == comma)
						{
							accept(comma); expression();
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
						accept(lbracket); expression();
						while (symbol == comma)
						{
							accept(comma); expression();
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
			expression();
			if (symbol == twopoints)
				expression();
			while (symbol == comma)
			{
				accept(comma);
				expression();
				if (symbol == twopoints)
					expression();
			}
		}
		accept(rbracket);
		break;
	case notsy:
		accept(notsy);
		mult();
		break;
	case leftpar:
		accept(leftpar);
		expression();
		accept(rightpar);
		break;
	default:
		error(322, token); idknextsym();
	}
}
void constpart()
{
	if (symbol == constsy)
	{
		accept(constsy);
		while (symbol == ident)
		{
			accept(ident);
			accept(equal);
			constant();
			accept(semicolon);
		}
	}
}
void typepart()
{
	if (symbol == typesy)
	{
		accept(typesy);
		while (symbol == ident)
		{
			accept(ident);
			accept(equal);
			type();
			accept(semicolon);
		}
	}
}
void procfuncpart()
{
	while (symbol == proceduresy || symbol == functionsy)
	{
		if (symbol == proceduresy)
		{
			procedureheader();
			block();
		}
		else
		{
			functionheader();
			block();
		}
		accept(semicolon);
	}
}
void procedureheader()
{
	accept(proceduresy);
	accept(ident);
	if (symbol == leftpar)
	{
		accept(leftpar);
		fparametermodule();
		while (symbol == semicolon)
		{
			accept(semicolon);
			fparametermodule();
		}
		accept(rightpar);
	}
	accept(semicolon);
}
void functionheader()
{
	accept(functionsy);
	accept(ident);
	if (symbol == leftpar)
	{
		accept(leftpar);
		fparametermodule();
		while (symbol == semicolon)
		{
			accept(semicolon);
			fparametermodule();
		}
		accept(rightpar);
	}
	accept(colon);
	accept(ident);
	accept(semicolon);
}
void fparametermodule()
{
	switch (symbol)
	{
	case ident:
		paramgroup();
		break;
	case varsy:
		accept(varsy);
		paramgroup();
		break;
	case functionsy:
		accept(functionsy);
		paramgroup();
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
		error(7, token); idknextsym();
	}
}
void paramgroup()
{
	accept(ident);
	while (symbol == comma)
	{
		accept(comma);
		accept(ident);
	}
	accept(colon);
	accept(ident);
}
void factparameter()
{
	//cout << "fparam\n";
		expression();
}