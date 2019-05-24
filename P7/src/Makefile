
HEADER := $(wildcard *.h)
FILES  := $(wildcard *.cpp)
OBJ    := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

TARGET = P7

.PHONY: all clean run

all: $(TARGET)

	$(MAKE) -C ./texture_coords run

run: all

	./$(TARGET)

clean:

	$(RM) $(OBJ) $(TARGET)

$(TARGET): $(OBJ) $(HEADER) $(FILES)

	$(LINK) $(TARGET) $(OBJ) $(LIBS)

AffineTransforms.o:	AffineTransforms.h AffineTransforms.cpp
			$(COMPILE) AffineTransforms.cpp

Color.o:		Color.h Color.cpp
			$(COMPILE) Color.cpp

Light.o:		Light.h Light.cpp
			$(COMPILE) Light.cpp

Face.o:			Face.h Face.cpp
			$(COMPILE) Face.cpp

Vertex.o:		Vertex.h Vertex.cpp
			$(COMPILE) Vertex.cpp

Pixel.o:		Pixel.h Pixel.cpp
			$(COMPILE) Pixel.cpp

BasicObject.o:		BasicObject.h BasicObject.cpp
			$(COMPILE) BasicObject.cpp
			
DeleteObject.o:		DeleteObject.h DeleteObject.cpp
			$(COMPILE) DeleteObject.cpp
			
InstanceObject.o:	InstanceObject.h InstanceObject.cpp
			$(COMPILE) InstanceObject.cpp
			
Scene.o:			Scene.h Scene.cpp
			$(COMPILE) Scene.cpp
			
Node.o:				Node.h Node.cpp
			$(COMPILE) Node.cpp
			
Vector.o:			Vector.h Vector.cpp
			$(COMPILE) Vector.cpp

Texture.o:			Texture.h Texture.cpp
			$(COMPILE) Texture.cpp
			
TransformNode.o:	TransformNode.h TransformNode.cpp
			$(COMPILE) TransformNode.cpp

Picture.o:		Picture.h Picture.cpp
			$(COMPILE) Picture.cpp

Window.o:		Window.h Window.cpp
			$(COMPILE) Window.cpp

main.o:			main.cpp
			$(COMPILE) main.cpp
