AutomatedMakefile := am

# compiler information
CC      := g++
CCFLAGS := -g -std=c++11 -O0 -pedantic -Wall -Wextra
AR 		:= ar -r

SYS := $(shell $(CC) -dumpmachine)

.PHONY: all run clean program setup

all: program

run: program

	$(MAKE) -C ./src run

clean: setup

	$(MAKE) -C ./src clean

program: setup

	$(MAKE) -C ./src all

setup:

ifneq (, $(findstring apple, $(SYS)))
# Do apple things
$(info System detected to be Mac OS X)

INC_DIRS := -I$(PROJECT_DIR)/include -I/usr/local/include
LIB_DIRS := -L/usr/local/lib -L$(PROJECT_DIR)
LIBS 	 :=  -lCSC1310Unix -framework OpenGL -framework GLUT 

RM 		 := rm -f
MV 		 := mv
MAKE 	 := make

else ifneq (, $(findstring mingw, $(SYS)))
# Do mingw things
$(info System detected to be Windows MinGW)

INC_DIRS := -I$(PROJECT_DIR)/../include -I$(DRIVE_LETTER)/TDM-GCC-64/include
LIB_DIRS := -L$(PROJECT_DIR)/../ -L$(DRIVE_LETTER)/TDM-GCC-64/lib
LIBS 	 := -lCSC1310 -lfreeglut -lopengl32

RM   	 := del
MV 		 := copy /Y 
MAKE 	 := mingw32-make

else ifneq (, $(findstring linux, $(SYS)))
# Do linux things
$(info System detected to be GNU/Linux)

INC_DIRS := -I$(PROJECT_DIR)/include 
LIB_DIRS := -L/usr/local/lib -L/opt/X11/lib
LIBS 	 := -lCSC1310Unix

RM 		 := rm -f
MV 		 := mv
MAKE 	 := make

$(error Set LIBS and INC_DIRS flags first before trying to build on Linux!)

else 
# Do other things
$(error Unrecongized OS)

endif

#how we build things
COMPILE := $(CC) $(CCFLAGS) $(INC_DIRS) -c
LINK := $(CC) $(LIB_DIRS) -o

#export variables so that make chains can have them
export
