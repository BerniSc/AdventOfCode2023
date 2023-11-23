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

int main() {
    // Read the Data in using mode 1 from File "input_test.txt" -> TODO Exception and Mode Diff.
    InputData bernhard(1);
    bernhard << "input_test.txt";

    /*
    InputData jasmina(0);
    jasmina << "input_test.txt";

    std::vector<int> indices;

    // Print out actual readin Data
    std::cout << bernhard << std::endl;

    // Removes the first character, deletes all the now Duplicate Lines Paragraphwise (can still be duplicate globaly) and then removes the Last character
    bernhard << truncateString(0,1) << removeDuplicates(&indices, false) << truncateString(-1, -2);

    for(auto i : indices)
        std::cout << i << std::endl;

    // Replace "ffe" with "eef"
    bernhard << replaceString("ffe", "eef");

    // Insert the String "SE" on the second to last position and "FE" on the SECOND
    bernhard << insertString("SE", -2) << insertString("FE", 1);

    // Removes everthing from the first to the fifth to last Character, then removes everything that is not a digit and clear up the empty rows
    jasmina << truncateString(0, -4) << replaceStringRegex("[^0-9]", "") << clearEmptyRows;

    // Prints out the modified InputData
    std::cout << bernhard << "\n OtherTest \n" << jasmina;
    */

    std::cout << bernhard;

    bernhard << tokenizeData(&tokenizedData, "ff");

    for(std::vector<std::vector<std::string>> paragraph : tokenizedData) {
        for(std::vector<std::string> string : paragraph) {
            for(std::string token : string) {
                std::cout << token << "\t\t";
            }
            std::cout << "\n";
        }
        std::cout << "=== PARAGRAPH ===" << '\n';
    }

    return 0;
}