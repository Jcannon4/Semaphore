CC = g++ -std=c++11
STRUCTS = io.o production.o
mizzo: driver.cpp ${STRUCTS}
	${CC} -g -o mizzo driver.cpp io.o production.o
	rm io.o production.o
io.o: io.c io.h
	${CC} -w -o io.o -c io.c
production.o: production.cpp production.h
	${CC} -c production.cpp
clean :
	rm mizzo