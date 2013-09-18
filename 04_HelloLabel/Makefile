CC = g++
FLAGS = -Wall
LIBS = -lGLEW libFramework.a -lfreetype libSOIL.a
FRAMEWORKS = -framework OpenGL -framework SDL2 -framework CoreFoundation
TARGET = HelloLabel
OBJ = 

.PHONY:
$(TARGET): Main.cpp $(OBJ)
	cd Framework;make;mv libFramework.a ..
	$(CC) -g -o $(TARGET) Main.cpp $(OBJ) $(FLAGS) $(LIBS) $(FRAMEWORKS) 
	rm libFramework.a

%.o: %.cpp
	$(CC) -c $< $(FLAGS)
