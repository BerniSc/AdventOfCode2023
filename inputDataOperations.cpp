#include "inputDataOperations.hpp"

TruncateString::TruncateString() {
    start = 0;
    stop = 0;
}

TruncateString& TruncateString::operator()(int start, int stop) {
    this->start = start;
    this->stop = stop;
    return *this;
}

void TruncateString::performAction(std::vector<std::vector<std::string>>& data) {
    for(std::vector<std::string>& paragraph : data) {
        for(std::string& string : paragraph) {
            int stringLength = string.length();

            // Adjust start and stop based on the provided values
            int adjustedStart = (start < 0) ? std::max(0, stringLength + start + 1) : std::min(start, stringLength);
            int adjustedStop = (stop < 0) ? stringLength + stop : std::min(stop, stringLength);

            if(adjustedStart > adjustedStop) {
                int temp = adjustedStart;
                adjustedStart = adjustedStop;
                adjustedStop = temp;
            }

            // Calculate the number of characters to erase
            int numCharsToRemove = std::max(0, adjustedStop - adjustedStart);

            // Ensure valid indices
            if(adjustedStart >= stringLength || numCharsToRemove >= stringLength || adjustedStart < 0) {
                continue;
            }
            std::cout << adjustedStart << "     " << numCharsToRemove << "      " << stringLength << std::endl; 
            // Perform the erase operation
            string.erase(adjustedStart, numCharsToRemove);
        }
    }
}

RemoveDuplicates::RemoveDuplicates() : positions(nullptr), paragraphWide(true) {

}

RemoveDuplicates& RemoveDuplicates::operator()(std::vector<int>* positions, bool paragraphWide) {
    this->positions = positions;
    this->paragraphWide = paragraphWide;
    return *this;
}

void RemoveDuplicates::performAction(std::vector<std::vector<std::string>>& data) {
    std::unordered_set<std::string> uniqueElements;
    std::vector<int> indices;

    for(std::vector<std::string>& paragraph : data) {
        int iterator = 0;
        int formerIndex = 0;
        while (iterator < paragraph.size()) {
            std::string& string = paragraph[iterator];
            iterator++;
            formerIndex++;

            if(!uniqueElements.insert(string).second) {
                // If the insertion is unsuccessful, the element is not unique -> Delete it from Dataset
                if(positions)
                    positions->push_back(formerIndex);
                paragraph.erase(paragraph.begin() + iterator - 1);
                iterator--;
            }
        }
        if(!this->paragraphWide)
            uniqueElements.clear();
    }
}

ReplaceString::ReplaceString() {

}

ReplaceString& ReplaceString::operator()(const std::string searchString, const std::string replaceString) {
    this->searchString = searchString;
    this->replaceString = replaceString;
    return *this;
}

void ReplaceString::performAction(std::vector<std::vector<std::string>>& data) {
    for(std::vector<std::string>& paragraph : data) {
        for(std::string& string : paragraph) {
            // Find all occurrences of searchString in the current string
            size_t pos = 0;
            while((pos = string.find(searchString, pos)) != std::string::npos) {
                // Replace searchString with replaceString
                string.replace(pos, searchString.length(), replaceString);
                pos += replaceString.length();
            }
        }
    }
}

InsertString::InsertString() {

}

InsertString& InsertString::operator()(const std::string inputString, const int position) {
    this->inputString = inputString;
    this->position = position;
    return *this;
}

void InsertString::performAction(std::vector<std::vector<std::string>>& data) {
    for(std::vector<std::string>& paragraph : data) {
        for(std::string& string : paragraph) {
            // Ensure the position is within the bounds of the string
            int insertPosition = (position < 0) ? std::max(0, static_cast<int>(string.length()) + position + 1)
                                                : std::min(position, static_cast<int>(string.length()));

            // Insert inputString at the specified position
            string.insert(insertPosition, inputString);
        }
    }
}