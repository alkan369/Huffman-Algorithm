output: main.o HTree.o Encoder.o System.o Menu.o
	g++ main.o HTree.o Encoder.o System.o Menu.o -o output

main.o: main.cpp
	g++ -c main.cpp

Htree.o: HTree.cpp HTree.h
	g++ -c HTree.cpp

Encoder.o: Encoder.cpp Encoder.h
	g++ -c Encoder.cpp

System.o: System.cpp System.h
	g++ -c System.cpp

Menu.o: Menu.cpp Menu.h
	g++ -c Menu.cpp