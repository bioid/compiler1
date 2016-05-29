#include "SymbolTable.h"

symbol *SymbolTable::addSymbol(char *name, char *type) {
	if (this->st.find(name) == this->st.end()) {
		symbol *record = new symbol;
		record->identifier = name;
		record->type = type;
		this->st[name] = record;
		return this->st[name];
	}
	return NULL; 		
}

symbol *SymbolTable::getSymbol(char* name) {
	if (this->st.find(name) == this->st.end()) {
		return NULL;
	}
	return this->st[name];
}

int SymbolTable::setValue(char* name, int val) {
	if (this->st.find(name) == this->st.end()) {
		return -1;
	}
	int *ptr = new int;
	*ptr = val;
	this->st[name]->val = ptr;
	return 0;
}

