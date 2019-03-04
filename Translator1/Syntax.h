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