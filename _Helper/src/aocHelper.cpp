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

InputData& InputData::operator<<(InputDataOperation& operation) {
    operation.performAction(this->data);
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