CC = g++ -std=c++11
STRUCTS = io.o production.o belt.o

mizzo: driver.cpp ${STRUCTS} 
	${CC} -g -o mizzo driver.cpp io.o production.o belt.o
	rm io.o production.o belt.o
io.o: io.c io.h
	${CC} -w -o io.o -c io.c
production.o: production.cpp production.h
	${CC} -c production.cpp
belt.o : belt.cpp belt.h
	${CC} -c belt.cpp
clean :
	rm mizzo