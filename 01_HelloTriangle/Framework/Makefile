CC = g++
FLAGS = -Wall
LIBS = -lGLEW 
FRAMEWORKS = -framework OpenGL -framework SDL2
TARGET = libFramework.a
OBJ = SDLApplication.o Program.o Shader.o Error.o BufferObject.o VertexArray.o

.PHONY:
$(TARGET): $(OBJ)
	ar -rcs $(TARGET) $(OBJ)
	rm *.o 

%.o: %.cpp
	$(CC) -c $< $(FLAGS)
