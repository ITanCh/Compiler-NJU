all:
	bison -d -v la.y
	flex la.l
	gcc -Wall -pedantic -std=c99 -g la.tab.c table.c node.c intercode.c -lfl -o parser
