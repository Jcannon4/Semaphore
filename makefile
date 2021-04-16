CC = g++ -std=c++11
STRUCTS = io.o production.o belt.o producer.o consumer.o 

mizzo: driver.cpp ${STRUCTS} 
	${CC} -g -o mizzo driver.cpp io.o production.o belt.o producer.o consumer.o -lpthread
	rm io.o production.o belt.o producer.o consumer.o
io.o: io.c io.h
	${CC} -w -o io.o -c io.c
production.o: production.cpp production.h
	${CC} -c production.cpp 
belt.o : belt.cpp belt.h
	${CC} -c belt.cpp 
producer.o : producer.cpp producer.h
	${CC} -c producer.cpp 
consumer.o: consumer.cpp consumer.h
	${CC} -c consumer.cpp 


# mizzo: driver.cpp belt.cpp producer.cpp consumer.cpp production.cpp io.c
# 	g++ -o mizzo -g driver.cpp belt.cpp producer.cpp consumer.cpp io.c production.cpp  -lpthread -lrt

clean :
	rm mizzo