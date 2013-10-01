CC = g++
FLAGS = -Wall
LIBS = 
FRAMEWORKS = 
TARGET = libFramework.a
OBJ = BufferObject.o GUIElement.o TextureAtlas.o IObject.o IEventHandler.o Application.o File.o Mesh.o TmpMesh.o Program.o Shader.o VertexArray.o Perspective.o Camera.o
DOBJ = Error.o

.PHONY:
$(TARGET): $(DOBJ)
	cd OBJ; $(CC) -g -c *.cpp; mv *.o ..
	cd GL; $(CC) -g -c *.cpp; mv *.o ..
	cd APP; $(CC) -g -c *.cpp; mv *.o ..
	ar -rcs $(TARGET) $(OBJ) $(DOBJ)
	rm *.o 								
	
%.o: %.cpp
	$(CC) -c $< $(FLAGS)

Error.o:
	cd Error; make; mv Error.o ..
	
