#include "aocHelper.hpp"

#include <regex>

/**
 * Define the Instances of the String Manipulation classes
*/
TruncateString truncateString;
RemoveDuplicates removeDuplicates;
ClearEmptyRows clearEmptyRows;
ReplaceString replaceString;
ReplaceStringRegex replaceStringRegex;
InsertString insertString;
TokenizeData tokenizeData;

std::vector<std::vector<std::vector<std::string>>> tokenizedData;
void printTokenizedData(std::vector<std::vector<std::vector<std::string>>>& tokenizedData);
void processData(InputData& data);
void processDataPartTwo(InputData& data);

int main() {
    // Read the Data in using mode 1 from File "input_test.txt" -> TODO Exception and Mode Diff.
    InputData bernhard(1);
    InputData bernhard_part_two(2);
    
    //bernhard << "example.txt";
    bernhard << "puzzle_input.txt";

    bernhard_part_two << "example.txt";
    //bernhard_part_two << "puzzle_input.txt";

    std::vector<int> indices;

    // Print out actual readin Data
    std::cout << bernhard << std::endl;
    //  std::cout << bernhard_part_two << std::endl;

    processData(bernhard);    
    
    //processDataPartTwo(bernhard_part_two);

    //bernhard << tokenizeData(&tokenizedData, " ");

    //printTokenizedData(tokenizedData);

    return 0;
}

struct Galaxy {
    int x, y;
    
    Galaxy(int x, int y) : x(x), y(y) {

    }

    long long getManhattanDistance(const Galaxy& other) {
        return (abs(x - other.x) + abs(y - other.y));
    }
};

bool isGalaxyInLine(const std::string& line) {
    return std::find(line.begin(), line.end(), '#') != line.end();
}

bool isGalaxyInVertical(const std::vector<std::string>& universe, int index) {
    for(std::string line : universe) 
        if(line[index] == '#') return true;
    return false;
}

void processData(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    long long accumulator = 0;
    
    std::vector<Galaxy> galaxies;

    std::vector<int> galaxyOffets(myModifiedData[0][0].size());

    int offsetCounter = 0;
    for(int i = 0; i < myModifiedData[0][0].size(); i++) {
        if(!isGalaxyInVertical(myModifiedData[0], i))
            offsetCounter++;
        galaxyOffets[i] = i + offsetCounter;
    }

    int lineCounter = 0;
    offsetCounter = 0;
    for(std::string line : myModifiedData[0]) {
        if(!isGalaxyInLine(line)) {
            offsetCounter++;
            continue;
        }
        for(int i = 0; i < line.size(); i++) {
            if(line[i] == '#') {
                galaxies.push_back(Galaxy(galaxyOffets[i], lineCounter + offsetCounter));
            }
        }
        lineCounter++;
    }

    for(auto e : galaxies)
        std::cout << e.x << "|" << e.y << " ";

    int comb = 0;
    for(int i = 0; i < galaxies.size(); i++) {
        for(int j = i + 1; j < galaxies.size(); j++) {
            accumulator += galaxies[i].getManhattanDistance(galaxies[j]) + 1;
            comb++;
        }
    }

    std::cout << "Your solution to part one is: " << accumulator << "\tcomb" << comb << "\n";
}

void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    int accumulator = 0;
    
    
    std::cout << "Your solution to part two is: " << accumulator << "\n";
}

void printTokenizedData(std::vector<std::vector<std::vector<std::string>>>& tokenizedData) {
    for(std::vector<std::vector<std::string>> paragraph : tokenizedData) {
        for(std::vector<std::string> string : paragraph) {
            for(std::string token : string) {
                std::cout << token << "\t\t";
            }
            std::cout << "\n";
        }
        std::cout << "=== PARAGRAPH ===" << '\n';
    }
}

/**
 * Snippets
*/
// Sort Array
// std::sort(std::begin(array), std::end(array));

// String to Int
// stoi(string)