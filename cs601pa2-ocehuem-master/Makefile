# Compiler and flags
CFLAGS = -std=c++11 -g -Wall
CXX = g++

# Directory structure
SRC=./src
INC=./inc
OBJ=./obj
DOC=./doc

# Main targets
all: part1 part2

part1: directories FEMain.o FEGrid.o Element.o Node.o
	$(CXX) $(OBJ)/FEMain.o $(OBJ)/FEGrid.o $(OBJ)/Element.o $(OBJ)/Node.o -o pa5
	@echo "To run ./pa5 <prefix of file name>"

FEMain.o: $(SRC)/FEMain.cpp $(INC)/FEGrid.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/FEMain.o $(SRC)/FEMain.cpp

Node.o: $(SRC)/Node.cpp $(INC)/Node.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/Node.o $(SRC)/Node.cpp

Element.o: $(INC)/Element.h $(SRC)/Element.cpp
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/Element.o $(SRC)/Element.cpp

FEGrid.o: $(INC)/FEGrid.h $(SRC)/FEGrid.cpp $(INC)/Element.h $(INC)/Node.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/FEGrid.o $(SRC)/FEGrid.cpp

# Part II target
part2: directories RDomain.o GridFn.o Solution.o simulation.o
	$(CXX) $(OBJ)/RDomain.o $(OBJ)/GridFn.o $(OBJ)/Solution.o $(OBJ)/simulation.o -o simulation

RDomain.o: $(SRC)/RDomain.cpp $(INC)/RDomain.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/RDomain.o $(SRC)/RDomain.cpp

GridFn.o: $(SRC)/GridFn.cpp $(INC)/GridFn.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/GridFn.o $(SRC)/GridFn.cpp

Solution.o: $(SRC)/Solution.cpp $(INC)/Solution.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/Solution.o $(SRC)/Solution.cpp

simulation.o: $(SRC)/simulation.cpp $(INC)/Solution.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/simulation.o $(SRC)/simulation.cpp

# Directory creation
directories:
	@mkdir -p $(OBJ)
	@mkdir -p $(DOC)

# Clean command
clean:
	rm -f $(OBJ)/* pa5 simulation
	rm -rf $(DOC)

# Generate Doxygen documentation
doc: directories
	@if [ ! -f Doxyfile ]; then \
		doxygen -g; \
		echo "PROJECT_NAME           = \"Finite Element Method Implementation\"" >> Doxyfile; \
		echo "PROJECT_BRIEF         = \"CS601 Programming Assignment\"" >> Doxyfile; \
		echo "OUTPUT_DIRECTORY      = $(DOC)" >> Doxyfile; \
		echo "RECURSIVE             = YES" >> Doxyfile; \
		echo "EXTRACT_ALL           = YES" >> Doxyfile; \
		echo "EXTRACT_PRIVATE       = YES" >> Doxyfile; \
		echo "EXTRACT_STATIC        = YES" >> Doxyfile; \
		echo "INPUT                 = $(SRC) $(INC)" >> Doxyfile; \
		echo "FILE_PATTERNS         = *.cpp *.h" >> Doxyfile; \
		echo "GENERATE_HTML         = YES" >> Doxyfile; \
		echo "GENERATE_LATEX        = NO" >> Doxyfile; \
		echo "HAVE_DOT             = YES" >> Doxyfile; \
		echo "UML_LOOK             = YES" >> Doxyfile; \
		echo "CALL_GRAPH           = YES" >> Doxyfile; \
		echo "CALLER_GRAPH         = YES" >> Doxyfile; \
	fi
	@doxygen Doxyfile
	@echo "Documentation generated in $(DOC) directory"
	@echo "Open $(DOC)/html/index.html in your browser to view"

# Print team information
team:
	@echo "Team: [220010015:Choudari Harshitha Reddy & 220010032:Mubarakpur Keerthi], CS601 PA2 Submission"

# Declare phony targets
.PHONY: all clean obj doc team directories part1 part2
