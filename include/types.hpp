#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <string>

// Define t_matrix as a typedef for a vector of strings
typedef std::vector<std::string> t_matrix;

// Rename the struct to avoid conflict with the typedef
struct matrix_struct {
    // Your struct members go here
};

#endif // TYPES_HPP
