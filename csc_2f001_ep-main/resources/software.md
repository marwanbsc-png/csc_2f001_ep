# Software used in the course

The concepts covered in this module are generic and should work on any Unix system (Linux, Mac OS, BSD, WSL...).
Therefore, you can use your personal machine for the labs.

## Installing a Unix environment

First, you have to install a Unix environment on your laptop.
For that, you have several solutions.

* For the Mac users, good news, MacOS is already a Unix system.
  You can start a terminal by clicking on `Terminal` in `/Application/Utilities`.
      
* For the Windows users, it's not more complicated, you just have to install the
  Windows Subsystem for Linux (WSL).
  You can find the installation guide [here](https://learn.microsoft.com/en-us/windows/wsl/install).
  When you start WSL, this launch a terminal.
  > **Attention:** The first time you start the terminal, run the command `sudo apt-get update` to be sure that you have the latest version of the packages.
  > 
  > **Attention:** Only use the WSL terminal in the course. Especially, don't use the default terminal of Windows (PowerShell), which is very different from the WSL terminal.
      
* For the most adventurous students, you can install a complete Linux system on a second partition,
  while keeping your current operating system (e.g., your Windows or your MacOS).
  For a first Linux installation, we advise you to use Ubuntu or Debian.
  There is plenty of documentation for these systems, and they are relatively easy to use.
  For the PC users, you can use [this tutorial](https://help.ubuntu.com/community/WindowsDualBoot),
  and for the Mac users, you can use [this one](https://help.ubuntu.com/community/DualBoot/MacOSX).

## Compilation tool chain

Now that you have a Unix environment, you need to install some applications:
`gcc`, `make`, `libc`, `git` and `cmake`.

### For the Linux and Windows/WSL users

You can install all of these packages at once with the command:

```bash
sudo apt-get install gcc make libc-dev-bin git-all cmake
```

### MacOS users

To install the compilation tool chain on a MacOS, you first have to type

```bash
xcode-select --install
```

in the terminal. This command install `gcc`, `make`, `git` and `libc`.

You will also need `cmake` and `git`.
For that, you have to install a Unix package manager on your mac.
You can use either [macport](https://www.macports.org/) or [brew](https://brew.sh/).
Install one of these package managers, and then, in a terminal, type
`sudo port install cmake git` if you use macport, or `brew install cmake git` if you use brew.

## Code editor

Finally, you need a code editor to edit your C and C++ code.
There are many different code editors.
One of the easiest at the beginning is `vscode`, you can download it from [here](https://code.visualstudio.com/).
If you are a Windows user and if you want to use vscode, you additionnaly have to:

* Install the WSL extension for VS Code. Find the extensions by clicking ![vscode extension](vscode-extension.png) button and typing WSL. The WSL extension page gives you details of what WSL is and how to use it.
* Select the green button on the lower left corner ![vscode green button](vscode-green-button.png) or press F1 to open a Command Palette.
* Choose an option WSL:Open Folder in WSL, then choose a path of your working directory (ex. path to cse201/lab1). Wait for WSL to be initialized.
* Use Ctrl+Shift+` or choose Terminal-> New terminal, to open a terminal in your working directory in VS code. This terminal uses WSL as a backend and you can run all Linux commands required for the lecture.

If you are more adventurous, you can try `emacs` or `vim`.
These code editors are very powerful, but the interface is not what we can call user friendly.
If you want to try, on a Linux or Windows/WSL, just type `apt-get install emacs` or `apt-get install vim`.
On a MacOS, you already have the `emacs` and `vim` commands installed.
However, they run directly in the terminal, which is maybe not very convenient for a beginner.
For an emacs with a graphical user interface, you can use [Emacs for MacOS X](https://emacsformacosx.com/).
The default configuration is not perfect because the shortcuts to type the characters commonly used when programming are not properly configured (e.g., braces, brackets).
To have a correct configuration, you have to edit the file `~/.emacs` with `emacs ~/.emacs` and type:

```elisp
(setq mac-option-modifier nil
      mac-command-modifier 'meta
      x-select-enable-clipboard t)
```

## Special characters on a Mac

For the Mac users, you need to learn the shortcuts for typing commonly used characters when programming.
The `Alt` key is called `option` on a Mac keyboard.
These shortcuts should be the same in both the terminal and your code editor.

* Shift-Alt-( : [
* Shift-Alt-) : ]
* Shift-( : {
* Shift-) : }
* Alt-n : ~
* Shift-Alt-l : |
* Shift-Alt-/ : \