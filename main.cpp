#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
#include "sudokuGrid.hpp"
#include <chrono>

using namespace std;

fstream inFile, outFile;
mutex inFileMutex, outFileMutex;

fstream& operator>>(fstream& os, SudokuGrid& gridIn) {
    char tmp;

    if (os.is_open()) {
        getline(os, gridIn.m_strGridName);
    }

    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            gridIn.gridElement[i][j] = os.get();
        }
        tmp = os.get();
        // read the `\n` at the end of each line of grid into garbage variable
        // this prevents us from getting `\n` in our grid
    }

    return os;
}

fstream& operator<<(fstream& os, SudokuGrid& gridOut) {
    os << gridOut.m_strGridName << "\n";

    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            os << gridOut.gridElement[i][j];
        }
        os << "\n";
    }
    
    return os;
}

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

    // check single threaded speed
    // unsigned int numThreads = 2;

    cout<<"Max no. of threads that can run = "<<numThreads<<"\n";
    cout<<"Spawning max - 1 threads\n";

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