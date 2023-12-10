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
    
    bernhard << replaceString(".", " ");

    // Print out actual readin Data
    std::cout << bernhard << std::endl;
    //  std::cout << bernhard_part_two << std::endl;

    //processData(bernhard);    
    
    processDataPartTwo(bernhard_part_two);

    //bernhard << tokenizeData(&tokenizedData, " ");

    //printTokenizedData(tokenizedData);

    return 0;
}

struct LUT {
    static int getMovementVector(char c) {
        // ORUL
        // 3210
        switch (c) {
            case '|' :
                return (1 << 3) | (1 << 1); 
            case '-' :
                return (1 << 2) | (1 << 0); 
            case 'L' :
                return (1 << 3) | (1 << 2); 
            case 'J' :
                return (1 << 3) | (1 << 0); 
            case '7' :
                return (1 << 1) | (1 << 0); 
            case 'F' :
                return (1 << 2) | (1 << 1);
            case 'S' :
                return 0xF;    
        }
        return 0;
    }

    static bool interfaceMatches(int interface1, int interface2, int direction) {
        if(direction == 0 || direction == 2)
            return (interface1 & (1 << ((3 + direction) % 4))) && (interface2 & (1 << ((1 + direction) % 4))); 
        else
            return (interface1 & (1 << ((1 + direction) % 4))) && (interface2 & (1 << ((3 + direction) % 4))); 
    }

    static bool interfaceMatches(char c1, char c2, int direction) {
        int interface1 = getMovementVector(c1);
        int interface2 = getMovementVector(c2);
        //std::cout <<  c1 << interface1 << " Matches " << c2 << interface2 << "   " << interfaceMatches(interface1, interface2, direction) << "\n";
        return interfaceMatches(interface1, interface2, direction);
    }
};

void processData(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    int accumulator = 0;
    
    int startX = 0, startY = 0;

    for(std::string line : myModifiedData[0]) {
        std::size_t found = line.find("S");
        if(found!=std::string::npos) {
            startX = found;
            break;
        }
        startY++;
    }
    
    char nextChar = '.';
    int currentX = startX, currentY = startY;

    int lastMove = 0;

    while(nextChar != 'S') {
        //std::cout << nextChar << "     " << currentX << "|" << currentY << "\n";
        bool alreadyMoved = false;

        // Unten
        if(currentY < myModifiedData[0].size() - 1 && !alreadyMoved && lastMove != 1) {
            if(LUT::interfaceMatches(myModifiedData[0][currentY][currentX], myModifiedData[0][currentY + 1][currentX], 2)) {
                currentY++;
                lastMove = 3;
                alreadyMoved = lastMove;
            }
        }

        // Links
        if(currentX > 0 && !alreadyMoved && lastMove != 2) {
            if(LUT::interfaceMatches(myModifiedData[0][currentY][currentX], myModifiedData[0][currentY][currentX - 1], 3)) {
                currentX--;
                lastMove = 4;
                alreadyMoved = lastMove;
            }
        }

        // Oben
        if(currentY > 0 && !alreadyMoved && lastMove != 3) {
            if(LUT::interfaceMatches(myModifiedData[0][currentY][currentX], myModifiedData[0][currentY - 1][currentX], 0)) {
                currentY--;
                lastMove = 1;
                alreadyMoved = lastMove;
            }
        }

        // Rechts
        if(currentX < myModifiedData[0][0].size() - 1 && !alreadyMoved && lastMove != 4) {
            if(LUT::interfaceMatches(myModifiedData[0][currentY][currentX], myModifiedData[0][currentY][currentX + 1], 1)) {
                currentX++;
                lastMove = 2;
                alreadyMoved = lastMove;
            }
        }

        nextChar = myModifiedData[0][currentY][currentX];
        accumulator++;
    }

    for(std::string e : myModifiedData[0])
        std::cout << e << "\n";

    std::cout << "Your solution to part one is: " << accumulator/2 << "\n";
}

void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    int accumulator = 0;
    
    int startX = 0, startY = 0;

    for(std::string line : myModifiedData[0]) {
        std::size_t found = line.find("S");
        if(found!=std::string::npos) {
            startX = found;
            break;
        }
        startY++;
    }
    
    char nextChar = '.';
    int currentX = startX, currentY = startY;

    int lastMove = 0;

    while(nextChar != 'S') {
        //std::cout << nextChar << "     " << currentX << "|" << currentY << "\n";
        bool alreadyMoved = false;

        // Unten
        if(currentY < myModifiedData[0].size() - 1 && !alreadyMoved && lastMove != 1) {
            if(LUT::interfaceMatches(myModifiedData[0][currentY][currentX], myModifiedData[0][currentY + 1][currentX], 2)) {
                if(myModifiedData[0][currentY][currentX] != 'S') myModifiedData[0][currentY][currentX] = '*';
                currentY++;
                lastMove = 3;
                alreadyMoved = lastMove;
            }
        }

        // Links
        if(currentX > 0 && !alreadyMoved && lastMove != 2) {
            if(LUT::interfaceMatches(myModifiedData[0][currentY][currentX], myModifiedData[0][currentY][currentX - 1], 3)) {
                if(myModifiedData[0][currentY][currentX] != 'S') myModifiedData[0][currentY][currentX] = '*';
                currentX--;
                lastMove = 4;
                alreadyMoved = lastMove;
            }
        }

        // Oben
        if(currentY > 0 && !alreadyMoved && lastMove != 3) {
            if(LUT::interfaceMatches(myModifiedData[0][currentY][currentX], myModifiedData[0][currentY - 1][currentX], 0)) {
                if(myModifiedData[0][currentY][currentX] != 'S') myModifiedData[0][currentY][currentX] = '*';
                currentY--;
                lastMove = 1;
                alreadyMoved = lastMove;
            }
        }

        // Rechts
        if(currentX < myModifiedData[0][0].size() - 1 && !alreadyMoved && lastMove != 4) {
            if(LUT::interfaceMatches(myModifiedData[0][currentY][currentX], myModifiedData[0][currentY][currentX + 1], 1)) {
                if(myModifiedData[0][currentY][currentX] != 'S') myModifiedData[0][currentY][currentX] = '*';
                currentX++;
                lastMove = 2;
                alreadyMoved = lastMove;
            }
        }

        nextChar = myModifiedData[0][currentY][currentX];
        accumulator++;
    }

    myModifiedData[0][startY][startX] = '*';

    long long insideCounter = 0;

    // Define the regular expression pattern to match characters between asterisks
    std::regex pattern("\\*([^\\*]+)\\*");
    // Alternative Idea of replacing outside characters piece by piece and then count the remaining
    //std::regex pattern("(^[^\\*]+\\*)|(\\*[^\\*]+$)");

    int defaultSize = myModifiedData[0][0].size();

    for(std::string& line : myModifiedData[0]) {
        std::stringstream _string;
        std::regex_replace(std::ostream_iterator<char>(_string), line.begin(), line.end(), pattern, "+");
        insideCounter += ((defaultSize - _string.str().size()) ? (defaultSize - _string.str().size() + 1 - 2) : 0);
        line = _string.str();
    }

    for(std::string e : myModifiedData[0])
        std::cout << e << "\n";

    std::cout << "Your solution to part two is: " << insideCounter << "\n";
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