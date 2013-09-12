CC = g++
FLAGS = -Wall
LIBS = 
FRAMEWORKS = 
TARGET = libGL.a
OBJ = Program.o Shader.o BufferObject.o VertexArray.o

.PHONY:
$(TARGET): $(OBJ)
	ar -rcs $(TARGET) $(OBJ)
	rm *.o 

%.o: %.cpp
	$(CC) -c $< $(FLAGS)