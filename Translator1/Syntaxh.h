#pragma once
void idknextsym();
bool belong(unsigned symbol, unsigned followers[]);
void dis(unsigned one[], unsigned two[], unsigned *&res);
void skipto(unsigned followers[]);
void skipto2(unsigned starters[], unsigned followers[]);
void accept(unsigned symbolexpected
/* код ожидаемого символа */);
void block(unsigned *followers);
void programme();
void constant(unsigned *followers);
void whilestatement(unsigned *followers);
void forstatement(unsigned *followers);
void repeatstatement(unsigned *followers);
void compoundstatement(unsigned *followers);
void varpart(unsigned *followers);
void vardeclaration(unsigned *followers);
void type(unsigned *followers);
void simpletype(unsigned *followers);
void unpackedcompositetype(unsigned *followers);
void numtype(unsigned *followers);
void multipletype(unsigned *followers);
void limtype(unsigned *followers);
void regtype(unsigned *followers);
void combtype(unsigned *followers);
void fieldlist(unsigned *followers);
void variativesection(unsigned *followers);
void variant(unsigned *followers);
void recordsection(unsigned *followers);
void variable(unsigned *followers);
void ifstatement(unsigned *followers);
void casestatement(unsigned *followers);
void caseelement(unsigned *followers);
void labelpart();
void statementpart(unsigned *followers);
void statement(unsigned *followers);
void connstatement(unsigned *followers);
void cyclestatement(unsigned *followers);
void expression(unsigned *followers);
void simpleexpression(unsigned *followers);
void addend(unsigned *followers);
void mult(unsigned *followers);
void constpart(unsigned *followers);
void typepart(unsigned *followers);
void procfuncpart(unsigned *followers);
void procedureheader(unsigned *followers);
void functionheader(unsigned *followers);
void fparametermodule(unsigned *followers);
void paramgroup(unsigned *followers);
/*void factparameter(unsigned *followers)
{
	//cout << "fparam\n";
		expression();
}*/