#ifndef INPUT_DATA_OPERATIONS_HPP
#define INPUT_DATA_OPERATIONS_HPP

#include <string>
#include <vector>

#include <iostream>

#include <unordered_set>    // For RemoveDuplicates
#include <algorithm>        // For ReplaceString

// Interface for String operations
struct InputDataOperation {
    virtual void performAction(std::vector<std::vector<std::string>>&) = 0;
};

class TruncateString : public InputDataOperation {
    private:
        int start, stop;
    public:
        TruncateString();
        // Accepts the Indicies of the Chars to delete, f.e. (0,1) delets first char, (-1,-2) deletes last char
        TruncateString& operator()(int start, int stop);
        void performAction(std::vector<std::vector<std::string>>& data) override;
};

class RemoveDuplicates : public InputDataOperation {
    private:
        std::vector<int>* positions;
        bool paragraphWide;
    public:
        RemoveDuplicates();
        // optionaly set a reference to an out-var where the Indices of the Doubled Vars are stored
        RemoveDuplicates& operator()(std::vector<int>* positions, bool paragraphWide = true);
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

#endif