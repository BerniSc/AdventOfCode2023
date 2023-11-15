COMPILER = "g++"
PROJECTNAME = test
SOURCE = main.cpp aocHelper.cpp
FLAGS = -std=c++17 -pthread

$(PROJECTNAME) : $(SOURCE)
		$(COMPILER) $(SOURCE) $(FLAGS) -o $(PROJECTNAME)