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
    std::vector<std::vector<std::string>> mySearchData;
    data >> myModifiedData;
    data >> mySearchData;

    int accumulator = 0;
    
    // Matches all symbols 
    std::regex pattern("([^0-9.])");

    for(int line = 0; line < myModifiedData[0].size(); line++) {
            // Loop to find and replace matches
            std::smatch match;

            // Needed for multiple matches in one Line
            int pos = 0;

            // Matched some Shit
            while(std::regex_search(mySearchData[0][line], match, pattern)) {  
                // Matched text
                std::string matched = match.str(0);

                pos = (pos == 0) ? match.position() : (pos + match.position() + 1); 

                std::string tmp = "";

                // Start on top line
                if(line > 0) {
                    // Start on left
                    if(!isdigit(myModifiedData[0][line - 1][pos])) {
                        for(int i = pos - 1; i >= 0; i--) {
                            if(isdigit(myModifiedData[0][line - 1][i])) {
                                tmp.insert(0, 1, myModifiedData[0][line - 1][i]);
                                myModifiedData[0][line - 1][i] = '.';
                            } else {
                                break;
                            }
                        }
                    }
                    if(tmp != "")
                        accumulator += stoi(tmp);
                    tmp = "";

                    // Start on left middle
                    if(!isdigit(myModifiedData[0][line - 1][pos + 1])) {
                        for(int i = pos; i >= 0; i--) {
                            if(isdigit(myModifiedData[0][line - 1][i])) {
                                tmp.insert(0, 1, myModifiedData[0][line - 1][i]);
                                myModifiedData[0][line - 1][i] = '.';
                            } else {
                                break;
                            }
                        }
                    }
                    if(tmp != "")
                        accumulator += stoi(tmp);
                    tmp = "";

                    // On the Right
                    int width;
                    bool found = false;
                    for(width = pos + 1; width < myModifiedData[0][line - 1].length(); width++) {
                        if(!isdigit(myModifiedData[0][line - 1][width]))
                            break;
                        else
                            found = true;
                    }

                    for(int i = width - 1; i >= 0; i--) {
                        if(isdigit(myModifiedData[0][line - 1][i]) && found) {
                            tmp.insert(0, 1, myModifiedData[0][line - 1][i]);
                            myModifiedData[0][line - 1][i] = '.';
                        } else {
                            break;
                        }
                    }
                    if(tmp != "")
                        accumulator += stoi(tmp);
                    tmp = "";
                }

                // left direct
                for(int i = pos - 1; i >= 0; i--) {
                    if(isdigit(myModifiedData[0][line][i])) {
                        tmp.insert(0, 1, myModifiedData[0][line][i]);
                        myModifiedData[0][line][i] = '.';
                    } else {
                        break;
                    }
                }
                if(tmp != "")
                    accumulator += stoi(tmp);
                tmp = "";
                
                for(int i = pos + 1; i < myModifiedData[0][line].size(); i++) {
                    if(isdigit(myModifiedData[0][line][i])) {
                        tmp += myModifiedData[0][line][i];
                        myModifiedData[0][line][i] = '.';
                    } else {
                        break;
                    }
                }
                if(tmp != "")
                    accumulator += stoi(tmp);
                tmp = "";

                // Below
                if(line < myModifiedData[0].size() - 1) {
                    // Start on left
                    if(!isdigit(myModifiedData[0][line + 1][pos])) {
                        for(int i = pos - 1; i >= 0; i--) {
                            if(isdigit(myModifiedData[0][line + 1][i])) {
                                tmp.insert(0, 1, myModifiedData[0][line + 1][i]);
                                myModifiedData[0][line + 1][i] = '.';
                            } else {
                                break;
                            }
                        }
                    }
                    if(tmp != "")
                        accumulator += stoi(tmp);
                    tmp = "";

                    // Start on left middle
                    if(!isdigit(myModifiedData[0][line + 1][pos + 1])) {
                        for(int i = pos; i >= 0; i--) {
                            if(isdigit(myModifiedData[0][line + 1][i])) {
                                tmp.insert(0, 1, myModifiedData[0][line + 1][i]);
                                myModifiedData[0][line + 1][i] = '.';
                            } else {
                                break;
                            }
                        }
                    }
                    if(tmp != "")
                        accumulator += stoi(tmp);
                    tmp = "";

                    // On the Right
                    int width;
                    bool found = false;
                    for(width = pos + 1; width < myModifiedData[0][line + 1].length(); width++) {
                        if(!isdigit(myModifiedData[0][line + 1][width]))
                            break;
                        else
                            found = true;
                    }
                    for(int i = width - 1; i >= 0; i--) {
                        if(isdigit(myModifiedData[0][line + 1][i]) && found) {
                            //tmp +=  myModifiedData[0][line - 1][i];
                            tmp.insert(0, 1, myModifiedData[0][line + 1][i]);
                            myModifiedData[0][line + 1][i] = '.';
                        } else {
                            break;
                        }
                    }
                    if(tmp != "")
                        accumulator += stoi(tmp);
                    tmp = "";
                }

                //std::cout << matched << "      " << match.position() << std::endl;
               
                mySearchData[0][line] = match.suffix();
            }
        }
    std::cout << "Your solution to part one is: " << accumulator << "\n";
}

bool isPartOfNumber(const std::string& str, int index) {
    while(index < str.length() && std::isdigit(str[index])) {
        index++;
    }
    return index > 0 && std::isdigit(str[index - 1]);
}

bool checkNeighbourhoodPartTwo(const std::vector<std::vector<std::string>>& mySearchData, int x, int y) {
    if (y >= 0 && y < mySearchData[0].size() && x >= 0 && x < mySearchData[0][y].length()) {
        char currentDigit = mySearchData[0][y][x];
        int countNeighbours = 0;

        for(int i = -1; i <= 1; i += 2) {
            for(int j = -1; j <= 1; j += 1) {
                int newX = x + j;
                int newY = y + i;

                if(newX >= 0 && newX < mySearchData[0][newY].length() && newY >= 0 && newY < mySearchData[0].size()) {
                    if(isdigit(mySearchData[0][newY][x])) {
                        countNeighbours++;
                        break;
                    }
                    if(std::isdigit(mySearchData[0][newY][newX])) {
                        //if(!isdigit(mySearchData[0][newY][newX - 1]) || !isdigit(mySearchData[0][newY][newX + 1])) {
                            countNeighbours++;
                        //}
                    }
                }
            }
        }
        if(isdigit(mySearchData[0][y][x-1])) countNeighbours++;
        if(isdigit(mySearchData[0][y][x+1])) countNeighbours++;


        std::cout << "NEIGH" << countNeighbours << "\n";
        return countNeighbours >= 2;
    }

    return false;
}

void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    std::vector<std::vector<std::string>> mySearchData;
    data >> myModifiedData;
    data >> mySearchData;

    int accumulator = 0;

    std::regex pattern("[*]");

    for(int line = 0; line < myModifiedData[0].size(); line++) {
            // Loop to find and replace matches
            std::smatch match;

            // Needed for multiple matches in one Line
            int pos = 0;

            // Matched some Shit
            while(std::regex_search(mySearchData[0][line], match, pattern)) {  
                // Matched text
                std::string matched = match.str(0);

                pos = (pos == 0) ? match.position() : (pos + match.position() + 1); 

                if(!checkNeighbourhoodPartTwo(mySearchData, pos, line)) {
                    mySearchData[0][line] = match.suffix();
                    continue;
                }

                std::string tmp = "";
                int localAcc = 1;

                // Start on top line
                if(line > 0) {
                    // Start on left
                    if(!isdigit(myModifiedData[0][line - 1][pos])) {
                        for(int i = pos - 1; i >= 0; i--) {
                            if(isdigit(myModifiedData[0][line - 1][i])) {
                                tmp.insert(0, 1, myModifiedData[0][line - 1][i]);
                                myModifiedData[0][line - 1][i] = '.';
                            } else {
                                break;
                            }
                        }
                    }
                    if(tmp != "")
                        localAcc *= stoi(tmp);
                    tmp = "";

                    // Start on left middle
                    if(!isdigit(myModifiedData[0][line - 1][pos + 1])) {
                        for(int i = pos; i >= 0; i--) {
                            if(isdigit(myModifiedData[0][line - 1][i])) {
                                tmp.insert(0, 1, myModifiedData[0][line - 1][i]);
                                //myModifiedData[0][line - 1][i] = '.';
                            } else {
                                break;
                            }
                        }
                    }
                    if(tmp != "")
                        localAcc *= stoi(tmp);
                    tmp = "";

                    // On the Right
                    int width;
                    bool found = false;
                    for(width = pos + 1; width < myModifiedData[0][line - 1].length(); width++) {
                        if(!isdigit(myModifiedData[0][line - 1][width]))
                            break;
                        else
                            found = true;
                    }

                    for(int i = width - 1; i >= 0; i--) {
                        if(isdigit(myModifiedData[0][line - 1][i]) && found) {
                            tmp.insert(0, 1, myModifiedData[0][line - 1][i]);
                            //myModifiedData[0][line - 1][i] = '.';
                        } else {
                            break;
                        }
                    }
                    if(tmp != "")
                        localAcc *= stoi(tmp);
                    tmp = "";
                }

                // left direct
                for(int i = pos - 1; i >= 0; i--) {
                    if(isdigit(myModifiedData[0][line][i])) {
                        tmp.insert(0, 1, myModifiedData[0][line][i]);
                        //myModifiedData[0][line][i] = '.';
                    } else {
                        break;
                    }
                }
                if(tmp != "")
                    localAcc *= stoi(tmp);
                tmp = "";
                
                for(int i = pos + 1; i < myModifiedData[0][line].size(); i++) {
                    if(isdigit(myModifiedData[0][line][i])) {
                        tmp += myModifiedData[0][line][i];
                        //myModifiedData[0][line][i] = '.';
                    } else {
                        break;
                    }
                }
                if(tmp != "")
                    localAcc *= stoi(tmp);
                tmp = "";

                // Below
                if(line < myModifiedData[0].size() - 1) {
                    // Start on left
                    if(!isdigit(myModifiedData[0][line + 1][pos])) {
                        for(int i = pos - 1; i >= 0; i--) {
                            if(isdigit(myModifiedData[0][line + 1][i])) {
                                tmp.insert(0, 1, myModifiedData[0][line + 1][i]);
                                //myModifiedData[0][line + 1][i] = '.';
                            } else {
                                break;
                            }
                        }
                    }
                    if(tmp != "")
                        localAcc *= stoi(tmp);
                    tmp = "";

                    // Start on left middle
                    if(!isdigit(myModifiedData[0][line + 1][pos + 1])) {
                        for(int i = pos; i >= 0; i--) {
                            if(isdigit(myModifiedData[0][line + 1][i])) {
                                tmp.insert(0, 1, myModifiedData[0][line + 1][i]);
                                //myModifiedData[0][line + 1][i] = '.';
                            } else {
                                break;
                            }
                        }
                    }
                    if(tmp != "")
                        localAcc *= stoi(tmp);
                    tmp = "";

                    // On the Right
                    int width;
                    bool found = false;
                    for(width = pos + 1; width < myModifiedData[0][line + 1].length(); width++) {
                        if(!isdigit(myModifiedData[0][line + 1][width]))
                            break;
                        else
                            found = true;
                    }
                    for(int i = width - 1; i >= 0; i--) {
                        if(isdigit(myModifiedData[0][line + 1][i]) && found) {
                            //tmp +=  myModifiedData[0][line - 1][i];
                            tmp.insert(0, 1, myModifiedData[0][line + 1][i]);
                            //myModifiedData[0][line + 1][i] = '.';
                        } else {
                            break;
                        }
                    }
                    if(tmp != "")
                        localAcc *= stoi(tmp);
                    tmp = "";

                    accumulator += localAcc;
                }


                std::cout << matched << "      " << match.position() << std::endl;
               
                mySearchData[0][line] = match.suffix();
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