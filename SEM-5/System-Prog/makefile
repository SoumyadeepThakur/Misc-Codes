test: asm_sic.o sicxe_exec.o sic_test.o
	g++ $(CFLAGS) -o sic asm_sic.o sicxe_exec.o sic_test.o
asm_sic.o: asm_sic.h asm_sic.cpp
	g++ $(CFLAGS) -c asm_sic.cpp -std=c++14
sicxe_exec.o: sicxe_exec.h sicxe_exec.cpp
	g++ $(CFLAGS) -c sicxe_exec.cpp -std=c++14
sic_test.o: sic_test.cpp asm_sic.h sicxe_exec.h
	g++ $(CFLAGS) -c sic_test.cpp -std=c++14
clean:
	rm -f *.o test
