

args="100,100,100" "160,100,100" ${PWD}

all: run

compile: gradient.c
	gcc -O2 -pedantic -Wall gradient.c -o gradient.out -lm
	
debug_compile: gradient.c
	gcc -g -pedantic -Wall gradient.c -o gradient.out -lm
	
run: compile
	./gradient.out ${args}
	
debug: debug_compile
	gdb -tui --args ./gradient.out ${args} 
