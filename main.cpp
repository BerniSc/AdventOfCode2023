#include "aocHelper.hpp"

int main() {
    // Uses an Instance of The TruncateString Class to edit the Readin Data
    TruncateString truncateString;
    RemoveDuplicates removeDuplicates;
    ReplaceString replaceString;
    // Read the Data in using the Mode 1 from File "input_test.txt" -> TODO Exception
    InputData bernhard(1);
    bernhard << "input_test.txt";

    std::vector<int> indices;

    // Print out actual readin Data, removes the First Character and the Last character in each line and prints result
    std::cout << bernhard;
    //bernhard << &truncateString(0,1) << &removeDuplicates(indices, false) << &truncateString(-1, -2);
    bernhard << &replaceString("ffe", "eef");
    std::cout << bernhard;

    return 0;
}