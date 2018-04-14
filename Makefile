CC=g++
FLAGS=-std=c++11 -c
OBJS=node.o graph.o pathfinder.o edge.o
OUT=libgraph.a

debug: FLAGS += -O0 -g
debug: OUT=libgraphd.a
debug: lib

lib: $(OBJS)
	ar rcs $(OUT) $(OBJS)

node.o:
	$(CC) $(FLAGS) node.cpp

graph.o:
	$(CC) $(FLAGS) graph.cpp

pathfinder.o:
	$(CC) $(FLAGS) pathfinder.cpp

edge.o:
	$(CC) $(FLAGS) edge.cpp

clean:
	rm -f libgraph.a libgraphd.a $(OBJS)
