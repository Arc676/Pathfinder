CC=g++
FLAGS=-std=c++11 -c
OBJS=node.o graph.o pathfinder.o

lib: $(OBJS)
	ar rcs libgraph.a $(OBJS)

node.o:
	$(CC) $(FLAGS) node.cpp

graph.o:
	$(CC) $(FLAGS) graph.cpp

pathfinder.o:
	$(CC) $(FLAGS) pathfinder.cpp

clean:
	rm -f libgraph.a $(OBJS)
