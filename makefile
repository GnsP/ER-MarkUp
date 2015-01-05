CC=g++
HEADERS=lexer.hpp includes.hpp parser.hpp structure.hpp symbolTable.hpp sstream.hpp
OBJ=lexer.o parser.o main.o globals.o codegen.o
CFLAGS=-fpermissive
all:erdcc clean
	
erdcc:$(OBJ)
		$(CC) $(OBJ) -o $@ $(CFLAGS)

%.o:%.cpp $(HEADERS)
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
