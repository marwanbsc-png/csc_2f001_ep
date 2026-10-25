# The sudoku solver (training exercise, not mandatory)

> **Note:**
> Doing this exercise is not required.
> It is only here for students who already master the Unix environment and GitLab, so that they have something interesting to do during the lab session.

In this exercise, you will write a sudoku solver.
A sudoku is defined by a grid of 9 columns by 9 rows.
Each cell must contain a number between 1 and 9.
The aim of the game is to fill in the grid in such a way that each number between 1 and 9 appears at most once in (i) each row, (ii) each column and (iii) each of the sub-squares shown in the figure below.
At the start of the game, some numbers are placed in the grid, and the player has to find the remaining ones.

```text
-------------------------
| . 1 . | 6 . 7 | . . 4 |
| . 4 2 | . . . | . . . |
| 8 7 . | 3 . . | 6 . . |
-------------------------
| . 8 . | . 7 . | . 2 . |
| . . . | 8 9 3 | . . . |
| . 3 . | . 6 . | . 1 . |
-------------------------
| . . 8 | . . 6 | . 4 5 |
| . . . | . . . | 1 7 . |
| 4 . . | 9 . 8 | . 6 . |
-------------------------
```

The grid solving the sudoku shown above is shown below:

```text
-------------------------
| 9 1 3 | 6 2 7 | 5 8 4 |
| 6 4 2 | 5 8 9 | 7 3 1 |
| 8 7 5 | 3 4 1 | 6 9 2 |
-------------------------
| 5 8 9 | 1 7 4 | 3 2 6 |
| 2 6 1 | 8 9 3 | 4 5 7 |
| 7 3 4 | 2 6 5 | 8 1 9 |
-------------------------
| 1 2 8 | 7 3 6 | 9 4 5 |
| 3 9 6 | 4 5 2 | 1 7 8 |
| 4 5 7 | 9 1 8 | 2 6 3 |
-------------------------
```

To represent a grid in C, we could use a two-dimensional array of size 9 by 9.
However, a two-dimensional array will turn out to be difficult to manage with the algorithm that we will implement to solve the sudoku.
For this reason, we advise you instead to implement the grid with a one-dimensional array of 81 elements.
With such an implementation, you access the $j^{\text{th}}$ column of the $i^{\text{th}}$ line of the grid simply by accessing the element at position `i*9 + j` in the one-dimensional array.

## Question 1

In order to test your application, you first need some sudoku grids.
For that, you have to download [grids.tar.xz](grids.tar.xz), to extract it (with `tar xf grids.tar.xz`), and to move the `grids` directory in `csc_2f001_ep/lab1`.

## Question 2

Write a `sudoku.c` file that:
* quits with a message if the program does not exactly receive one argument,
* and prints this argument in the terminal.

For example, running `./sudoku grids/grid01/grid.bin` should output `grids/grid01/grid.bin`.

To manage the arguments, you have to know that:
* The signature of the `main` function is `int main(int argc, char* argv[])`,
* `argc` gives the number of arguments, knowing that the name of the program itself account for one argument,
* `argv[i]` is the $i^{\text{th}}$ argument (`argv[0]` is the name of the program).

## Question 3

The argument provided to the program is a path to a binary file that contains a grid.
In details, the binary file contains 81 integers (4 bytes each).
Write a function `int read_sudoku(const char* path, int grid[])` that reads the content of the file `path` into the grid `grid`.
The function has to return -1 if an error occurred and 0 otherwise.
In the `main` function, instead of writing the argument of the program, you have to call `read_sudoku` with the argument.

In order to read a file, you need these functions:
* `int open(const char* path, int oflags)` (provided by `fcntl.h`): open the file `path` and returns a **file descriptor** that can be used to access the file. `oflags` indicates how you want to open the file (read, write, create etc...). In our case, we want to read from the file, so we will use the flag `O_RDONLY`.
* `ssize_t read(int fd, void* buf, size_t nbytes)` (provided by `unistd.h`): read `nbytes` in `buf` from the file descriptor `fd`. You will better understand what is `void*` in the next labs.
  For the moment, imagine that `void*` means "any array".
  As a result, to read the content of the file identified by the file descriptor `fd`, you have to insert this code:
  ```c
  read(fd, grid, 81 * sizeof(int));
  ```
  Thanks to that, `read` will read 81 times the size of an `int` from the file identified by `fd`, and put these bytes into the grid.

To use the `open` and `read` functions, you may need to add this line at the top of your source file:

```c
#include <fcntl.h>
```

In order to test your program, you have to run `./sudoku grids/grid01/grid.bin`.

Note that you can find a lot of useful information about the `open` and `read` by typing the command `man 2 open` or `man 2 read` in the terminal.

## Question 4

Write a `void print_sudoku(int grid[])` function that prints the sudoku grid in the terminal.

```text
-------------------------
| . 1 . | 6 . 7 | . . 4 |
| . 4 2 | . . . | . . . |
| 8 7 . | 3 . . | 6 . . |
-------------------------
| . 8 . | . 7 . | . 2 . |
| . . . | 8 9 3 | . . . |
| . 3 . | . 6 . | . 1 . |
-------------------------
| . . 8 | . . 6 | . 4 5 |
| . . . | . . . | 1 7 . |
| 4 . . | 9 . 8 | . 6 . |
-------------------------
```

In order to test your program, you have to run `./sudoku grids/grid01/grid.bin`.

## Question 5

We propose that you solve your grid using a backtracking method.
This method involves trying out values and, if they lead to an inconsistent grid, going back to try a different value.
Modify your program so that it solves the sudoku using this method.

### High level overview
At a high level, you need to iterate through the grid with a variable `cur`.
This variable is initialized to 0, and the algorithm loops while `cur` has not reached 81 (which means the grid has been solved) and while `cur` has not dropped below 0 (which means the grid cannot be solved).

For a given `cur`, the algorithm must try a new value for the cell `grid[cur]` (if it is not initially given) by incrementing its value. If this value reaches 10, it means that a value tried in a previous cell does not lead to a solution for the grid, so the algorithm must backtrack. Otherwise, if this new value conflicts with a value already in the grid, the algorithm should try the next value. Finally, if the new value does not conflict, the algorithm can attempt to solve the rest of the grid by moving to the next cell.

**The remaining text guides you step by step: only read it if you get stuck, otherwise try to solve the problem on your own.**

### Identifying the initial values
Since the algorithm modifies the grid in place, the grid contains both initial values and tried values.
When the algorithm backtracks, `cur` has to go back to the previously tried value by jumping the initial values.
For this reason, the algorithm has to know which cells initially contain a value.
For that, you should define a boolean array named `fixed` and set a cell's value to `true` if and only if that cell initially contains a value (i.e., if the corresponding cell in grid initially has a value other than 0).

**The remaining text guides you step by step: only read it if you get stuck, otherwise try to solve the problem on your own.**

### Step by step resolution (advanced)
Once you know where the initial values are, at each iteration, your code has to handle these cases:
* If `grid[cur]` contains an initial value, the algorithm has to increment `cur`,
* Otherwise, the algorithm has to increment `grid[cur]` by 1.
  At this step, you have different choices:
  * If `grid[cur]` is equal to 10, it means that a previous cell contains a value that makes the grid unsolvable.
    The algorithm has thus to backtrack by:
    * Setting the value of `grid[cur]` to 0 for the next attempts.
    * Decrementing `cur` to the previous non-initial value.
      Note that, `cur` can become lower than 0.
      If this happens, it means that the grid does not have a solution.
  * If `grid[cur]` is strictly lower than 10, you have to check that the new value of `grid[cur]` is valid.
    For that, you have to verify that the value of `grid[cur]` only appears once in:
    (i) the column of `grid[cur]`,
    (ii) the line of `grid[cur]`, and
    (iii) the square of `grid[cur]`.
    If the value is valid, you can increment `cur` to work on the next cell in the next loop iteration.
    If the value is not valid, you don't have anything to do: a new value for `grid[cur]` will be tested in the next loop iteration.

**The remaining text guides you step by step: only read it if you get stuck, otherwise try to solve the problem on your own.**

#### Testing whether a value is correct
In order to test whether a value is correct, you need two variables `column` and `line`, which give the coordinate of `cur` in the 2-dimensional grid.
In detail, `column` is equal to `cur % 9`, while `line` is equal to `cur / 9`.

* To test the line of `cur`, you have to compare the value of `grid[cur]` with the value located at `grid[line * 9 + i]`, where `i` goes from 0 to 9.
* To test the column of `cur`, you have to compare the value of `grid[cur]` with the value located at `grid[i * 9 + column]`, where `i` goes from 0 to 9.
* To test the square of `cur`, it's slightly more complex.
  You need the coordinate of the upper left corner of the square that contains `cur`.
  The column `csquare` of this upper left corner is equal to `3 * (column / 3)` and its line `cline` is `3 * (line / 3)`.
  Then, you have to compare the value of `grid[cur]` with the value of `grid[9 * ((cline * 3) + i) + (ccolumn * 3) + j]` where `i` and `j` go from 0 to 3.

🎉 **Congratulations, you are now able to write complex programs in C!**