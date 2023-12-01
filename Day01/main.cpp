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

    std::vector<int> indices;

    bernhard << replaceStringRegex("[a-z]", "");
    
    // bernhard_part_two << replaceStringRegex("one", "1") << replaceStringRegex("two", "2") << replaceStringRegex("three", "3") << replaceStringRegex("four", "4");
    // bernhard_part_two << replaceStringRegex("five", "5") << replaceStringRegex("six", "6") << replaceStringRegex("seven", "7") << replaceStringRegex("eight", "8");
    // bernhard_part_two << replaceStringRegex("nine", "9");
    
    // Print out actual readin Data
    //  std::cout << bernhard << std::endl;
    std::cout << bernhard_part_two << std::endl;

    // processData(bernhard);    

    processDataPartTwo(bernhard_part_two);

    //bernhard << tokenizeData(&tokenizedData, " ");

    //printTokenizedData(tokenizedData);

    return 0;
}

void processData(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    int accumulator = 0;

    for(std::vector<std::string> paragraph : myModifiedData) {
        for(std::string string : paragraph) {
            std::string tmp = "";
            tmp += string.at(0);
            tmp += string.at(string.length()- 1);
            accumulator += stoi(tmp);
        }
    }

    std::cout << "Your solution is: " << accumulator << "\n";
}

void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    int accumulator = 0;

    std::regex pattern("(one|two|three|four|five|six|seven|eight|nine|[0-9])");

    for(std::vector<std::string>& paragraph : myModifiedData) {
        for(std::string& string : paragraph) {
            // Loop to find and replace matches
            std::smatch match;
            std::stringstream stringBuilder;
            while(std::regex_search(string, match, pattern)) {  
                // Matched text
                std::string matched = match.str(0);

                // Replace with corresponding values -> Quick and Dirty
                // if(matched == "one") string.replace(match.position(), match.length(), "1");
                // else if(matched == "two") string.replace(match.position(), match.length(), "2");
                // else if(matched == "three") string.replace(match.position(), match.length(), "3");
                // else if(matched == "four") string.replace(match.position(), match.length(), "4");
                // else if(matched == "five") string.replace(match.position(), match.length(), "5");
                // else if(matched == "six") string.replace(match.position(), match.length(), "6");
                // else if(matched == "seven") string.replace(match.position(), match.length(), "7");
                // else if(matched == "eight") string.replace(match.position(), match.length(), "8");
                // else if(matched == "nine") string.replace(match.position(), match.length(), "9");

                if(matched == "one") stringBuilder << "1";
                else if(matched == "two") stringBuilder << "2";
                else if(matched == "three") stringBuilder << "3";
                else if(matched == "four") stringBuilder << "4";
                else if(matched == "five") stringBuilder << "5";
                else if(matched == "six") stringBuilder << "6";
                else if(matched == "seven") stringBuilder << "7";
                else if(matched == "eight") stringBuilder << "8";
                else if(matched == "nine") stringBuilder << "9";
                else stringBuilder << matched << matched;

                // Move to the next match, considering overlapping matches
                string = match.suffix();
            }

            std::string tmp = "";
            tmp += stringBuilder.str().at(0);
            tmp += stringBuilder.str().at(stringBuilder.str().length() - 1);
            
            std::cout << stringBuilder.str() << "\t" << tmp << '\n';
    
            accumulator += stoi(tmp);
        }
    }
    
    std::cout << "Your solution to Part 2 is: " << accumulator << "\n";
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