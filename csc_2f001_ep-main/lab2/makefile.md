# My first Makefile

In this lab, we also introduce you to Makefiles. A Makefile is like a recipe used to generate an executable from source code. For now, your Makefile will be quite simple and will mainly help you avoid typing `gcc -Wall -Werror -o executable source` in the terminal. In future labs, you will create more advanced Makefiles and discover how powerful this tool can be.

## Question 1

In your local `csc_2f001_ep` repository, create a directory named `lab2`. In this directory, create a file `sierpinski.c` that print "Hello, world!!!" in the terminal. Compile it with `gcc -Wall -Werror -o sierpinski sierpinski.c` and executes it.

Once the compilation is done, tell git to track `sierpinski.c` with `git add sierpinski.c`. Commit the changes with `git commit -a -m "Start lab2"`, and push your changes on gitlab with `git push`.

While you will write your code in the labs, think that it's very useful to commit (and push) regularly your changes: if your computer crashes, this ensures that your lab is saved on gitlab.

## Question 2

Now, download the file [Makefile](Makefile) in the directory of `sierpinski.c` (be carreful: your browser may propose to save the file with the name "Makefile.txt" instead of "Makefile", if it happens, rename the file into "Makefile"). Add it to your repository with `git add Makefile`.

After this exercise, we will not recall you that you have to add your source files to you to track files, or that you have to commit and push your changes. Don't forget that it's important to avoid losing your code, and that we will use your gitlab repositories to grade your labs. If you forget to synchronize your local repository with the gitlab repository, you may end up with a zero.

## Question 3

Read carefully the file `Makefile` and try to understand:

- Why, when you edit and modify "sierpinski.c" and then execute `make` in the terminal, `make` executes `gcc -Wall -Werror -o sierpinski sierpinski.c`?
- Why, if you execute `make` a second time, the command does not do anything?
- Why, if you execute `make clean` and then `make`, the command re-generates the executable `sierpinski` from `sierpinski.c`.

Ask your teacher if you have any doubt

> **Remarque :** In the remainder of the lab, you can use this Makefile: instead of compiling your code with a long `gcc` command, you just have to type `make`.