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

    //bernhard_part_two << "example.txt";
    bernhard_part_two << "puzzle_input.txt";

    std::vector<int> indices;
    
    // Print out actual readin Data
    std::cout << bernhard << std::endl;
    //  std::cout << bernhard_part_two << std::endl;

    //processData(bernhard);    
    
    processDataPartTwo(bernhard_part_two);

    //bernhard << tokenizeData(&tokenizedData, " ");

    //printTokenizedData(tokenizedData);

    return 0;
}

struct OasisData {
    std::vector<int> readData;

    void addData(int i) {
        readData.push_back(i);
    }

    int getAnomaly() {
        int iteration = 0;
        bool stillGoing;
        do {
            stillGoing = false;
            for(int i = 0; i < readData.size() - 1 - iteration; i++) {
                int val = readData[i + 1] - readData[i];
                readData[i] = val;
                if(val) stillGoing = true;
            }
            iteration++;
        } while(stillGoing);

        int accumulator = 0;
        for(int i = 0; i < iteration; i++)
            accumulator += readData[readData.size() - 1 - i];

        return accumulator;
    }

    int getAnomalyPartTwo() {
        std::reverse(readData.begin(), readData.end());

        int iteration = 0;
        bool stillGoing;
        do {
            stillGoing = false;
            for(int i = 0; i < readData.size() - 1 - iteration; i++) {
                int val = readData[i] - readData[i + 1];
                readData[i] = val;
                if(val) stillGoing = true;
            }
            iteration++;
        } while(stillGoing);

        int accumulator = 0;
        for(int i = iteration - 1; i >= 0; i--)
            accumulator = (readData[readData.size() - 1 - i] - accumulator);

        return accumulator;
    }
};

void processData(InputData& data) {
    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    printTokenizedData(tokenizedData);

    std::vector<std::vector<std::string>> myModifiedData = tokenizedData[0];

    int accumulator = 0;
    
    for(std::vector<std::string> line : myModifiedData) {
        OasisData tmp;
        for(std::string number : line)
            tmp.addData(stol(number));
        accumulator += tmp.getAnomaly();
    }
    

    std::cout << "Your solution to part one is: " << accumulator << "\n";
}

void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    printTokenizedData(tokenizedData);

    std::vector<std::vector<std::string>> myModifiedData = tokenizedData[0];

    int accumulator = 0;
    
    for(std::vector<std::string> line : myModifiedData) {
        OasisData tmp;
        for(std::string number : line)
            tmp.addData(stol(number));
        accumulator += tmp.getAnomalyPartTwo();
    }

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