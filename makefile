CC = g++ -std=c++11
STRUCTS = io.o belt.o producer.o consumer.o 

mizzo: driver.cpp ${STRUCTS} 
	${CC} -g -o mizzo driver.cpp io.o belt.o producer.o consumer.o -lpthread
	rm io.o belt.o producer.o consumer.o
io.o: io.c io.h production.h
	${CC} -w -o io.o -c io.c
belt.o : belt.cpp belt.h
	${CC} -c belt.cpp 
producer.o : producer.cpp producer.h
	${CC} -c producer.cpp 
consumer.o: consumer.cpp consumer.h
	${CC} -c consumer.cpp 
clean :
	rm mizzo