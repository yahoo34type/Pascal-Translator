#pragma once
#include "Symbols.h"
/* Множества КОДОВ символов, стартовых для различных обрабатываемых 	*/
/* конструкций:								*/

unsigned codes_idstart[] = {1, ident },	/* стартовые символы некоторых 	*/
									/* обрабатываемых конструкций 				*/
	codes_block[] = {7, labelsy,constsy,typesy,varsy,functionsy,
	proceduresy,beginsy },	/* стартовые символы разделов	*/
									/* описаний и раздела операторов			*/
	codes_rightpar[] = {1, rightpar },
	/* правая скобка 					*/
	codes_constant[] = {7, plus,minus,charc,stringc,ident,intc,floatc },	/* стартовые сcodes_rightparимволы конструкции constant       */
	codes_typ[] = { 13, packedsy,arrow,arraysy,filesy,setsy,recordsy,
	plus,minus,ident,leftpar,intc,charc,stringc },
	/* стартовые символы конструкции описания типа;	*/
	/* {plus,minus,ident,leftpar,intc,charc,stringc,eolint}-*/
	/* стартовые символы конструкции описания простого типа */
	codes_fixpart[] = { 4, ident,semicolon,casesy,endsy },
	codes_fpmodule[]= {4, ident,varsy,functionsy,proceduresy},
	codes_typepart[] = {5, typesy, varsy, functionsy, proceduresy, beginsy},
	codes_varpart[] = {4, varsy, functionsy, proceduresy, beginsy},
	codes_procfuncpart[] = {3, functionsy, proceduresy, beginsy},
	codes_semiright[] = {2,semicolon,rightpar},
	/* стартовые символы конструкции списка полей и кон-	*/
	/* струкции фиксированной части	записи			*/
	codes_casefield[] = { 9, floatc,endsy,semicolon,plus,minus,charc,
	stringc,ident,intc },
	codes_simpleexpress[] = {11, minus,plus,ident,intc,floatc,stringc,charc,nilsy,lbracket,notsy,leftpar},
	/* стартовые символы конструкции варианта       	*/
	codes_statement[] = { 14, intc,endsy,elsesy,untilsy,ident,beginsy,ifsy,
	whilesy,repeatsy,forsy,casesy,withsy,semicolon,gotosy },
	/* стартовые символы конструкции <оператор>             */
	/* (при нейтрализации ошибок используются символы:      */
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
	/* стартовые символы выражения и простого выражения 	*/
	codes_termfact[] = { 9, ident, leftpar, lbracket, notsy, intc, floatc,
	charc, stringc, nilsy };
/* стартовые символы слагаемого и множителя 		*/


/* Множества кодов символов, ожидаемых после обработки различных кон-	*/
/* струкций:								*/

unsigned

acodes_block[] = { 1, point },	/* сим-	*/
												/* волы, следующие за конструкцией блока в основной 	*/
												/* программе			 			*/
	acodes_simpletype[] = { 2, comma,rbracket }, 	/* сим- */
														/* волы, ожидаемые сразу после вызова simpletype() во 	*/
														/* время анализа типа "массив" 				*/
	acodes_fixpart[] = { 3, casesy,rightpar,endsy },	/* символы, 	*/
															/* ожидаемые сразу после анализа конструкции fixpart;	*/
															/* {rightpar,endsy,eolint} - символы, ожидаемые сразу 	*/
															/* после анализа списка полей при вызове reestrfields() */
															/* из casefield() ( а при вызове из complextype() ожи-	*/
															/* даемый символ только endsy )				*/
	acodes_typ[] = { 3, endsy,rightpar,semicolon },	/* сим-	*/
														/* волы, ожидаемые сразу после анализа конструкции typ 	*/
														/* при вызове функции typ() из fixpart()		*/
	acodes_2constant[] = { 2, comma,colon }, 	/* символы, ожидаемые 	*/
													/* сразу после анализа константы при вызове constant()	*/
													/* из casefield() и variant()				*/
	acodes_3const[] = { 3, twopoints,comma,rbracket },	/* коды */
															/* символов, ожидаемых сразу после анализа константы 	*/
	acodes_listparam[] = { 4, colon,semicolon,constsy,varsy },
	acodes_mult[]={5,star,slash,divsy,modsy,andsy},
	/* символы, ожидаемые сразу после списка параметров     */
	/* ( символы functionsy,proceduresy,beginsy уже есть в  */
	/*   followers)                                         */
	acodes_factparam[] = { 2, comma,rightpar },
	/* символы, ожидаемые сразу после разбора фактических   */
	/* параметров процедур и функций                        */
	acodes_assign[] = { 1, assign },
	aftervar[] = {1, semicolon},
	/* символ, ожидаемый сразу после переменной в операторе */
	/* присваивания и в операторе for                       */
	acodes_compcase[] = { 2, semicolon,endsy },
	/* символы, ожидаемые сразу после оператора в составном */
	/* операторе и после варианта в операторе варианта      */
	acodes_iftrue[] = { 1, thensy },
	/* символ, ожидаемый сразу после условного выражения в  */
	/* операторе if						*/
	acodes_iffalse[] = { 1, elsesy },
	/*символ, ожидаемый сразу после оператора ветви "истина"*/
	/* в операторе if					*/
	acodes_wiwifor[] = { 2, comma,dosy },
	/* символы, ожидаемые сразу после переменной в заголовке*/
	/* оператора with;  { dosy,eolint} - символ, ожидаемый  */
	/* сразу после условного выражения в операторе while и  */
	/* сразу после выражения-второй границы изменения пара- */
	/* метра цикла в операторе for				*/
	acodes_repeat[] = { 2, untilsy, semicolon },
	/* cимволs, ожидаемые сразу после оператора в теле      */
	/* оператора repeat					*/
	acodes_case1[] = { 1, ofsy },
	/* символ, ожидаемый сразу после выбирающего выражения  */
	/* в операторе case					*/
	acodes_for1[] = { 2, tosy,downtosy },
	/* символы, ожидаемые сразу после выражения-первой гра- */
	/* ницы изменения пераметра цикла в операторе for       */
	acodes_ident[] = { 3, lbracket, arrow, point },
	/* ... после идентификатора в переменной 		*/
	acodes_index[] = { 2, rbracket, comma },
	/* ... после индексного выражения при разборе массива	*/
	acodes_set1[] = { 3, rbracket, twopoints, comma };
/* ... после 1-го выражения в конструкторе множества 	*/


