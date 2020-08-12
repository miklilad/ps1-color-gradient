

all: run

compile: gradient.c
	gcc -O2 -pedantic -Wall gradient.c -o gradient.out -lm
	
debug_compile: gradient.c
	gcc -g -pedantic -Wall gradient.c -o gradient.out -lm
	
run: compile
	./gradient.out "0,100,100" "120,100,100" ${PWD}
	./gradient.out "120,100,100" "240,100,100" ${PWD}
	./gradient.out "240,100,100" "360,100,100" ${PWD}
	./gradient.out "0,100,100" "360,100,100" ${PWD}
	
debug: debug_compile
	gdb -tui --args ./gradient.out ${PWD} 

