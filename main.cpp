/*
 * 
 * 
 * 
 */

/* 
 * File:   main.cpp
 * Author: rf922
 * An expansion on an old assignment from csc177 at ccsf.
 * The program opens and reads from threesData.bin and orginally only counted 
 * for the occurances of the number '3'. 
 * Created on February 17, 2021, 10:48 AM Public
 */
#include <iostream>
#include <fstream>
#include <span>
#include <optional>
#include <stdexcept>

using namespace std;

/**
 * Parses command line arguments that are passed, expects an int N
 * @param argc
 * @param argv
 * @return 
 */

std::optional<int32_t> parseArgument(int argc, char** argv) {
    if (argc > 1) {
        try {
            int32_t val = std::stoi(argv[1]);
            if (val < 0) {
                std::cerr << "Invalid argument: " << argv[1] << " is a negative number." << std::endl;
                return std::nullopt;
            }
            return val;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << argv[1] << " is not an integer." << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Invalid argument: " << argv[1] << " is out of range for an int32_t." << std::endl;
        }
    }
    return std::nullopt;
}

int main(int argc, char** argv) {
    try {
        auto targetValue = parseArgument(argc, argv).value_or(3);

        //init the count to 0 and a temp container for value read
        int count = 0;
        int32_t dataValue;
        
        //init the input file stream to read from 
        ifstream dataFile("data/threesData.bin", ios::binary);
        
        if (!dataFile) {
            throw runtime_error("threesData.bin could not be opened!");
        }

        while (dataFile.read(reinterpret_cast<char *> (&dataValue), sizeof (dataValue))) {
            if (dataValue == targetValue) {
                count++;
            }
        }

        cout << "Number of occurrences of '" << targetValue << "': " << count << endl;
    } catch (const std::exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}


