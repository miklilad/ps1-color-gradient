
lorem="Lorem ipsum dolor sit amet, consectetuer adipiscing elit. In convallis. Quis autem vel eum iure reprehenderit"


all: run

compile: gradient.c
	gcc -O2 -pedantic -Wall gradient.c -o .gradient.out -lm
	
debug_compile: gradient.c
	gcc -g -pedantic -Wall gradient.c -o .gradient.out -lm
	
run: compile
	@./.gradient.out --rgb "151,100,100" "172,100,100" "Successfully compiled!"
	
example: compile
	@./.gradient.out "0,100,100" "120,100,100" ${lorem}; echo
	@./.gradient.out "120,100,100" "240,100,100" ${lorem}; echo
	@./.gradient.out "240,100,100" "360,100,100" ${lorem}; echo
	@./.gradient.out "0,100,100" "360,100,100" ${lorem}; echo
	@./.gradient.out "0,100,100" "720,100,100" ${lorem}; echo
	@./.gradient.out --rgb "0,100,100" "120,100,100" ${lorem}; echo
	@./.gradient.out --rgb "120,100,100" "240,100,100" ${lorem}; echo
	@./.gradient.out --rgb "240,100,100" "360,100,100" ${lorem}; echo
	@./.gradient.out "240,100,100" "240,0,100" ${lorem}; echo
	@./.gradient.out "240,100,100" "240,100,0" ${lorem}; echo
	@./.gradient.out "240,100,100" "240,0,0" ${lorem}; echo
	@./.gradient.out "240,100,100" "240,50,50" ${lorem}; echo
	@./.gradient.out --rgb "240,100,100" "240,0,100" ${lorem}; echo
	@./.gradient.out --rgb "240,100,100" "240,100,0" ${lorem}; echo
	@./.gradient.out --rgb "240,100,100" "240,0,0" ${lorem}; echo
	@./.gradient.out --rgb "240,100,100" "240,50,50" ${lorem}; echo

	
debug: debug_compile
	gdb -tui --args ./.gradient.out ${lorem} 

