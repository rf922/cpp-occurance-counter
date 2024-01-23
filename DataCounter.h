/* 
 * File:   DataCounter.h
 * Author: rf922
 * Logic for parsing the command line arguments and counting occur the time a 
 * Created on January 22, 2024, 3:52 PM Public
 */

#ifndef DATA_COUNTER_H
#define DATA_COUNTER_H

#include <fstream>
#include <optional>
#include <atomic>
#define DATA_FILE_PATH "data/threesData.bin"

std::optional<int32_t> parseArgument(int argc, char** argv);
void countOccurrences(int32_t val, std::streampos start, std::streampos end, std::atomic<int>& count);

std::streampos getFileSize(const std::string& filePath);
void processFile(const std::string& file, int32_t val, unsigned int numThreads);

#endif // DATA_COUNTER_H
