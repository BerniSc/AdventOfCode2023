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

    bernhard << replaceStringRegex("[a-z]", "");
    
    bernhard_part_two << replaceStringRegex("one", "o1e") << replaceStringRegex("two", "t2o") << replaceStringRegex("three", "t3e") << replaceStringRegex("four", "f4r");
    bernhard_part_two << replaceStringRegex("five", "f5e") << replaceStringRegex("six", "s6x") << replaceStringRegex("seven", "s7n") << replaceStringRegex("eight", "e8t");
    bernhard_part_two << replaceStringRegex("nine", "n9e") << replaceStringRegex("[a-z]", "");
    
    // Print out actual readin Data
    //  std::cout << bernhard << std::endl;
    //  std::cout << bernhard_part_two << std::endl;

    // processData(bernhard);    
    
    // Lol -> completly unneccesary... just read the Task wrong and assumed that oneight should only match one -> result completly wrong
    // After a lot of fruitless debugging and useless functions just did it this way and it worked instantly...
    // A really great Start :-)
    processData(bernhard_part_two);
    //processDataPartTwo(bernhard_part_two);

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

// I am useless :-)   you can delete me
void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    int accumulator = 0;

    std::regex pattern("(one|two|three|four|five|six|seven|eight|nine)");

    for(std::vector<std::string>& paragraph : myModifiedData) {
        for(std::string& string : paragraph) {
            // Loop to find and replace matches
            std::smatch match;
            std::stringstream stringBuilder;

            while(std::regex_search(string, match, pattern)) {  
                // Matched text
                std::string matched = match.str(0);

                // Replace with corresponding values -> Quick and Dirty
                if(matched == "one") string.replace(match.position(), match.length() - 1, "1");
                else if(matched == "two") string.replace(match.position(), match.length() - 1, "2");
                else if(matched == "three") string.replace(match.position(), match.length() - 1, "3");
                else if(matched == "four") string.replace(match.position(), match.length() - 1, "4");
                else if(matched == "five") string.replace(match.position(), match.length() - 1, "5");
                else if(matched == "six") string.replace(match.position(), match.length() - 1, "6");
                else if(matched == "seven") string.replace(match.position(), match.length() - 1, "7");
                else if(matched == "eight") string.replace(match.position(), match.length() - 1, "8");
                else if(matched == "nine") string.replace(match.position(), match.length() - 1, "9");
            }

            // Remove Superflous characters as my function would have done -> TODO... Extend Function
            std::stringstream _string;
            std::regex_replace(std::ostream_iterator<char>(_string), string.begin(), string.end(), std::regex("[a-z]"), "");
            string = _string.str();

            std::string tmp = "";
            tmp += string.at(0);
            tmp += string.at(string.length() - 1);
            
            // std::cout << string << "\t" << tmp << '\n';
    
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