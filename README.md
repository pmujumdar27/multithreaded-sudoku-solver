# multithreaded-sudoku-solver

Author: [Pushkar Mujumdar](https://github.com/pmujumdar27)

## Input and Output Format
Input format is as follows:
```
There are n unsolved Sudoku Grids.
    First line of each of the n grids is the grid name, eg. Grid 01
    The next 9 lines contain 9 characters each (0-9), with 9 denoting empty sudoku cell
    These 9 lines of 9 characters each denote unsolved sudoku (blanks represented by 0)
```

Output Format:
```
Output format is same as input format:
    First line contains grid name, eg. Grid 02
    Next 9 lines contain 9 characters each (1-9)
    These 9 lines of 9 characters each make a solved sudoku
```
Output is directed to `output.txt` by default

---

## Usage

A [Makefile](./Makefile) is provided along with the code.  
To make use of the Makefile provided, install [GNU Make](https://www.gnu.org/software/make/)  
The compiler is set to `g++ -std=c++11` by default.

### Build

```
make buid
```


### Run

```
make run INPUT_FILE=<path_to_input_file>
```


### Clean

```
make clean
```

---