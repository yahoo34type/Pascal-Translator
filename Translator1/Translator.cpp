#include "Syntax.h"
void main()
{
	positionnow.linenumber = 1;
	positionnow.charnumber = 0;
	ReadNextLine();
	nextch();
	int y = 0;
	while (nextsym())
		cout << symbol << " in position " << token.linenumber << "," << token.charnumber << "\n";
	nextch();
	OUT.close(); cout << endl;
}