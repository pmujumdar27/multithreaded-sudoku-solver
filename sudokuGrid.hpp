#pragma once

#include <fstream>
#include <string>

using namespace std;

class SudokuGrid
{
    public:
        friend fstream& operator>>(fstream &os, SudokuGrid& gridIn);
        friend fstream& operator<<(fstream &os, SudokuGrid& gridOut);
        void solve();

        string get_gridname();

    private:
        string m_strGridName;
        unsigned char gridElement[9][9];
        int row[9][256], col[9][256], cube[3][3][256];
        bool solveRecursive(int i, int j);
        bool checkvalid(int r, int c, char val);
};