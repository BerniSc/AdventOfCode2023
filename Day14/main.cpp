#include "aocHelper.hpp"

#include <regex>
#include <unordered_map>

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

struct Board {
    std::vector<std::string> board;

    Board(std::vector<std::string>& board) : board(board) {

    }

    int moveNorth() {
        int moved = 0;

        for(int y = 0; y < board.size() - 1; y++) {
            for(int x = 0; x < board[0].size(); x++) {
                if(board[y][x] == '.' && board[y + 1][x] == 'O') {
                    board[y][x] = 'O';
                    board[y + 1][x] = '.';
                    moved++;
                }
            }
        }
        return moved;
    }

    int moveEast() {
        int moved = 0;

        for(int y = 0; y < board.size(); y++) {
            for(int x = board[0].size() - 1; x > 0; x--) {
                if(board[y][x] == '.' && board[y][x - 1] == 'O') {
                    board[y][x] = 'O';
                    board[y][x - 1] = '.';
                    moved++;
                }
            }
        }
        return moved;
    }

    int moveSouth() {
        int moved = 0;

        for(int y = board.size() - 1; y > 0; y--) {
            for(int x = 0; x < board[0].size(); x++) {
                if(board[y][x] == '.' && board[y - 1][x] == 'O') {
                    board[y][x] = 'O';
                    board[y - 1][x] = '.';
                    moved++;
                }
            }
        }
        return moved;
    }

    int moveWest() {
        int moved = 0;

        for(int y = 0; y < board.size(); y++) {
            for(int x = 0; x < board[0].size() - 1; x++) {
                if(board[y][x] == '.' && board[y][x + 1] == 'O') {
                    board[y][x] = 'O';
                    board[y][x + 1] = '.';
                    moved++;
                }
            }
        }
        return moved;
    }

    int moveCircle() {
        while(this->moveNorth() != 0);
        while(this->moveWest() != 0);
        while(this->moveSouth() != 0);
        while(this->moveEast() != 0);
    }

    /*void moveCircle(int times) {
        std::unordered_map<std::string, int> seen;
        int c = 1;
        int loop = 0;

        while((loop == 0 || seen.count(serializeBoard()) == 0) && c <= times) {
            while(moveNorth());
            while(moveWest());
            while(moveSouth());
            while(moveEast());

            if(loop == 0 && seen.count(serializeBoard()) > 0) {
                int before = seen[serializeBoard()];
                loop = c - before;
                std::cout << "Loop of size " << loop << " from " << before << " to " << c << std::endl;
            }

            seen[serializeBoard()] = c++;
        }
    }*/

    void cycle(int times) {
        int target = times;
        int loop = 0;
        std::unordered_map<std::string, int> seen;

        for (int c = 1; ; c++) {
            moveCircle();

            if (c == target) {
                return;
            }

            if (loop == 0 && seen.count(serializeBoard()) > 0) {
                int before = seen[serializeBoard()];
                loop = c - before;
                std::cout << "Loop of size " << loop << " from " << before << " to " << c << std::endl;
                target -= (target - c) / loop * loop;
                std::cout << "Changing target from " << times << " to " << target << std::endl;
            }

            seen[serializeBoard()] = c;
        }
    }

    std::string serializeBoard() {
        std::string result = "";
        for(const auto& row : board) {
            result += row;
        }
        return result;
    }

    void printBoard() {
        for(auto line : board)
            std::cout << line << "\n";
    }

    long long getLoad() {
        long long load = 0;
        for(int y = 0; y < board.size(); y++)
            for(char c : board[y])
                if(c == 'O') 
                    load += 1 * (board.size() - y); 

        return load;
    }
};

void processData(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    long long accumulator = 0;
    
    Board b(myModifiedData[0]);

    while(b.moveNorth() != 0);

    b.printBoard();
    accumulator = b.getLoad();

    std::cout << "Your solution to part one is: " << accumulator << "\n";
}

void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    long long accumulator = 0;
    
    Board b(myModifiedData[0]);

    b.cycle(1'000'000'000);

    accumulator = b.getLoad();

    b.printBoard();
    
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