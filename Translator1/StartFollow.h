#pragma once
#include "Symbols.h"
/* ��������� ����� ��������, ��������� ��� ��������� �������������� 	*/
/* �����������:								*/

unsigned codes_idstart[] = {1, ident },	/* ��������� ������� ��������� 	*/
									/* �������������� ����������� 				*/
	codes_block[] = {7, labelsy,constsy,typesy,varsy,functionsy,
	proceduresy,beginsy },	/* ��������� ������� ��������	*/
									/* �������� � ������� ����������			*/
	codes_rightpar[] = {1, rightpar },
	/* ������ ������ 					*/
	codes_constant[] = {7, plus,minus,charc,stringc,ident,intc,floatc },	/* ��������� �codes_rightpar������ ����������� constant       */
	codes_typ[] = { 13, packedsy,arrow,arraysy,filesy,setsy,recordsy,
	plus,minus,ident,leftpar,intc,charc,stringc },
	/* ��������� ������� ����������� �������� ����;	*/
	/* {plus,minus,ident,leftpar,intc,charc,stringc,eolint}-*/
	/* ��������� ������� ����������� �������� �������� ���� */
	codes_fixpart[] = { 4, ident,semicolon,casesy,endsy },
	codes_fpmodule[]= {4, ident,varsy,functionsy,proceduresy},
	codes_typepart[] = {5, typesy, varsy, functionsy, proceduresy, beginsy},
	codes_varpart[] = {4, varsy, functionsy, proceduresy, beginsy},
	codes_procfuncpart[] = {3, functionsy, proceduresy, beginsy},
	codes_semiright[] = {2,semicolon,rightpar},
	/* ��������� ������� ����������� ������ ����� � ���-	*/
	/* �������� ������������� �����	������			*/
	codes_casefield[] = { 9, floatc,endsy,semicolon,plus,minus,charc,
	stringc,ident,intc },
	codes_simpleexpress[] = {11, minus,plus,ident,intc,floatc,stringc,charc,nilsy,lbracket,notsy,leftpar},
	/* ��������� ������� ����������� ��������       	*/
	codes_statement[] = { 14, intc,endsy,elsesy,untilsy,ident,beginsy,ifsy,
	whilesy,repeatsy,forsy,casesy,withsy,semicolon,gotosy },
	/* ��������� ������� ����������� <��������>             */
	/* (��� ������������� ������ ������������ �������:      */
	/* {beginsy,ifsy,whilesy,repeatsy,forsy,casesy,withsy,  */
	/* semicolon,gotosy,eolint} )                           */
	codes_express[] = { 11, plus, minus, leftpar, lbracket, notsy, ident,
	intc, floatc, charc, stringc, nilsy },
	codes_do[] = {1,dosy},
	codes_todownto[] = { 2, tosy, downtosy },
	codes_mult[] = { 9,ident,intc,floatc,stringc,charc,nilsy,lbracket,notsy,leftpar },
	codes_end[]={1,endsy},
	codes_case[] = { 1,casesy },
	codes_field[] = {2,casesy,ident},
	codes_if[] = { 1,ifsy },
	codes_label[] = { 1,labelsy },
	codes_begin[] = { 1,beginsy },
	codes_with[] = { 1,withsy },
	codes_const[]={6,constsy,typesy,varsy,functionsy,proceduresy,beginsy },
	codes_type[]={5,typesy,varsy,functionsy,proceduresy,beginsy },
	codes_semicase[] = {2, semicolon, casesy},
	codes_pmo[] = {3,plus,minus,orsy},
	codes_comp[] = { 7, equal, latergreater, later, laterequal, greaterequal, greater,insy },
	/* ��������� ������� ��������� � �������� ��������� 	*/
	codes_termfact[] = { 9, ident, leftpar, lbracket, notsy, intc, floatc,
	charc, stringc, nilsy };
/* ��������� ������� ���������� � ��������� 		*/


/* ��������� ����� ��������, ��������� ����� ��������� ��������� ���-	*/
/* ��������:								*/

unsigned

acodes_block[] = { 1, point },	/* ���-	*/
												/* ����, ��������� �� ������������ ����� � �������� 	*/
												/* ���������			 			*/
	acodes_simpletype[] = { 2, comma,rbracket }, 	/* ���- */
														/* ����, ��������� ����� ����� ������ simpletype() �� 	*/
														/* ����� ������� ���� "������" 				*/
	acodes_fixpart[] = { 3, casesy,rightpar,endsy },	/* �������, 	*/
															/* ��������� ����� ����� ������� ����������� fixpart;	*/
															/* {rightpar,endsy,eolint} - �������, ��������� ����� 	*/
															/* ����� ������� ������ ����� ��� ������ reestrfields() */
															/* �� casefield() ( � ��� ������ �� complextype() ���-	*/
															/* ������ ������ ������ endsy )				*/
	acodes_typ[] = { 3, endsy,rightpar,semicolon },	/* ���-	*/
														/* ����, ��������� ����� ����� ������� ����������� typ 	*/
														/* ��� ������ ������� typ() �� fixpart()		*/
	acodes_2constant[] = { 2, comma,colon }, 	/* �������, ��������� 	*/
													/* ����� ����� ������� ��������� ��� ������ constant()	*/
													/* �� casefield() � variant()				*/
	acodes_3const[] = { 3, twopoints,comma,rbracket },	/* ���� */
															/* ��������, ��������� ����� ����� ������� ��������� 	*/
	acodes_listparam[] = { 4, colon,semicolon,constsy,varsy },
	acodes_mult[]={5,star,slash,divsy,modsy,andsy},
	/* �������, ��������� ����� ����� ������ ����������     */
	/* ( ������� functionsy,proceduresy,beginsy ��� ���� �  */
	/*   followers)                                         */
	acodes_factparam[] = { 2, comma,rightpar },
	/* �������, ��������� ����� ����� ������� �����������   */
	/* ���������� �������� � �������                        */
	acodes_assign[] = { 1, assign },
	aftervar[] = {1, semicolon},
	/* ������, ��������� ����� ����� ���������� � ��������� */
	/* ������������ � � ��������� for                       */
	acodes_compcase[] = { 2, semicolon,endsy },
	/* �������, ��������� ����� ����� ��������� � ��������� */
	/* ��������� � ����� �������� � ��������� ��������      */
	acodes_iftrue[] = { 1, thensy },
	/* ������, ��������� ����� ����� ��������� ��������� �  */
	/* ��������� if						*/
	acodes_iffalse[] = { 1, elsesy },
	/*������, ��������� ����� ����� ��������� ����� "������"*/
	/* � ��������� if					*/
	acodes_wiwifor[] = { 2, comma,dosy },
	/* �������, ��������� ����� ����� ���������� � ���������*/
	/* ��������� with;  { dosy,eolint} - ������, ���������  */
	/* ����� ����� ��������� ��������� � ��������� while �  */
	/* ����� ����� ���������-������ ������� ��������� ����- */
	/* ����� ����� � ��������� for				*/
	acodes_repeat[] = { 2, untilsy, semicolon },
	/* c�����s, ��������� ����� ����� ��������� � ����      */
	/* ��������� repeat					*/
	acodes_case1[] = { 1, ofsy },
	/* ������, ��������� ����� ����� ����������� ���������  */
	/* � ��������� case					*/
	acodes_for1[] = { 2, tosy,downtosy },
	/* �������, ��������� ����� ����� ���������-������ ���- */
	/* ���� ��������� ��������� ����� � ��������� for       */
	acodes_ident[] = { 3, lbracket, arrow, point },
	/* ... ����� �������������� � ���������� 		*/
	acodes_index[] = { 2, rbracket, comma },
	/* ... ����� ���������� ��������� ��� ������� �������	*/
	acodes_set1[] = { 3, rbracket, twopoints, comma };
/* ... ����� 1-�� ��������� � ������������ ��������� 	*/


