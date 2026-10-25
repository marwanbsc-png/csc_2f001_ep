# Hello World!!!

Create a directory `lab1` in the `csc_2f001_ep` directory. In `lab1`, create a file `hello.c` with a code editor (e.g., vscode, emacs, vim, please don't use gedit, nano or notepad which are really not designed to write code). In `hello.c`, write an application that prints `Hello World!!!` in the terminal and exits by returning the value 0. This value 0 means "the command ended successfully" for bash. Any other value means that an error occurred.

In the terminal, use `gcc` to compile your amazing application. For that, you have to use the command:

```
gcc -Wall -Werror hello.c -o hello
```

* `gcc`: gcc is the program that compiles a c file into an executable,
* `-Wall`: indicates that you want `gcc` to report any warning. This is very useful to avoid mistakes that may lead to bugs.
* `-Werror`: indicates that you want `gcc` to consider any warning as an error. In conjunction with `-Wall`, `-Werror` is very helpful to avoid bugs.
* `hello.c`: the source file that you want to compile,
* `-o hello`: generates the executable in the file `hello`.

By using `ls`, check that the directory now contains a `hello.c` and a `hello` file.

Finally, start your application in the terminal with the command `./hello`. This command means that you want to execute the program `hello` located in the working directory (i.e., the `.` directory).

🎉 **Congratulation, you are now able to write a program in C!**