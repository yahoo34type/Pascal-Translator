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
#define minus 71 /* – */
#define lcomment 72 /* (* */
#define rcomment 73 /* *) */
#define assign 51 /* := */
#define twopoints 74 /* .. */
#define ident 2 /* идентификатор */
#define floatc 82 /* вещественная константа */
#define intc 15 /* целая константа */
#define charc 83 /* символьная константа */
#define stringc 101 /* строковая константа */
#define olcomment 100
#define casesy 31 
#define elsesy 32 
#define filesy 57 
#define gotosy 33 
#define thensy 52 
#define typesy 34 
#define untilsy 53 
#define dosy 54 
#define withsy 37 
#define ofsy 75 
#define orsy 76 
#define insy 77 
#define ifsy 44 
#define tosy 78 
#define endsy 79 
#define varsy 80 
#define divsy 81 
#define andsy 42 
#define notsy 43 
#define forsy 84 
#define modsy 85 
#define nilsy 86 
#define setsy 87 
#define beginsy 88 
#define whilesy 89 
#define arraysy 90 
#define constsy 91 
#define labelsy 92 
#define downtosy 93 
#define packedsy 94 
#define recordsy 95 
#define repeatsy 96 
#define programsy 97 
#define functionsy 98 
#define proceduresy 99 
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
