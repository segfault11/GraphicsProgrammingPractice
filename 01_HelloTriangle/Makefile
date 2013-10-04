CC = g++
FLAGS = -Wall
LIBS = libFramework.a -lGLEW -lGL -lGLU -lSDL2 
FRAMEWORKS =
TARGET = HelloTriangle
OBJ = Triangle.o

.PHONY:
$(TARGET): Main.cpp $(OBJ)
	cd Framework;make;cp libFramework.a ..
	$(CC) -o $(TARGET) Main.cpp  $(OBJ)  $(LIBS) $(FLAGS) 
	rm *.o

%.o: %.cpp
	$(CC) -c $< $(FLAGS)
