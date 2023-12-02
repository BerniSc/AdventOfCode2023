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

void processData(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    int accumulator = 0;
    
    std::vector<int> eliminatedLines;

    // Matches all Lines that have more than 12 Red cubes, more than 13 green and more than 14 blue cubes
    std::regex pattern("((1[3-9]|[2-9][0-9]) red)|((1[4-9]|[2-9][0-9]) green)|((1[5-9]|[2-9][0-9]) blue)");

    int loopCounter = 0;

    for(std::vector<std::string>& paragraph : myModifiedData) {
        for(std::string& string : paragraph) {
            // Loop to find and replace matches
            std::smatch match;
            int i = 0;
            // Matched some Shit
            while(std::regex_search(string, match, pattern)) {  
                // Matched text
                std::string matched = match.str(0);

                std::cout << matched << std::endl;

                eliminatedLines.push_back(loopCounter + 1);

                // Already finished... no other match needed
                break;
            }
            
            loopCounter++;
        }
    }

    // Only has a single Paragraph -> Checking against first element sufficient, also start at one -> instant gameID
    for(int i = 1; i <= myModifiedData[0].size(); i++) {
        // If the eliminatedLines vector does not conain our current Line add the ID 
        if(std::find(eliminatedLines.begin(), eliminatedLines.end(), i) == eliminatedLines.end())
            accumulator += i;
    }

    std::cout << "Your solution to part one is: " << accumulator << "\n";
}

// I am useless :-)   you can delete me
void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    int accumulator = 0;

    // Matches all the numbers and their origin 
    std::regex pattern("(([1-9]*[0-9] r)|([1-9]*[0-9] g)|([1-9]*[0-9] b))");

    for(std::vector<std::string>& paragraph : myModifiedData) {
        for(std::string& string : paragraph) {
            // Loop to find and replace matches
            std::smatch match;
            int i = 0;

            int r = 0, g = 0, b = 0;

            // Matched some Shit
            while(std::regex_search(string, match, pattern)) {  
                // Matched text
                std::string matched = match.str(0);

                // std::cout << matched << std::endl;

                std::string tmp = "";
                if(matched.at(match.length() - 1) == 'r') {
                    tmp = matched.substr(0, matched.size() - 2);
                    r = (stoi(tmp) > r ? stoi(tmp) : r);
                } else if(matched.at(match.length() - 1) == 'g') {
                    tmp = matched.substr(0, matched.size() - 2);
                    g = (stoi(tmp) > g ? stoi(tmp) : g);
                } else if(matched.at(match.length() - 1) == 'b') {
                    tmp = matched.substr(0, matched.size() - 2);
                    b = (stoi(tmp) > b ? stoi(tmp) : b);
                }
                string = match.suffix();
            }

            std::cout << "r: " << r << " g: " << g << " b: " << b << "  " << r*g*b <<"\n"; 
            accumulator += r * g * b;
        }
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