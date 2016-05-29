#ifndef __SYMBOL_TABLE_H
#define __SYMBOL_TABLE_H
#include <map>
#include <string>

struct symbol {
	char* identifier;
	char* type;
	unsigned offset;
	void* val;
};

class SymbolTable {
public:
	std::map<std::string, symbol*> st;
	symbol *addSymbol(char* name, char* type);
	symbol *getSymbol(char* name);
	int setValue(char* name, int val);
	//int setValue(char* name, double val);
	//int setValue(char* name, char* val);
};

#endif
