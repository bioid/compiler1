snapple.tab.c snapple.tab.h: snapple.y
	bison -d snapple.y

lex.yy.c: snapple.l snapple.tab.h
	flex snapple.l

snapple: lex.yy.c snapple.tab.c snapple.tab.h
	g++ snapple.tab.c SymbolTable.cc lex.yy.c -lfl -o snapple
