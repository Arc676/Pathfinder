CC=g++
FLAGS=-std=c++11 -c
OBJS=node.o graph.o

lib:
	ar rcs libgraph.a $(OBJS)

node.o:
	$(CC) $(FLAGS) node.cpp

graph.o:
	$(CC) $(FLAGS) graph.cpp

clean:
	rm -f libgraph.a $(OBJS)
