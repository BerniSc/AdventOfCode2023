#include "aocHelper.hpp"

#include <regex>

#include <unordered_set>

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

    //bernhard_part_two << "example.txt";
    bernhard_part_two << "puzzle_input.txt";

    std::vector<int> indices;
    
    bernhard << replaceStringRegex("[^0-9|\\s+]", "") << replaceStringRegex("^\\s+", "") << replaceStringRegex("\\s+", " ");

    bernhard_part_two << replaceStringRegex("[^0-9]", "");// << replaceStringRegex("^\\s+", "") << replaceStringRegex("\\s+", " ");

    // Print out actual readin Data
    //std::cout << bernhard << std::endl;
    std::cout << bernhard_part_two << std::endl;

    //processData(bernhard);    
    
    processDataPartTwo(bernhard_part_two);

    //bernhard << tokenizeData(&tokenizedData, " ");

    //printTokenizedData(tokenizedData);

    return 0;
}

struct Race {
    long long time;
    long long distance;

    Race(long long time) : time(time), distance(-1) {

    }

    long long getNumberWinningScores() {
        long long res = 0;
        for(long long timeIterator = 1; timeIterator < time - 1; timeIterator++) {
            res += (getDistanceTraveled(timeIterator) > distance ? 1 : 0);
        }
        return res;
    }

    long long getDistanceTraveled(long long timePressed) {
        long long timeTraveled = time - timePressed;
        //std::cout << timePressed <<"    " << timeTraveled * timePressed << "\n";
        return timeTraveled * timePressed;
    }
};

void processData(InputData& data) {
    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    printTokenizedData(tokenizedData);

    int accumulator = 1;

    std::vector<std::vector<std::string>> myModifiedData = tokenizedData[0];

    std::vector<Race> races;

    for(int i = 0; i < myModifiedData[0].size(); i++) {
        races.push_back(Race(stol(myModifiedData[0][i])));
    }

    for(int i = 0; i < myModifiedData[1].size(); i++) {
        races.at(i).distance = (stol(myModifiedData[1][i]));
    }

    for(Race race : races)
        accumulator *= race.getNumberWinningScores();
            

    std::cout << "Your solution to part one is: " << accumulator << "\n";
}

void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    printTokenizedData(tokenizedData);

    long long accumulator = 1;

    std::vector<std::vector<std::string>> myModifiedData = tokenizedData[0];

    std::vector<Race> races;

    for(int i = 0; i < myModifiedData[0].size(); i++) {
        races.push_back(Race(stol(myModifiedData[0][i])));
    }

    for(int i = 0; i < myModifiedData[1].size(); i++) {
        races.at(i).distance = (stol(myModifiedData[1][i]));
    }

    for(Race race : races)
        accumulator *= race.getNumberWinningScores();
            

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