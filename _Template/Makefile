COMPILER = "g++"
PROJECTNAME = aoc_solution
INCLUDE_HELPER = ../_Helper/inc/
SOURCE_HELPER = ../_Helper/src/aocHelper.cpp ../_Helper/src/inputDataOperations.cpp
SOURCE = main.cpp $(SOURCE_HELPER)
FLAGS = -std=c++17 -pthread

$(PROJECTNAME) : $(SOURCE)
		$(COMPILER) $(SOURCE) $(FLAGS) -I$(INCLUDE_HELPER) -o $(PROJECTNAME)

.PHONY: clean run
clean:
		rm ./$(aoc_solution)

run:
        ./$(PROJECTNAME)
