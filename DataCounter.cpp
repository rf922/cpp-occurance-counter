/* 
 * File:   DataCounter.cpp
 * Author: rf922
 * implementation of DataCounter
 * Created on January 22, 2024, 3:52 PM Public 
 */

#include "DataCounter.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <thread>

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

/**
 * function to get the size of the data file
 * @param filePath 
 * @return 
 */
std::streampos getFileSize(const std::string& filePath) {
    std::ifstream dataFile(filePath, std::ios::binary | std::ios::ate);
    if (!dataFile) {
        throw std::runtime_error(filePath + " could not be opened!");
    }
    return dataFile.tellg();
}

/**
 * Core logic which processes the file itself by taking in a path, value to search for
 * and the number of threads to be used. Then computes the appropriate chunck
 * size. Then a for loop is used to init each thread by tracking the starting and ending 
 * pos of the given thread and creating each thread passing countOccurances and a 
 * refference to the number of occurances. Once the function completes the number of occurances
 * are shown to the screen along with the number of threads that were used
 * @param filePath
 * @param val
 * @param numThreads
 */
void processFile(const std::string& filePath, int32_t val, unsigned int numThreads) {
    std::streampos fileSize = getFileSize(filePath);
    std::atomic<int> totalCount = 0;
    std::vector<std::thread> threads;
    std::streampos chunkSize = fileSize / numThreads;

    for (unsigned int i = 0; i < numThreads; ++i) {
        std::streampos start = i * chunkSize;
        std::streampos end = (i == numThreads - 1) ? fileSize : static_cast<std::streampos>((i + 1) * chunkSize);
        threads.emplace_back(countOccurrences, val, start, end, std::ref(totalCount));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Number of occurrences of '" << val << "': " << totalCount << std::endl;
    std::cout << "Number of Threads used : " << numThreads << std::endl;
    
}
