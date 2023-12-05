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

    bernhard << replaceStringRegex("([^0-9|\\s]|)", "");
    
    // Print out actual readin Data
    std::cout << bernhard << std::endl;
    //  std::cout << bernhard_part_two << std::endl;

    //processData(bernhard);    
    processDataPartTwo(bernhard_part_two);

    //bernhard << tokenizeData(&tokenizedData, " ");

    //printTokenizedData(tokenizedData);

    return 0;
}

// Function to find the target value by traversing through the maps
int findTargetValue(const std::vector<std::unordered_map<int, int>>& maps, int initialValue) {
    int currentValue = initialValue;
    std::cout << "MAPPING\n";
    int mapper = 0;
    // Iterate through each map
    for(const auto& currentMap : maps) {
        // Attempt to find the current value in the map
        auto it = currentMap.find(currentValue);

        // If the value is found, update currentValue with the corresponding target value
        if(it != currentMap.end()) {
            //std::cout << "Mapper " << ++mapper << " " << currentValue << "  " << it->second << "\n";
            currentValue = it->second;
        } else {
            ++mapper;
            //std::cout << "Not found\n";
            currentValue = currentValue;
        }

    }

    // Return the final target value
    return currentValue;
}

// WHEWP -> My Programm hatet the Data.... Retry
// Sad, i really Liked this Solution
/*void processData(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    // printTokenizedData(tokenizedData);

    int accumulator = 1000000;
    
    std::unordered_map<int, int> seed2soil;
    std::unordered_map<int, int> soil2fertilizer;
    std::unordered_map<int, int> fertilizer2water;
    std::unordered_map<int, int> water2light;
    std::unordered_map<int, int> light2temp;
    std::unordered_map<int, int> temp2humidity;
    std::unordered_map<int, int> humidity2location;

    std::vector<std::unordered_map<int,int>> maps;

    maps.push_back(seed2soil);
    maps.push_back(soil2fertilizer);
    maps.push_back(fertilizer2water);
    maps.push_back(water2light);
    maps.push_back(light2temp);
    maps.push_back(temp2humidity);
    maps.push_back(humidity2location);

    //for(std::vector<std::vector<std::string>> paragraph : tokenizedData) {
    for(int paragraph = 1; paragraph < tokenizedData.size(); paragraph++) {
        int lineSkipper = 0;
        maps[paragraph - 1].reserve(150000);
        for(std::vector<std::string>& line : tokenizedData[paragraph]) {
            if(lineSkipper++ == 0) continue;
            unsigned long range = stol(line[2]);
            for(unsigned int i = 0; i < range; i++) {
                maps[paragraph - 1].insert(std::pair<int, int>(stol(line[1]) + i, stol(line[0]) + i));
            }
            std::cout << "Finished " << lineSkipper << "on p " << paragraph << "\n";
        }
    }

    //for(auto elem : maps[1]) 
    //    std::cout << elem.first << "    " << elem.second << "\n";

    int skipFirst = 0;
    for(std::string elem : tokenizedData[0][0]) {
        if(skipFirst++ == 0) continue;
        accumulator = std::min(accumulator, findTargetValue(maps, stol(elem)));
    }


    std::cout << "Your solution to part one is: " << accumulator << "\n";
}*/

struct Range {
    long long source;
    long long destination;
    long long range;

    Range(long long source, long long destination, long long range) : source(source), destination(destination), range(range) {

    }
};

struct AlmanachChapter {
    std::vector<long long> source;
    std::vector<long long> destination;
    std::vector<long long> range;

    AlmanachChapter(std::vector<Range> ranges) {
        for(Range range : ranges) {
            source.push_back(range.source);
            destination.push_back(range.destination);
            this->range.push_back(range.range);
        }
    }

    long long getMappedValue(long long previousValue) {
        for(long long i = 0; i < source.size(); i++) {
            // If the "previous Value" is in the Range of the current Element then get the complementary value
            if(source[i] <= previousValue && (source[i] + range[i]) > previousValue)
                return destination[i] + (previousValue - source[i]);
        }
        return previousValue;   // Not Mapped here -> Propagate self to next function
    }
};

void processData(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    // printTokenizedData(tokenizedData);

    long long accumulator = INT64_MAX;
    
    std::vector<AlmanachChapter> chapters;

    for(int paragraph = 1; paragraph < tokenizedData.size(); paragraph++) {
        int lineSkipper = 0;
        std::vector<Range> tmp;
        for(std::vector<std::string>& line : tokenizedData[paragraph]) {
            if(lineSkipper++ == 0) continue;
            tmp.push_back(Range(stol(line[1]), stol(line[0]), stol(line[2])));
        }
        chapters.push_back(AlmanachChapter(tmp));
    }

    int skipFirst = 0;
    for(std::string elem : tokenizedData[0][0]) {
        if(skipFirst++ == 0) continue;
        long long val = stol(elem);
        for(AlmanachChapter chapter : chapters)
            val = chapter.getMappedValue(val);
        accumulator = std::min(accumulator, val);
    }

    std::cout << "Your solution to part one is: " << accumulator << "\n";
}

// Hm, thats far from Great. Only Use this solution if you want to see your Computer suffer...
// But it ultimatly works
void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::string>> myModifiedData;
    data >> myModifiedData;

    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    // printTokenizedData(tokenizedData);

    long long accumulator = INT64_MAX;
    
    std::vector<AlmanachChapter> chapters;

    for(int paragraph = 1; paragraph < tokenizedData.size(); paragraph++) {
        int lineSkipper = 0;
        std::vector<Range> tmp;
        for(std::vector<std::string>& line : tokenizedData[paragraph]) {
            if(lineSkipper++ == 0) continue;
            tmp.push_back(Range(stol(line[1]), stol(line[0]), stol(line[2])));
        }
        chapters.push_back(AlmanachChapter(tmp));
    }

    int skipFirst = 0;
    for(int i = 1; i < tokenizedData[0][0].size(); i += 2) {
        long long valStart = stol(tokenizedData[0][0][i]);
        long long valEnd = stol(tokenizedData[0][0][i + 1]);
        long long valStartReadSeed = valStart;
        for(; valEnd > 0; valEnd--, valStartReadSeed++) {
            valStart = valStartReadSeed;
            for(AlmanachChapter chapter : chapters)
                valStart = chapter.getMappedValue(valStart);
            accumulator = std::min(accumulator, valStart);
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