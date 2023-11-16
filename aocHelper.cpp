#include "aocHelper.hpp"

InputData::InputData(const int mode) : mode(mode) {

}

InputData& InputData::operator<<(const std::string filename) {
    std::ifstream myFile;
    myFile.open(filename);

    std::vector<std::string> paragraph;
    std::string lineIterator;

    if(myFile.is_open()) {
        while(myFile) {
            // If EOF is reached set Output to empty to ensure that the final paragraph is pushed onto the full data set
            if(myFile.eof())
                lineIterator = "";
            // Read in Data linewise
            getline(myFile, lineIterator);
            // if Line is empty treat it as a seperate Paragraph and Push Paragraph onto final dataset
            if(lineIterator == "") {
                this->data.push_back(paragraph);
                paragraph.clear();
            } else {
                paragraph.push_back(lineIterator);
            }
        }
    } else {
        std::cout << "There seems to have been a Problem in reading your File..." << std::endl;
    }
    return *this;
}

InputData& InputData::operator<<(InputDataOperation* operation) {
    operation->performAction(this->data);
    return *this;
}

std::ostream& operator<<(std::ostream& ostream, const InputData& data) {
    for(std::vector<std::string> paragraph : data.data) {
        for(std::string string : paragraph) {
            ostream << string << '\n';
        }
        ostream << "=== PARAGRAPH ===" << '\n';
    }
    return ostream;
}


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
            int adjustedStart = (start < 0) ? std::max(0, stringLength + start) : std::min(start, stringLength);
            int adjustedStop = (stop < 0) ? stringLength + stop : std::min(stop, stringLength);

            // Ensure valid indices
            if(adjustedStart >= stringLength) {
                continue;;
            }

            // Perform the erase operation
            string.erase(adjustedStart, std::min(adjustedStop, stringLength) - adjustedStart);
        }
    }
}

RemoveDuplicates::RemoveDuplicates() : positions(nullptr), paragraphWide(true) {

}

RemoveDuplicates& RemoveDuplicates::operator()(std::vector<int>& positions, bool paragraphWide) {
    this->positions = &positions;
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
    for (std::vector<std::string>& paragraph : data) {
        for (std::string& string : paragraph) {
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