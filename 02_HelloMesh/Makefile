CC = g++
FLAGS = -Wall
LIBS = -lGLEW libFramework.a
FRAMEWORKS = -framework OpenGL -framework SDL2
TARGET = HelloMesh
OBJ = MeshRenderer.o

.PHONY:
$(TARGET): Main.cpp $(OBJ)
	cd Framework;make;mv libFramework.a ..
	$(CC) -o $(TARGET) Main.cpp $(OBJ) $(FLAGS) $(LIBS) $(FRAMEWORKS) 
	rm *.a

%.o: %.cpp
	$(CC) -c $< $(FLAGS)
