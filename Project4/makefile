## 11/22 Vishal Indivar Kandala
## MEEN 689 Computing  Concepts Project 3
CC=g++
CFLAGS=  # -g -Wall 
#DEPS = 
OBJ = main.o setup.o solver.o data.o 

%.o: %.cpp #$(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

1dheat: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	$(RM) *.o
all: 1dheat clean

