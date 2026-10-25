# Surviving in a terminal

As a first step, you will have to learn how to survive on a Unix-like system where you only have a terminal. It's important for this course because you will have to manually compile and execute your code. If you are already comfortable with a terminal, you can skip this exercise.

So, first, you have to know that when you launch a terminal, the terminal executes a process named `bash` (Bourne-Again shell). `bash` is what we name an interactive shell in command line. You type commands, and the shell executes them.

Any Unix system is organized with folders that contain files and sub-folders. On a Unix system, we don't use the term "folder", but we use the term "directory". The root directory is named `/` (slash) on any Unix system, and the directory separator is also `/`. With that, you can give full paths, for example, `/usr/bin/tar` is the full path that names the file `tar` located in the directory `bin`, which is itself located in the `usr` sub-directory of the root directory (note that you have three directories: `/`, `/usr/` and `/usr/bin/`).

At any time, `bash` considers two directories:

* The home directory: it's the basic directory where you have all your user files. Typically, in this directory, you will find the `Desktop` directory, where you have the files that you see in the graphical user interface of your system, or the `Document` directory, where the applications store by default your documents (e.g., word files etc...).
* The working directory: it's the directory that `bash` considers as the default directory when it is looking for a file. You can change it with the `cd name` command. If `name` is the name of a directory located in your working directory, then the new working directory becomes `name`. At a high-level, it's exactly like double-clicking on a directory in your file explorer. When `bash` starts, it initializes the working directory to the home directory.

A Unix system considers also two special directories:

* `.`: is the working directory. For example the path `hello.txt` and the path `./hello.txt` both represent the same file: the file `hello.txt` located in the working directory. The usage of `.` is not very obvious at a first glance, but when you write scripts, it becomes very useful.
* `..`: is the parent directory. For example the path `/usr/bin/..` and `/usr` represents the same directory: the directory `usr` located in the root directory.

The most important Unix command to manage directories are:

* `pwd` (print working directory): print the working directory,
* `echo $HOME`: print the home directory,
* `cd path` (change directory): change the working directory to path (path can be `.` or `..`)
  * `cd` (without any argument): when you omit the path, you just go back to your home directory
* `ls` (list): list the content of the working directory:
  * `ls path` lists the content of the directory path, for example `ls ..` lists the content of the directory that is the parent of the working directory.
  * `ls -a` (all) lists also the hidden files. A hidden file is a file that begin with a dot (`.`),
  * `ls -l` (long) display many useful information (size of the file, owner etc...).
* `mkdir path` (make directory): create the directory `path`,
* `rmdir path` (remove directory): remove the directory `path`,
* `cp from to` (copy): copy the file from the name `from` to the name `to` (copy to `to` and keep `from`). Only works if `from` is not a directory.
  * `cp -a from to`: copy recursively from `from` to `to`. If `from` is a directory, copy all the sub-directories and files of the sub-directories.
  * `cp -i / cp -f`: copy in interactive or force mode. In interactive mode, ask before destroying the destination. In force mode, silently override the destination (be careful!).
* `mv from to` (move): move the file from the name `from` to the name `to` (copy to `to` and destroy `from`).
  * `mv -i / mv -f`: move in interactive or force mode. In interactive mode, ask before destroying the destination. In force mode, silently override the destination (be careful!).
* `rm path` (remove): delete the file `path`. Only works if `path` is a file.
  * `rm -r path`: remove recursively `path`. If `path` is a directory, it means that you remove all the files and sub-directories reachable from path, use with caution!
  * `rm -f / rm -i`: as for `cp` or `mv` (interactive or force mode).

Be careful with the `-i, -a, -r` switches of `cp`, `mv` and `rm`: you can easily loose files with that because `bash` does not manage a trashcan like your graphical user interface!

A final note: in `bash`, when you type the tab key, `bash` can complete the command. If `bash` has several possibilities to complete the command, it emits a bip and nothing else happens. You just jave to re-type tab to see the possibilities, and to continue to type your command. It's very useful. Otherwise, `bash` memorizes the last commands in a history. You can retrieve them simply by using the `up` and `down` arrows.

## Question 1: home directory

By using a `bash` command, find your home directory. Try to also find it in the (graphical) file explorer of your operating system (e.g. windows explorer, finder).

## Question 2: create a directory for the course

Create a directory named `csc_2f001_ep` in your home directory. Check with a graphical file explorer that the directory exists.
