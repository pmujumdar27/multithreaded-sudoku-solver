#include "sudokuGrid.hpp"

string SudokuGrid::get_gridname() {
    return this->m_strGridName;
}

void SudokuGrid::solve() {
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(cube, 0, sizeof(cube));

    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            if (gridElement[i][j]!='.') {
                int d = gridElement[i][j];
                row[i][d] = 1;
                col[j][d] = 1;
                cube[i/3][j/3][d] = 1;
            }
        }
    }

    bool ret = solveRecursive(0, 0);
}

bool SudokuGrid::solveRecursive(int i, int j) {
    if (i==9) return true;
    if (j==9) return solveRecursive(i+1, 0);

    if (gridElement[i][j]!='0') return solveRecursive(i, j+1);

    for(char d='1'; d<='9'; d++) {
        if (checkvalid(i, j, d)) {
            gridElement[i][j] = d;
            row[i][d] = 1;
            col[j][d] = 1;
            cube[i/3][j/3][d] = 1;
            if (solveRecursive(i, j+1)) return true;
            gridElement[i][j] = '0';
            row[i][d] = 0;
            col[j][d] = 0;
            cube[i/3][j/3][d] = 0;
        }
    }

    return false;
}

bool SudokuGrid::checkvalid(int r, int c, char val) {
    return (!row[r][val] && !col[c][val] && !cube[r/3][c/3][val]);
}