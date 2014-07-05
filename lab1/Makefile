all:
	bison -d -v la.y
	flex la.l
	gcc -g la.tab.c node.c -lfl -o parser
