# Surviving in the terminal

In the remainder, you will find many useful `bash` commands. For the "introduction to C++ course", you have to know the commands used to access the file system. The other commands are only here for the curious students who would like to master `bash`.

For a colored prompt, type:
```
export PS1='\[\033[01;31m\]\u\[\033[00m\]@\[\033[01;36m\]\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
```

## File System

| Command | Description |
| :--- | :--- |
| `cd [path]` | Sets the current directory to “path” or to the home directory (HomeDirectory) if no parameter is given. |
| `cp f1 f2` | Copies the file `f1` to the file `f2`. If `f2` already existed, its previous content is lost. |
| `ls [opt] [list]` | For each item `e` in `list`, displays the contents of the directory `e` if it is a directory or the name of the file `e` if it is a file.<br><br>A number of options can be specified (opt). Here are a few:<br>- `-l`: displays a number of information related to the items (type, size, date...).<br>- `-a`: shows all items, including hidden files and directories (on Unix, hidden items start with the character “.”).<br>- `-d`: displays the name of the directory and not its contents. |
| `tree [path]` | Displays the directory tree of files accessible from `path`. If `path` is not specified, uses the current directory. |
| `mkdir [opt] dir` | Creates the directory `dir` in the current directory. If the `-p` option is specified, intermediate directories are also created. |
| `mv f1 f2` | Moves the file `f1` to `f2`. This command can also be applied to directories. If `f2` already existed, its previous content is lost. After the operation, `f1` no longer exists. |
| `pwd` | Displays the absolute path of the current directory (the one you are in). |
| `rm f1` | Deletes the file `f1`. |
| `rmdir dir` | Deletes the directory `dir`, provided that it is empty. |
| `sleep n` | Pauses the process for `n` seconds. |

## Useful commands

| Command | Description |
| :--- | :--- |
| `cat file` | Displays the contents of the file `file` to the standard output. |
| `echo args` | Displays the arguments `args` to the standard output. |
| `expr expression` | Calculates the result of the arithmetic expression provided as an argument and displays the result to the standard output. Note that it only works with integer arithmetic. Typically, you can increment a counter `i` with the expression `i=$(expr $i + 1)`. |
| `grep [opt] pattern file` | Displays to the standard output the lines from `file` that match the pattern `pattern`. If the `-v` option is specified, lines that do not match the pattern `pattern` are displayed. If no file name is given, searches from the standard input. The patterns used by `grep` are different from those used by `bash`, and students are encouraged to consult the `man` page. For `grep`, the character `^` indicates the start of a line and the character `$` indicates the end of a line. |
| `du [opt] file` | Displays the size of the file `file` in number of blocks followed by the file name (one block corresponds to 512 bytes). The `-h` option allows displaying the size using units more commonly used by humans. |
| `read var` | Copies the line of characters read from the standard input into the variable `var`. Typically, to read a line from a file, use `read var < file`. To read a file line by line, use `while read var; do echo $var; done < file`. |
| `touch file` | Creates the file `file` if it does not already exist. |
| `which cmd` | Indicates the absolute path of the command `cmd` after searching for `cmd` in the `PATH`. |
| `alias cmd='...'` | `cmd` becomes an alias for the command `...`. `alias` without other options lists the aliases used by `bash`. |
| `unalias cmd` | Removes the alias associated with `cmd`. |
| `source script.sh` or `. script.sh` | Executes the instructions in `script.sh` in the current process. |

## `bash` patterns

| Pattern | Description |
| :--- | :--- |
| `*` | Any sequence of characters. |
| `?` | Any single character. |
| `[wtz]` | The character `w` or the character `t` or the character `z`. |
| `[d-r]` | All characters between `d` and `r`. |
| `[[:lower:]]/[[:upper:]]` | Lowercase/uppercase alphabet (including accented characters). |
| `[[:digit:]]` | Decimal digits. |
| `[[:alpha:]]` | All alphabetic characters, that is, all letters of the alphabet (including accented characters). |

## Important variables

| Variable | Description |
| :--- | :--- |
| `HOME` | Path to the login directory. |
| `PS1` | Prompt used by `bash`. For example, `PS1="\w$ "` provides a prompt that indicates the current directory. |
| `PS2` | Prompt for multi-line commands. |
| `PATH` | List of paths separated by `:` where `bash` searches for commands. |

## Input-output redirection

| Command / Syntax | Description |
| :--- | :--- |
| `exec n<> file` | Opens file descriptor number `n` for reading and writing from `file` (overwriting its content).<br>For example: `exec 3<>my-pipe.pipe`. In the rest of the script, you can then execute `echo hello >&3` to write data or `read x <&3` to read data. |
| `exec n> file` | Opens file descriptor number `n` for writing from `file` (overwriting its content). |
| `exec n>> file` | Opens file descriptor number `n` for appending to `file`. |
| `exec n< file` | Opens file descriptor number `n` for reading from `file`. |
| `cmd >&n` | Redirects the standard output of the command `cmd` to file descriptor number `n`. |
| `cmd <&n` | Redirects the standard input of the command `cmd` from file descriptor number `n`. |
| `cmd > file` | Opens a file descriptor for writing from `file` (overwriting its content), before redirecting the output of `cmd` to the file. |
| `cmd >> file` | Opens a file descriptor for writing from `file` (appending to the end), before redirecting the output of `cmd` to the file. |
| `cmd < file` | Opens a file descriptor for reading from `file`, before redirecting the input of `cmd` from the file. |

## Processes

| Command / Syntax | Description |
| :--- | :--- |
| `;` | Allows separating two commands executed sequentially. |
| `&` | Executes the command on the left in the background. |
| `$$` | Process ID (PID) of the current running process. |
| `$PPID` | Process ID (PID) of the parent process of the current running process. |
| `$!` | Process ID (PID) of the last background process. |
| `$?` | Return value of the last command executed in the foreground. |
| `exit [n]` | Terminates the execution of a script with the return value `n`. By convention, a command returns a value other than `0` in case of an error and `0` otherwise. |
| `export var` | Creates a copy of the variable `var` for child processes. The variable will also be exported to the children. |
| `wait [n1 n2 ...]` | Blocks the current process until the child processes with the specified identifiers are terminated. If no parameters are given, the process waits for all of its children to finish. |
| `$(xyz)` | The shell substitutes `$(xyz)` with the text produced on standard output by executing the command `xyz`. |
| `ps [opt]` | Displays the list of running processes. A number of options can be specified (opt). Here are a few:<br>- `l`: displays various information about the processes (PPID, status, priority...).<br>- `e`: displays a list of all processes (not just those attached to the current terminal).<br>- `u`: displays the username of the user who started each process. |
| `pstree` | Displays the process tree. |
| `top` | Provides a dynamic real-time view of running processes. |

## Arguments

| Command / Variable | Description |
| :--- | :--- |
| `$#` | Number of command line parameters. |
| `$n` with `n ∈ [0,9]` | Value of the n<sup>th</sup> parameter. `$0` corresponds to the name of the invoked command. `$n` corresponds to an empty string if there are fewer than `n` parameters. |
| `"$@"` | Gives all parameters starting from `$1` while preserving spaces within each parameter. Equivalent to writing `"$1" "$2" ...`. |
| `shift [n]` | Shifts the script parameters (by default one shift) or by “`n` shifts” (if `n` is specified). For example, if `n` is not specified, `$2` becomes `$1`, `$3` becomes `$2`, and so on...<br>**Attention:** The behavior is not specified if the number of parameters is insufficient. |

## Strings and character escaping

| Syntax | Description |
| :--- | :--- |
| `\x` | A `\` escapes any character that would normally have a special meaning to the shell. For example, `\*` is interpreted as the character `*` and not as the pattern `*`. `\\` corresponds to the character `\`. |
| `"xyz"` | Protects the string `xyz` from splitting on spaces during argument separation. Prevents the interpretation of language meta-characters, except for `$`, `` ` `` and `\`. In particular, variables (`$mavar`) and command substitutions (`$(xyz)`) are interpreted. |
| `'xyz'` | Protects the string `xyz` from splitting, like double quotes, but performs no substitution. No character other than `'` has a special meaning in a single-quoted string, not even `\`. |

## Tests

| Expression | Description |
| :--- | :--- |
| `[ -z ch1 ]` | Returns true if the string `ch1` is empty. |
| `[ -n ch1 ]` | Returns true if the string `ch1` is non-empty. |
| `[ ch1 = ch2 ]` | Returns true if the strings `ch1` and `ch2` are equal. |
| `[ ch1 != ch2 ]` | Returns true if the strings `ch1` and `ch2` are different. |
| `[ n1 -eq n2 ]` | Returns true if the numbers `n1` and `n2` are equal. For example, `[ "01" -eq "1" ]` returns true since the numbers are equal, while `[ "01" = "1" ]` returns false since the strings are different. |
| `[ n1 -ne n2 ]` | Returns true if the numbers `n1` and `n2` are different. |
| `[ n1 -lt n2 ]` | Returns true if the number `n1` is strictly less than the number `n2`. |
| `[ n1 -le n2 ]` | Returns true if the number `n1` is less than or equal to the number `n2`. |
| `[ n1 -gt n2 ]` | Returns true if the number `n1` is strictly greater than the number `n2`. |
| `[ n1 -ge n2 ]` | Returns true if the number `n1` is greater than or equal to the number `n2`. |
| `[ -e path ]` | Returns true if the path `path` exists in the file system (file, directory, symbolic link, etc.). |
| `[ -f path ]` | Returns true if `path` is a file. |
| `[ -d path ]` | Returns true if `path` is a directory. |
| `[ -L path ]` | Returns true if `path` is a symbolic link. |
| `! test` | Returns true if `test` returns false. For example, `! [ 42 -eq 67 ]` returns true. |
| `test1 && test2` | Returns true if both `test1` and `test2` return true. |
| `test1 \|\| test2` | Returns true if either `test1` or `test2` returns true. |

## Control structures

| Syntax | Description |
| :--- | :--- |
| `if test1; then`<br>`  body1`<br>`elif test2; then`<br>`  body2`<br>`else`<br>`  body3`<br>`fi` | Executes `body1` if `test1` returns true. If `test1` returns false, executes `body2` if `test2` returns true, and `body3` otherwise. The `elif` and `else` parts are optional. |
| `while test; do`<br>`  body`<br>`done` | Executes `body` as long as the `test` returns true. |
| `for var in list; do`<br>`  body`<br>`done` | For `var` taking on each value in the list (a list is a sequence of words separated by spaces), executes `body`. |
| `case $var in`<br>`  pattern1) body1;;`<br>`  pattern2) body2;;`<br>`  ...`<br>`  patternn) bodyn;;`<br>`esac` | Finds the first `pattern` that matches `$var` and executes the associated `body`. |
| `( expression )` | Allows grouping commands. Useful for giving precedence to `!`, `||` and `&&` operators in tests. For example, `[ 42 -eq 65 ] || ( [ 65 -eq 65 ] && [ 63 -eq 63 ] )` returns true. Can also be used to redirect input/output of multiple commands simultaneously. For example, `( ls; cat /etc/passwd ) > file` |

## Communication

| Command / Syntax | Description |
| :--- | :--- |
| `\|` | Anonymous communication pipe between two processes: connects the standard output of the command on the left to the standard input of the command on the right. |
| `kill -sig pid` | Sends the signal `sig` (`sig` is a signal number or name, with or without the `SIG` prefix) to the process with identifier `pid`. |
| `kill -l` | Displays the list of signals (name and numeric value). |
| `mkfifo path` | Creates a named pipe with the name `path`. |
| `trap [arg] sig` | Executes `arg` when handling the signal `sig` (`sig` is a signal number or name, with or without the `SIG` prefix). If `arg` is an empty string, the signal is ignored. If `arg` is omitted, the default signal handling is restored. |