/* 
 * File:   DataCounter.cpp
 * Author: rf922
 * implementation of DataCounter
 * Created on January 22, 2024, 3:52 PM Public 
 */

#include "DataCounter.h"
#include <iostream>
#include <stdexcept>


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
/**
 * logic to open and count occurrences of a val within a file and increment
 * the total count of occurrences 
 * @param val the value to be search
 * @param start starting pos in the file
 * @param end ending pos in the file
 * @param count total count of times val has been seen
 */
void countOccurrences(int32_t val, std::streampos start, std::streampos end, std::atomic<int>& count) {
    //init the input file stream to read from 
    std::ifstream dataFile(DATA_FILE_PATH, std::ios::binary);

    if (!dataFile) {//ensure the file can be opened
        throw std::runtime_error("threesData.bin could not be opened!");
    }
    
    dataFile.seekg(start); // move to starting pos in the file
    int32_t dataValue; //init val to store value from file
    
    // while the current pos has not reached the end and vals can be read 
    while (dataFile.tellg() < end && dataFile.read(reinterpret_cast<char *> (&dataValue), sizeof (dataValue))) {
        //compare and increment the count as maches are seen
        if (dataValue == val) {
            count++;
        }
    }

}
