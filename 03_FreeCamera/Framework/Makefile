CC = g++
FLAGS = -Wall
LIBS = 
FRAMEWORKS = 
TARGET = libFramework.a
OBJ = ICameraObserver.o IRenderer.o IObject.o IEventHandler.o Application.o File.o Mesh.o TmpMesh.o Program.o Shader.o BufferObject.o VertexArray.o Perspective.o Camera.o
DOBJ = Error.o

.PHONY:
$(TARGET): $(DOBJ)
	cd OBJ; $(CC) -c *.cpp; mv *.o ..
	cd GL; $(CC) -c *.cpp; mv *.o ..
	cd SDL; $(CC) -c *.cpp; mv *.o ..
	ar -rcs $(TARGET) $(OBJ) $(DOBJ)
	rm *.o 								
	
%.o: %.cpp
	$(CC) -c $< $(FLAGS)

Error.o:
	cd Error; make; mv Error.o ..
	