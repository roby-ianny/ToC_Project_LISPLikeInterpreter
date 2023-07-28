#include <iostream>
#include <filesystem>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <fstream>

namespace fsys = std::filesystem;

// Filename extensions for test inputs and outputs
constexpr const char* INPUT_EXT = ".txt";
constexpr const char* OUTPUT_EXT = ".out";
constexpr const char* LOG_FILE = "log.txt";

// Function to check that two files have the same contents
bool areSame(std::string fileName1, std::string fileName2) {
    std::ifstream file1{ fileName1 };
    std::ifstream file2{ fileName2 };
    while (!file1.eof() && !file2.eof()) {
        std::string l1; std::string l2;
        std::getline(file1, l1);
        std::getline(file2, l2);
        if (l1 != l2) {
            std::cout << "Mismatch found!" << std::endl;
            std::cout << l1 << std::endl;
            std::cout << l2 << std::endl;
            return false;
        }
    }
    if (file1.eof() && file2.eof()) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char* argv[]) 
{
    // argv[1] must contain the path to program to be tested
    // argv[2] must contain the path to a directory containing tests
    // Each test consists of two files:
    // <testname>.txt is the input file to be supplied to the program
    // <testname>.out is the expected output to be checked
    if (argc < 3) {
        std::cout << "Missing parameters!" << std::endl;
        std::cout << "Usage: " << argv[0] << " <program> <test_dir>" << std::endl;
        std::cout << "where <program> and <test_dir> are the complete pathnames to the program and the test directory" << std::endl;
        return EXIT_FAILURE;
    }

    // Create path objects for the program to test and the directory containint the tests
    fsys::path programToTest{ argv[1] };
    fsys::path testDirPath{ argv[2] };
  
    // Scan all entries of the test directory
    for (const auto& entry : 
        fsys::recursive_directory_iterator{ testDirPath }) {
    
        // When a test input is found...
        if (entry.path().extension() == std::string(INPUT_EXT)) {
        
            // Get the path of the test input
            fsys::path pathToInput{ entry.path() };
            std::cout << pathToInput.string() << std::endl;
            
            // Create the corresponding path of the test output 
            fsys::path pathToOutput{ entry.path() };
            pathToOutput.replace_extension(OUTPUT_EXT);
             
            // Run the program to test on the test input
            // The command standard output and standard error is redirected to LOG_FILE
            std::stringstream command;
            command << programToTest.string() << " "
                << "\"" << pathToInput.string() << "\"" << " >" << LOG_FILE << " 2>&1";
            std::cout << "Test: " << pathToInput.filename() << std::endl;
            system(command.str().c_str());
            
            // Check that the output of the program corresponds with the test output
            // Compare LOG_FILE with the test output
            std::cout << (areSame(LOG_FILE, pathToOutput.string()) ? "SUCCESS" : "FAILED");
            std::cout << std::endl << std::endl;
        }
    }

    return EXIT_SUCCESS;
}

