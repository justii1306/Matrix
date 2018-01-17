main: main.o matrix.o
	g++ -Wall $^ -o $@

matrix.o: matrix.cpp matrix.h
	g++ -c -Wall $< -o $@

main.o: main.cpp matrix.h
	g++ -c -Wall $< -o $@

.PHONY: clean

clean:
	-rm matrix.o main.o main
