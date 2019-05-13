CFLAGS= -Wall -fpic -coverage -lm -std=c99

tester.o: testme.c 
	gcc  testme.c -o tester.o  $(CFLAGS)


runtests: tester.o
	./tester.o

print: tester.o
	cat testme.c.gcov
	gcov -b testme.c



all: tester.o runtests print

clean:
	rm -f *.o  *.gcov *.gcda *.gcno *.so *.out 
