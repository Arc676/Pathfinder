CC=g++
STD=c++17
FLAGS=-std=$(STD) -c
OBJS=node.o graph.o pathfinder.o edge.o
OUT=libgraph.a

ifdef DEBUG
	FLAGS += -O0 -g
	OUT=libgraphd.a
endif

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
