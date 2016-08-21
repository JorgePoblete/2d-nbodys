SRC_FOLDER=./src/
SRC_FILES=nbody.cpp quadtree.cpp allegro_ui.cpp program_options.cpp main.cpp
SRC=$(addprefix $(SRC_FOLDER),$(SRC_FILES))
OBJ=$(SRC:.cpp=.o)
CC=g++
CCFLAGS=-Wall -std=c++11 -O3 -ffast-math
EXEFLAGS=-xHost
OBJFLAGS=-c
LDLIBS=-lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -fopenmp
EXE=nbody_simulator

$(VERBOSE).SILENT:

all: $(SRC) $(EXE)
	rm -f $(SRC_FOLDER)*.o

.cpp.o:
	$(CC) $(OBJFLAGS) $(CCFLAGS) $(LDLIBS) $< -o $@

$(EXE): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(LDLIBS) $(EXEFLAGS) -o $(EXE)

clean:
	rm -f $(SRC_FOLDER)*.o $(EXE)	
