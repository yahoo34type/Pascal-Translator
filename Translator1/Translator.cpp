#include "Syntax.h"
void syntax()
{
	nextsym();
	programme();
	/*while (positionnow.charnumber != LastInLine)
		nextch();
	nextch();*/
}
void lexic()
{
	while (nextsym())
		cout << symbol << " in position " << token.linenumber << "," << token.charnumber << "\n";
}
void main()
{
	positionnow.linenumber = 1;
	positionnow.charnumber = 0;
	ReadNextLine();
	nextch();
	syntax();
	//lexic();
	nextch();
	OUT.close(); cout << endl;
}