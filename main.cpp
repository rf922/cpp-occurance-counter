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
#include <chrono>
#include <future>
#include <thread>
#include <vector>

#include "DataCounter.h"


using namespace std;

/**
 * main entry point for the program. Verifies that the file can be opened
 * then determines a value for the number of threads to be used in the program.
 * The program then reads in the size of the file and computes an appropriate chunck
 * size to pass to each thread. Once the program completes the 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv) {
    try {
        // Init the timer and val to be searched for
        auto targetValue = parseArgument(argc, argv).value_or(3);
        auto startTime = chrono::steady_clock::now();

        // detect machines hardware to set an num threads to use
        unsigned int numThreads = thread::hardware_concurrency();
        if (numThreads == 0) {
            numThreads = 1; // Default fallback for numthreads
        }

        // verify that the file can be opened 
        ifstream dataFile(DATA_FILE_PATH, ios::binary | ios::ate);
        if (!dataFile) {
            throw runtime_error("threesData.bin could not be opened!");
        }

        // determine the files total size
        streampos fileSize = dataFile.tellg();
        dataFile.close();

        
        
        atomic<int> totalCount = 0;
        vector<thread> threads;
        
        //compute appropriate chunck size for each thread to process
        streampos chunckSize = fileSize / numThreads;

        // init each thread 
        for (unsigned int i = 0; i < numThreads; ++i) {
            
            //compute the correct start and end pos
            streampos start = i * chunckSize;
            streampos end = (i == numThreads - 1) ? fileSize : static_cast<streampos> ((i + 1) * chunckSize);
            // create and add each thread giving the func to execute, with its proper args
            threads.emplace_back(countOccurrences, targetValue, start, end, ref(totalCount));
        }

        for (auto& t : threads) { //join the threads 
            t.join();
        }

        // end time marker
        auto endTime = chrono::steady_clock::now();
        cout << "Number of occurrences of '" << targetValue << "': " << totalCount << endl;
        cout << "Number of Threads used : " << numThreads << endl;
        chrono::duration<double> elapsed_seconds = endTime - startTime;
        cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    } catch (const std::exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}


