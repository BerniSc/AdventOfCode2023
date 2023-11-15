#include "aocHelper.hpp"

int main() {
    // Uses an Instance of The TruncateString Class to edit the Readin Data
    TruncateString truncateString;
    // Read the Data in using the Mode 1 from File "input_test.txt" -> TODO Exception
    InputData bernhard(1);
    bernhard << "input_test.txt";

    // Print out actual readin Data, removes the First Character and the Last character in each line and prints result
    std::cout << bernhard;
    bernhard << &truncateString(0,1) << &truncateString(-1, 0);
    std::cout << bernhard;

    return 0;
}