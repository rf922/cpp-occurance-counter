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
        
        // detect machines hardware to set an num threads to use
        unsigned int numThreads = thread::hardware_concurrency();
        
        // init timers
        auto startTime = chrono::steady_clock::now();
        auto endTime = chrono::steady_clock::now();
        chrono::duration<double> elapsedTime;

        if (numThreads == 0) {
            numThreads = 1; // Default fallback for numthreads
        }


        if (numThreads != 1) { //multi threading was available 
            cout << "MultiThreading is supported \n";
            /* using all available threads  */
            startTime = chrono::steady_clock::now();
            processFile(DATA_FILE_PATH, targetValue, numThreads);
            endTime = chrono::steady_clock::now();
            elapsedTime = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
            cout << "Elapsed time: " << elapsedTime.count() << "s\n";


            /*  Using half of the available threads */
            startTime = chrono::steady_clock::now();
            processFile(DATA_FILE_PATH, targetValue, numThreads / 2);
            endTime = chrono::steady_clock::now();
            elapsedTime = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
            cout << "Elapsed time: " << elapsedTime.count() << "s\n";


        } else {
            cout << "MultiThreading is not supported " << endl;
            cout << "Performing only single threaded run " << endl;
        }

        /*  using a single thread */
        startTime = chrono::steady_clock::now();
        processFile(DATA_FILE_PATH, targetValue, 1);
        endTime = chrono::steady_clock::now();
        elapsedTime = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
        cout << "Elapsed time: " << elapsedTime.count() << "s\n";
    } catch (const std::exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}


