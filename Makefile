webstore: main.o
	g++ main.o -o webstore
main.o: main.cpp
	g++ -c main.cpp
