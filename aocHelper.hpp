#ifndef AOC_HELPER_HPP
#define AOC_HELPER_HPP

#include <string>
#include <vector>
#include <fstream>

#include <iostream>

// Interface for String operations
struct InputDataOperation {
    virtual void performAction(std::vector<std::vector<std::string>>&) = 0;
};

class InputData {
    private:
        const int mode;

        std::vector<std::vector<std::string>> data;
    public:
        InputData(const int mode);

        InputData& operator<<(const std::string filename);

        // Function for Chaining Operations together using Pipelike functionality
        InputData& operator<<(InputDataOperation*);

        void operator>>(std::vector<std::vector<std::string>>);

        friend std::ostream& operator<<(std::ostream& ostream, const InputData& data);

};

class TruncateString : public InputDataOperation {
    private:
        int start, stop;
    public:
        TruncateString();
        TruncateString& operator()(int start, int stop);
        void performAction(std::vector<std::vector<std::string>>& data) override;
};

class RemoveDuplicates : public InputDataOperation {
    private:
        std::vector<int>& positions;
    public:
        RemoveDuplicates();
        // optionaly set a reference to an out-var where the Indices of the Doubled Vars are stored
        RemoveDuplicates& operator()(std::vector<int>& positions);
        // Use a Set to remove the Duplicate Elements
        void performAction(std::vector<std::vector<std::string>>& data) override;
};

class ReplaceString : public InputDataOperation {
    private:
        std::string searchString, replaceString;
    public:
        ReplaceString();
        ReplaceString& operator()(const std::string searchString, const std::string replaceString);

        void performAction(std::vector<std::vector<std::string>>& data) override;
};

class InsertString : public InputDataOperation {
    private:
        std::string inputString;
        int position;
    public:
        InsertString();
        InsertString& operator()(const std::string inputString, const int position);

        void performAction(std::vector<std::vector<std::string>>& data) override;
};

// TODO -> Implement the Tokenizing

#endif