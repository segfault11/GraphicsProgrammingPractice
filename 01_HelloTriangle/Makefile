CC = g++
FLAGS = -Wall
LIBS = -lGLEW libFramework.a
FRAMEWORKS = -framework OpenGL -framework SDL2
TARGET = HelloTriangle
OBJ = Triangle.o 

.PHONY:
$(TARGET): Main.cpp $(OBJ)
	cd Framework;make;cp libFramework.a ..
	$(CC) -o $(TARGET) Main.cpp $(OBJ) $(FLAGS) $(LIBS) $(FRAMEWORKS) 
	rm *.o

%.o: %.cpp
	$(CC) -c $< $(FLAGS)
