#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
#include "sudokuGrid.hpp"
#include <chrono>

using namespace std;

fstream inFile, outFile;
mutex inFileMutex, outFileMutex;

void solveSudokuPuzzles(int tid) {
    do {
        SudokuGrid sg;
        
        inFileMutex.lock();
        // cout<<"This is thread: "<<tid<<"\n";
        inFile >> sg;
        inFileMutex.unlock();

        sg.solve();

        outFileMutex.lock();

        outFile<<sg;

        outFileMutex.unlock();
    }
    while (!inFile.eof());
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout<<"[ERROR] Argument INPUT_FILE missing!\n";
        return 1;
    }
    char* filename = argv[1];
    
    inFile.open(filename);

    outFile.open("output.txt");

    unsigned int numThreads = thread::hardware_concurrency();

    // check single worker thread speed
    // unsigned int numThreads = 2;

    cout<<"Max no. of threads that can run-> Max = "<<numThreads<<"\n";
    cout<<"Spawning Max - 1 = "<<numThreads-1<<" worker threads\n";

    vector<thread*> threads;

    auto start = chrono::high_resolution_clock::now();

    for(int i=0; i<numThreads-1; i++) {
        threads.push_back(new thread(solveSudokuPuzzles, i));
    }

    for(int i=0; i<numThreads-1; i++) {
        threads.at(i)->join();
        delete threads.at(i);
    }

    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);

    cout<<"Time taken in ms: "<<duration.count()<<"\n";

    cout<<"Done main()\n";

    return 0;
}