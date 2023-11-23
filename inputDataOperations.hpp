#ifndef INPUT_DATA_OPERATIONS_HPP
#define INPUT_DATA_OPERATIONS_HPP

#include <string>
#include <vector>

#include <iostream>

#include <unordered_set>    // For RemoveDuplicates
#include <algorithm>        // For ReplaceString
#include <regex>            // For ReplaceStringRegex
#include <sstream>          // For ReplaceStringRegex

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
        // Optionally set a reference to an out-var where the Indices of the Doubled Vars are stored
        RemoveDuplicates& operator()(std::vector<int>* positions, bool paragraphWide = true);
        // Use a Set to remove the Duplicate Elements
        void performAction(std::vector<std::vector<std::string>>& data) override;
};

class ClearEmptyRows : public InputDataOperation {
    private:
    public:
        ClearEmptyRows();
        void performAction(std::vector<std::vector<std::string>>& data) override;
};

class ReplaceString : public InputDataOperation {
    private:
        std::string searchString, replaceString;
    public:
        ReplaceString();
        // Takes in a regular String like 'hello' and replaces it with the replace String
        ReplaceString& operator()(const std::string searchString, const std::string replaceString);

        void performAction(std::vector<std::vector<std::string>>& data) override;
};

class ReplaceStringRegex : public InputDataOperation {
    private:
        std::string regexSearchString, replaceString;
    public:
        ReplaceStringRegex();
        // Takes in a regular Expression like [a-z] or [0-9] or [^a-z] and replaces it with the replace String 
        ReplaceStringRegex& operator()(const std::string regexSearchString, const std::string replaceString);

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

class TokenizeData : public InputDataOperation {
    private:
        std::string tokenizeRegex;

        std::vector<std::vector<std::vector<std::string>>>* tokenizedData;
    public:
        TokenizeData();
        // Default Param for Tokenize Regex is whitespace
        TokenizeData& operator()(std::vector<std::vector<std::vector<std::string>>>* tokenizedData, const std::string tokenizeRegex = "\\s+");

        void performAction(std::vector<std::vector<std::string>>& data) override;
};

#endif