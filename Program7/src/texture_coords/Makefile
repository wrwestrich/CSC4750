
HEADER 	:= $(wildcard *.h)
FILES 	:= $(wildcard *.cpp)
OBJ 	:= $(patsubst %.cpp,%.o,$(wildcard *.cpp))

TARGET := texture_program

.PHONY: all clean run

clean:
	$(RM) *.o
	$(RM) %(TARGET)

run: all
	./$(TARGET) ../../data/sphere.txt ../../data/sphere_texture.txt

all: $(TARGET)

$(TARGET): $(OBJ)
	$(LINK) $(TARGET) texture_coords.o $(LIBS)

texture_coords.o: texture_coords.cpp
	$(COMPILE) texture_coords.cpp