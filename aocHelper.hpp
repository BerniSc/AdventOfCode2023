#ifndef AOC_HELPER_HPP
#define AOC_HELPER_HPP

#include "inputDataOperations.hpp"

#include <string>
#include <vector>
#include <fstream>

#include <iostream>

// Interface for String operations
struct InputDataOperation;

class InputData {
    private:
        const int mode;

        std::vector<std::vector<std::string>> data;
    public:
        InputData(const int mode);

        InputData& operator<<(const std::string filename);

        // Function for Chaining Operations together using Pipelike functionality
        InputData& operator<<(InputDataOperation&);

        // Write out the Data to a Vector
        void operator>>(std::vector<std::vector<std::string>>&);

        friend std::ostream& operator<<(std::ostream& ostream, const InputData& data);

};

// TODO -> Implement the Tokenizing

#endif