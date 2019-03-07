#pragma once
#include "Lexical.h"
void accept(unsigned symbolexpected
/* ��� ���������� ������� */)
{
	if (symbol == symbolexpected)
		nextsym();
	else error(symbolexpected, token);
}
void programme()
/* ������ ����������� <���������> */
{
	accept(programsy);
	accept(ident);
	accept(semicolon);
	block(); /* ������ ����������� <����> */
	accept(point);
}
void block()
/* ������ ����������� <����> */
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
/* ������ ����������� <���� � ������������> */
{
	accept(whilesy); expression();
	accept(dosy); statement();
}
void forstatement()
/* ������ ����������� <���� � ����������> */
{
	accept(forsy); accept(ident);
	accept(assign); expression();
	if (symbol == tosy || symbol == downtosy)
		nextsym();
	expression(); accept(dosy);
	statement();
}
void repeatstatement()
/* ������ ����������� <���� � ����������> */
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
/* ������ ����������� <��������� ��������> */
{
	accept(beginsy); statement();
	while (symbol == semicolon)
	{
		nextsym(); statement();
	}
	accept(endsy);
}
void varpart()
/* ������ ����������� <������ ����������> */
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
/* ������ �����������
<�������� ���������� ����������> */
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
/* ��� */
{
	switch (symbol)
	{
	case leftpar : //�������������
		simpletype();
		break;
	case intc:	//������������
		simpletype();
		break;
	case charc:	//������������
		simpletype();
		break;
	case ident: //�������
		simpletype();
		break;
	case arraysy: //����������
		unpackedcompositetype();
		break;
	case recordsy:	//���������������
		unpackedcompositetype();
		break;
	case setsy:	// �������������
		unpackedcompositetype();
		break;
	case filesy: //��������
		unpackedcompositetype(); 
		break;
	case packedsy:	//�����������
		nextsym();
		unpackedcompositetype();
		break;
	case arrow:	//���������
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
	case leftpar: //�������������
		numtype();
		break;
	case intc:	//������������
		limtype(1);
		break;
	case charc:	//������������
		limtype(0);
		break;
	case ident: //�������
		break;
	}
}
void unpackedcompositetype()
{
	switch (symbol)
	{
	case arraysy: //����������
		regtype();
		break;
	case recordsy:	//���������������
		combtype();
		break;
	case setsy:	// �������������
		multipletype();
		break;
	case filesy: //��������
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
/* ������ ����������� <����������> */
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
/* ������ ����������� <�������� ��������> */
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
/* ������ ����������� <������ �����> */
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
/* ������ ���������� */
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
/* ������ ��������� */
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
/* ������ ��������� */
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