#include "aocHelper.hpp"

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

int main() {
    // Read the Data in using mode 1 from File "input_test.txt" -> TODO Exception and Mode Diff.
    InputData bernhard(1);
    bernhard << "input_test.txt";

    std::vector<int> indices;

    // Print out actual readin Data
    std::cout << bernhard << std::endl;

    processData(bernhard);    

    bernhard << tokenizeData(&tokenizedData, " ");

    printTokenizedData(tokenizedData);

    return 0;
}

void processData(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    for(std::vector<std::string> paragraph : myModifiedData) {
        for(std::string string : paragraph) {
            
        }
    }
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