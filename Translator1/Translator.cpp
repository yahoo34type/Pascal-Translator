#include "Lexical.h"
void main()
{
	/*ImportErrors();
	positionnow.linenumber = 1;
	positionnow.charnumber = 0;
	ReadNextLine();
	while (nextch())
		cout << ch;
	OUT.close();
	cout << endl;*/
	positionnow.linenumber = 1;
	positionnow.charnumber = 0;
	ReadNextLine();
	nextch();
	int y = 0;
	while (nextsym())
		cout << y++ << "\n";
	nextch();
	OUT.close(); cout << endl;
}