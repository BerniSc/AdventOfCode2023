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
    
    bernhard << replaceStringRegex("= |,|\\(|\\)", "");
    bernhard_part_two << replaceStringRegex("= |,|\\(|\\)", "");

    // Print out actual readin Data
    std::cout << bernhard << std::endl;
    //  std::cout << bernhard_part_two << std::endl;

    //processData(bernhard);    
    
    processDataPartTwo(bernhard_part_two);

    //bernhard << tokenizeData(&tokenizedData, " ");

    //printTokenizedData(tokenizedData);

    return 0;
}

struct Node {
    std::string leftPos;
    std::string rightPos;

    // PART 2
    std::string nodeName;

    Node(std::string left, std::string right, std::string nodeName = "") : leftPos(left), rightPos(right) {
        this->nodeName = nodeName;
    }
};

// Hm, had to "inspire" on this one to get the solution...
long long gcd(long long a, long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

long long lcm(std::vector<int> values) {
    long long lcm = 1;
    for(int val : values)
        lcm = lcm * val / gcd(lcm, val);
    return lcm;
}

struct GhostNode {
    std::vector<Node> nodes;

    std::vector<int> indices;

    void addNode(Node n) {
        nodes.push_back(n);
        indices.push_back(0);
    }

    bool checkWin(int accumulator) {
        bool ret = true;        // Needs to be with retVal Propagation, as multiple Nodes can have the same fricking accumulator and all must be checked
        for(int node = 0; node < nodes.size(); node++) {
            if(indices[node] != 0) continue;
            //std::string tmp = (direction == 'R' ? nodes[node].rightPos : nodes[node].leftPos);
            std::string tmp = nodes[node].nodeName;
            if(tmp[tmp.size() - 1] == 'Z')
                indices[node] = accumulator;
            else
                ret = false;
        }
        return ret;
    }
};

std::string getNextPos(std::unordered_map<std::string, Node>& nodeList, std::string key, char direction) {
    auto it = nodeList.find(key);

    std::cout << "Trying to find " << key << "\n";

    if(it != nodeList.end()) {
        if(direction == 'L')
            return it->second.rightPos;
        else    
            return it->second.leftPos;
        return "ZZZ";
    }
    std::cout << "This should not have been reached!\n";
    return "AAA";
}

Node getNextPosNode(std::unordered_map<std::string, Node>& nodeList, std::string key) {
    auto it = nodeList.find(key);

    if(it != nodeList.end()) {
        return it->second;
    }
    std::cout << "This should not have been reached!\n";
    //return ";
}

void processData(InputData& data) {
    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    printTokenizedData(tokenizedData);

    std::vector<std::vector<std::string>> myModifiedData = tokenizedData[1];

    int accumulator = 0;
    
    std::unordered_map<std::string, Node> nodeList;

    for(std::vector<std::string> elem : myModifiedData) {
        nodeList.insert(std::pair<std::string, Node>(elem[0], Node(elem[1], elem[2])));
        //std::cout << elem[0]<<"|"<<elem[1]<<"|"<<elem[2]<<"\n";
    }

    std::string directionIterator = tokenizedData[0][0][0];
    std::cout << directionIterator << "\n";

    int directionCounter = 0;

    for(auto e : nodeList)
        std::cout << e.first << "   " << e.second.leftPos << "  " << e.second.rightPos << "\n";;

    std::string curPos = "AAA";
    while(curPos != "ZZZ") {
        char direction = directionIterator[(directionCounter++) % directionIterator.size()];
        std::string tmp = getNextPos(nodeList, curPos, direction);
        curPos = tmp;
        ++accumulator;
    }

    std::cout << "Your solution to part one is: " << accumulator << "\n";
}

/*
void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    printTokenizedData(tokenizedData);

    std::vector<std::vector<std::string>> myModifiedData = tokenizedData[1];

    long long accumulator = 1;
    
    std::unordered_map<std::string, Node> nodeList;
    GhostNode start;

    for(std::vector<std::string> elem : myModifiedData) {
        Node n(elem[1], elem[2]);
        nodeList.insert(std::pair<std::string, Node>(elem[0], n));
        //std::cout << elem[0]<<"|"<<elem[1]<<"|"<<elem[2]<<"\n";
        if(elem[0][2] == 'A')
            start.addNode(n);
    }

    std::string directionIterator = tokenizedData[0][0][0];
    std::cout << directionIterator << "\n";

    int directionCounter = 0;

    for(auto e : nodeList)
        std::cout << e.first << "   " << e.second.leftPos << "  " << e.second.rightPos << "\n";;

    GhostNode current = start;
    char direction;

    do {
        direction = directionIterator[directionCounter++];

        directionCounter %= directionIterator.size();

        ++accumulator;
        for(int i = 0; i < current.nodes.size(); i++) {
            std::string key = (direction == 'R' ? current.nodes[i].rightPos : current.nodes[i].leftPos);
            current.nodes[i] = getNextPosNode(nodeList, key);
        }

        if(!(accumulator % 100000000)) std::cout << "still running with " << accumulator << "\n";
    } while(!current.checkWin(direction));
    
    std::cout << "Your solution to part two is: " << accumulator << "\n";
}
*/

void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    printTokenizedData(tokenizedData);

    std::vector<std::vector<std::string>> myModifiedData = tokenizedData[1];

    long long accumulator = 0;
    
    std::unordered_map<std::string, Node> nodeList;
    GhostNode start;

    for(std::vector<std::string> elem : myModifiedData) {
        Node n(elem[1], elem[2], elem[0]);
        nodeList.insert(std::pair<std::string, Node>(elem[0], n));
        if(elem[0][2] == 'A')
            start.addNode(n);
    }

    std::string directionIterator = tokenizedData[0][0][0];

    int directionCounter = 0;

    GhostNode current = start;
    char direction;

    while(!current.checkWin(accumulator)) {
        direction = directionIterator[(directionCounter++) % directionIterator.size()];

        //directionCounter %= directionIterator.size();

        for(int i = 0; i < current.nodes.size(); i++) {
            std::string key = (direction == 'R' ? current.nodes[i].rightPos : current.nodes[i].leftPos);
            current.nodes[i] = getNextPosNode(nodeList, key);
        }
        ++accumulator;
    }
    
    accumulator = lcm(current.indices);

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