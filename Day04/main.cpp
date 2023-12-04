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
    
    // Truncate 0,7 für Example
    bernhard << truncateString(0, 9) << replaceString("|", ";");

    bernhard_part_two << truncateString(0, 9) << replaceString("|", ";");
    // Print out actual readin Data
    //std::cout << bernhard << std::endl;
    std::cout << bernhard_part_two << std::endl;

    //processData(bernhard);    
    
    processDataPartTwo(bernhard_part_two);

    //bernhard << tokenizeData(&tokenizedData, " ");

    //printTokenizedData(tokenizedData);

    return 0;
}

bool isStringInVector(const std::vector<std::string>& strVector, const std::string& targetString) {
    return std::find(strVector.begin(), strVector.end(), targetString) != strVector.end();
}

void processData(InputData& data) {
    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, ";");
    printTokenizedData(tokenizedData);

    std::vector<std::vector<std::string>> myModifiedData = tokenizedData[0];

    int accumulator = 0;
    
    std::regex pattern("\\s+");

    std::vector<std::vector<std::string>> collectionRhs;
    std::vector<std::vector<std::string>> collectionLhs;

    for(std::vector<std::string>& line : myModifiedData) {
        // Iterate over the String and tokenize on Regex
        std::sregex_token_iterator iter(line[0].begin(), line[0].end(), pattern, -1);
        std::sregex_token_iterator end;

        std::vector<std::string> tmp(iter, end);
        
        collectionLhs.push_back(tmp);
    }

    for(std::vector<std::string>& line : myModifiedData) {
        // Iterate over the String and tokenize on Regex
        std::sregex_token_iterator iter(line[1].begin(), line[1].end(), pattern, -1);
        std::sregex_token_iterator end;

        std::vector<std::string> tmp(iter, end);
        
        collectionRhs.push_back(tmp);
    }

    int counter = 0;
    for(std::vector<std::string>& line : collectionLhs) {
        int tmpAcc = 0;
        int ommitCounter = 0;
        for(std::string& elem : line) {
            // Skip first element
            if((!ommitCounter++)) continue;
            if(isStringInVector(collectionRhs[counter], elem))
                tmpAcc = (!tmpAcc ? 1 : 2 * tmpAcc);

        }
        accumulator += tmpAcc;
        counter++;
    }
            

    std::cout << "Your solution to part one is: " << accumulator << "\n";
}

void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, ";");
    printTokenizedData(tokenizedData);

    std::vector<std::vector<std::string>> myModifiedData = tokenizedData[0];

    int accumulator = 0;
    std::vector<int> cards(myModifiedData.size(), 1);
    
    std::regex pattern("\\s+");

    std::vector<std::vector<std::string>> collectionRhs;
    std::vector<std::vector<std::string>> collectionLhs;

    for(std::vector<std::string>& line : myModifiedData) {
        // Iterate over the String and tokenize on Regex
        std::sregex_token_iterator iter(line[0].begin(), line[0].end(), pattern, -1);
        std::sregex_token_iterator end;

        std::vector<std::string> tmp(iter, end);
        
        collectionLhs.push_back(tmp);
    }

    for(std::vector<std::string>& line : myModifiedData) {
        // Iterate over the String and tokenize on Regex
        std::sregex_token_iterator iter(line[1].begin(), line[1].end(), pattern, -1);
        std::sregex_token_iterator end;

        std::vector<std::string> tmp(iter, end);
        
        collectionRhs.push_back(tmp);
    }

    int counter = 0;
    for(std::vector<std::string>& line : collectionLhs) {
        int tmpAcc = 0;
        int ommitCounter = 0;
        for(std::string& elem : line) {
            // Skip first element
            if((!ommitCounter++)) continue;
            if(isStringInVector(collectionRhs[counter], elem))
                tmpAcc++;

        }
        int tmp = cards[counter];
        for(int j = 0; j < tmp; j++) {
            for(int i = 1; (i <= tmpAcc) && (i + counter) < myModifiedData.size(); i++) {
                cards[i+counter]++;
            }
        }
        counter++;
    }

    for(auto e : cards) {
        accumulator += e;

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