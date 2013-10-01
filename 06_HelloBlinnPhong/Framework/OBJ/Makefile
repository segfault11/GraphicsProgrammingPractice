CC = g++
FLAGS = -Wall
LIBS = 
FRAMEWORKS = 
TARGET = libOBJ.o
OBJ = File.o TmpMesh.o

.PHONY:
$(TARGET): $(OBJ)
	ar -rcs $(TARGET) $(OBJ)
	rm *.o 

%.o: %.cpp
	$(CC) -c $< $(FLAGS)