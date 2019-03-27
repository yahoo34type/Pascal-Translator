#pragma once
#define star 21 /* * */
#define slash 60 /* / */
#define equal 16 /* = */
#define comma 20 /* , */
#define semicolon 14 /* ; */
#define colon 5 /* : */
#define point 61 /* . */
#define arrow 62 /* ^ */
#define leftpar 9 /* ( */
#define rightpar 4 /* ) */
#define lbracket 11 /* [ */
#define rbracket 12 /* ] */
#define flpar 63 /* { */
#define frpar 64 /* } */
#define later 65 /* < */
#define greater 66 /* > */
#define laterequal 67 /* <= */
#define greaterequal 68 /* >= */
#define latergreater 69 /* <> */
#define plus 70 /* + */
#define minus 71 /* Ц */
#define lcomment 72 /* (* */
#define rcomment 73 /* *) */
#define assign 51 /* := */
#define twopoints 74 /* .. */
#define ident 2 /* идентификатор */
#define floatc 82 /* вещественна€ константа */
#define intc 15 /* цела€ константа */
#define charc 83 /* символьна€ константа */
#define stringc 101 /* строкова€ константа */
#define booleanc 102 /* логическа€ константа */
#define olcomment 100 /* // */
#define eofile 134
/*  список  ключевых  слов  */
#define   dosy           54
#define   ifsy           56
#define   insy           22
#define   ofsy            8
#define   orsy           23           /* разделитель  !   */
#define   tosy           55

/* ключевые  слова  длины  2 */

#define   andsy          24            /* разделитель   &  */
#define   divsy          25
#define   endsy          13
#define   forsy          26
#define   modsy          27
#define   nilsy          89
#define   notsy          28
#define   setsy          29
#define   varsy          30

/*  ключевые  слова  длины  3 */

#define   casesy         31
#define   elsesy         32
#define   filesy         57
#define   gotosy         33
#define   thensy         52
#define   typesy         34
#define   withsy         37

/*  ключевые  слова   длины 4 */

#define   arraysy        38
#define   beginsy        17
#define   constsy        39
#define   labelsy        40
#define   untilsy        53
#define   whilesy        41

/*  ключевые  слова   длины  5 */

#define   downtosy        55
#define   packedsy        42
#define   recordsy        43
#define   repeatsy        44

/*  ключевые  слова    длины 6 */

#define   programsy        3

/*  ключевые  слова    длины 7 */

#define   functionsy      77

/*  ключевые  слова    длины 8 */

#define  proceduresy      80

struct key
{
	unsigned codekey;
	char namekey[10];
} keywords[] =
{
	{ ident, " " },
	{ dosy, "do" },
	{ ifsy, "if" },
	{ insy, "in" },
	{ ofsy, "of" },
	{ orsy, "or" },
	{ tosy, "to" },
	{ ident, " " },
	{ endsy,"end" },
	{ varsy,"var" },
	{ divsy,"div" },
	{ andsy,"and" },
	{ notsy,"not" },
	{ forsy,"for" },
	{ modsy,"mod" },
	{ nilsy,"nil" },
	{ setsy,"set" },
	{ ident, " " },
	{ thensy,"then" },
	{ elsesy,"else" },
	{ casesy,"case" },
	{ filesy,"file" },
	{ gotosy,"goto" },
	{ typesy,"type" },
	{ withsy,"with" },
	{ ident, " " },
	{ beginsy,"begin" },
	{ whilesy,"while" },
	{ arraysy,"array" },
	{ constsy,"const" },
	{ labelsy,"label" },
	{ untilsy,"until" },
	{ ident, " " },
	{ downtosy,"downto" },
	{ packedsy,"packed" },
	{ recordsy,"record" },
	{ repeatsy,"repeat" },
	{ ident, " " },
	{ programsy,"program" },
	{ ident, " " },
	{ functionsy,"function" },
	{ ident, " " },
	{ proceduresy,"procedure" },
	{ ident, " " }
};
int last[] =
{ -1, 0, 7, 17, 25, 32, 37, 39, 41, 43 };
