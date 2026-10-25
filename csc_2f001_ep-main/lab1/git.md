# Setting up your gitlab repository

To grade your labs, we will use the `GitLab` hosted by the binet association. `GitLab` is an online developer platform used to store your code.

> ⚠️  **The binet GitLab server has been down for the last few days. If it is still the case, we will use GitHub and an alternative procedure. For this reason, if the server is still down, read each question completely, and if you see the ⚠️  sign explaining the alternative procedure, follow it instead of the normal one.** 

## Qestion 1: Creating an account

In theory, you should already have an account. To check that it is the case, try to log in on [https://gitlab.binets.fr](https://gitlab.binets.fr). If that’s not the case, you need to activate your account by clicking on “ma première connexion” on the Sigma server ([https://sigma.binets.fr/app/login](https://sigma.binets.fr/app/login)).

> ⚠️  **In case the gitlab of binets is unreachable: we will use github instead during this lab, and we will migrate your repository later. For that, create an account on https://github.com/.**

## Question 2: Creating a repository

Once you have your account, you have to create a project named `csc_2f001_ep` by clicking on the `New project` button. For the project group, pick your own name, and for the project “name”, use “csc_2f001_ep”. Let the visibility as private, and **unselect "Initialize repository with README"**. Finally, click on "Create repository". You should now see your beautiful project. Since the project is empty, you should see some instructions explaining how to start.

> ⚠️  **If you use GitHub instead of the binet GitLab, click on "New", name your repository csc_2f001_ep, select "Private" visibility, and make sure that "Add a README" and "Add .gitignore" are not selected, and that License is set to "No Licence".**

What you have created on GitLab is named a "repository". A repository is like a directory where you store your source files. It's not so far from dropbox, but tailored for development. GitLab manages the repository with the git tool. git is a "distributed version control system". It means that git keeps an history of the files stored in the repository. It's very useful if you make mistakes when you modify your code, and want to retrieve an older version of a file.

> **Attention:**
> Actually, git is more complex than dropbox. In particular, using the web interface to create files or subdirectories inside a git repository may lead to inconsistencies that are difficult to resolve. **For this reason, unless explicitly stated otherwise as in the following questions, never use the web interface to change the contents of a repository!**

## Question 3: Adding your professors as a friend

Now, you have to add your professors in your project through the web interface. For that, click on "Manage", then "Members", and finally "Invite member". Type "gael.thomas" and selects the user. Modify the role to `Developper`, otherwise, we will not see your code. Finally, click on invite. Do the same with the user "julien.tierny".

> ⚠️  **If you use GitHub instead of the binet GitLab, you have to invite gaelthomas. To do that, click on "Settings", "Collaborators", and then "Add people" (or simply "Invite Collaborators").**

## Question 4: Adding a ssh key to GitLab

For the moment, your source files are stored in the servers of GitLab. To work with them, you have to copy them locally on your machine. For that, you have first to create what we name a ssh keypair, which is used as an authentication token to load and store the files in your repository. Technically, a ssh keypair contains a public and a private key. You give the public key to someone (in our case GitLab), and you use the private key to generate an authentication token. Since only the owner of the private key can create a token that matches the public key, anyone can verify that you are actually the owner of a public key, which authenticates you.

To create this keypair, you have to use the `ssh-keygen` tool. Then you have to display the public key and to record it in GitLab. For that, you have to launch a terminal (by launching the terminal application for the Mac users, or by starting WSL for the Windows user). In the terminal, type the following commands:

```
ssh-keygen -t rsa
```

When `ssh-keygen` asks you questions, just press enter.

Once the key is generated, type:
```
cat ~/.ssh/id_rsa.pub
```

At this step, you should see your public key in the terminal. Through the GitLab web interface, click on your profile, then preferences, then SSH Keys and then add new key. In the Key field, copy paste copy-paste the public key that you see in the terminal, and then click on "Add key".

> **Remarque:** You only have to create the keys once. You should not need to create them again for the rest of the course.

> ⚠️  **If you use the binet GitHub instead of the binet GitLab, click on your profile (top right corner), "Settings", "SSH and PGP keys", "New SSH key", and add your public key in the same way.**

## Question 5: Configuring you user name and password

With git, when you write code, other developers must be able to identify you. To do this, type:

```
git config --global user.name "Your name"
```
```
git config --global user.email "your.email@example.com"
```

## Question 6: Creating a local clone

Now that you have the `csc_2f001_ep` repository hosted on GitLab, we will connect your local `csc_2f001_ep` to this project.

Under the hood, `git` works by considering repositories, and by connecting them. Technically, a repository is a normal directory enriched with meta-data that, at a high level, contains the full history of modifications you brought to your project. Additionally, a repository may have what we call an `origin`. The `origin` of a repository is a kind of master copy. To work locally, you thus need a local repository configured so that it uses the repository hosted on the GitLab server as its origin. Such a local repository is what we call a clone of an origin. You can, of course, have clones of a git repository on different machines, which means that you can end up with an architecture similar to this one:

```
 ------------------------                -------------------------
| repository hosted on |  <-----------  |  repository hosted    |
| on the GitLab server |     origin     | on a lab room machine |
 ------------------------                -------------------------
              ^                                One clone
              | origin
              |
 ------------------------
| repository hosted on |
|    on your laptop    |
 ------------------------
      Another clone
```

We will now turn step by step your local `csc_2f001_ep` directory into a clone of the repository you created on the GitLab server. First, we will turn your local `csc_2f001_ep` directory into a Git repository. To do that, go into your `csc_2f001_ep` directory and verify that everything is ok by typing `ls` (`ls` should output the `lab1` directory you created in the previous exercise). Then, type this command, which turns a directory into a Git repository:

```
git init --initial-branch=main
```

For the second step, you will associate your local repository with the repository hosted on the GitLab server by setting its origin. To do that, get the URL of your repository on the GitLab server by clicking on the `Code` icon. Copy the URL that starts with `git@`, not the one that starts with `https`. Then, in the terminal, in your `csc_2f001_ep` directory, type:

```
git remote add origin [URL that you copied]
```

## Question 7: Adding and committing files

Internally, a Git repository considers two different elements:

* The working tree: this is the directory tree that you see in `csc_2f001_ep`. At the moment, in your working tree, you have a `lab1` subdirectory that contains your `hello.c` file.
* The commits: a commit is an internal snapshot of your files that you can send (we say push) to the origin server, or restore locally if you want to retrieve an older version.

This means that, locally, you have a set of commits (which we call the history) and your working tree, which is not yet committed. For example, as you work, you will end up with a history similar to this one:

```
   commit0 ---------> lab1/hello.c (version 0)
     ^
     |
   commit1 --------> lab1/hello.c (version 1)
                |--> lab2/Makefile (version 0)
                |--> lab2/sierpinski.c (version 0)
     ^
     |
  commit2 --------> lab1/hello.c (version 1)
               |--> lab2/Makefile (version 0)
               |--> lab2/sierpinski.c (version 1)
     ^
     .
     .
working tree -----> lab1/hello.c (version 1 - unmodified)
               |--> lab2/Makefile (version 0 - unmodified)
               |--> lab2/sierpinski.c (version 2 - modified)
```

Here, imagine that you created commits 0, 1, and 2, and then modified the `sierpinski.c` file. In this state, you can, for example, revert your working copy to commit 0, push commit 2 to origin, or create commit 3 from your working directory.

To illustrate, we will create commit 0 from your current version of the `lab1/hello.c` file. To do that, you need to know that, inside your working directory, Git considers different kinds of files:

* Untracked: Git totally ignores the file. Any new file is initially in this state.
* Tracked: Git tracks this file and can include it in a commit:
  * Unmodified: the file has not been modified. In the next commit, the version from the previous commit will be used.
  * Modified: the file has been modified:
    * Staged: the new version will be included in the commit.
    * Unstaged: the new version will be ignored, meaning Git will use the last committed version of the file in the next commit while ignoring the current state in the working directory.

You can see the state of your files at any moment with the following command:

```
git status
```

If you type this command, you will see that the directory `lab1` is untracked: it means that the whole directory and its files are untracked. We will thus tell Git to track the file `lab1/hello.c` (this also marks the `lab1` directory as tracked) with this command:

```
git add lab1/hello.c
```

If you type `git status` again, Git will tell you that `lab1/hello.c` will be committed in the next commit. It should also tell you that `lab1/hello` is untracked. You can thus create your first commit by typing:

```
git commit -a -m "My first commit"
```

The `-a` flag stands for "consider all modified tracked files as staged", and the `-m` flag allows you to add a message describing the modifications you made to your code.

🎉 **Congratulations, you created your first commit!**

## Question 8: The .gitignore file

Adding a generated executable to a commit is not a good idea, as we can always regenerate it from the source files. For this reason, we will never track a generated binary like `csc_2f001_ep/hello`. However, the file appears as untracked when you type `git status`, which can be annoying as it pollutes the output. If you want to hide these files, you can tell Git to totally ignore them by using the `lab1/.gitignore` file in the `csc_2f001_ep` directory. In detail, you have to add the ignored files, each on its own line, to `lab1/.gitignore`:

```
hello
```

`lab1/.gitignore` is itself a file. It is thus a good idea to add it to your repository so that if you clone your project on a different machine you don't lose it. For that, you just have to create a new commit:

```
git add lab1/.gitignore
git commit -a -m "Add lab1/.gitignore file"
```

## Question 9: Seeing the history

You can now see your beautiful commit history with the command:

```
git log
```

You should see your two commits: the one that adds `lab1/hello.c` and the one that adds `lab1/.gitignore`.

## Question 10: Pushing and pulling

If you go to the GitLab server, you will see that your repository is still empty. This is because when you commit to a local repository, it does not propagate the commit to origin. To propagate the commits, you have to use the command:

```
git push
```

Once entered, if you go to the GitLab server, you will see your files. Congratulations, it means that the professors can see your work and grade you. Regularly checking that your work is visible is a good idea to avoid disappointment: if your work is not pushed to GitLab, your professors will think that you did not work...

> ⚠️  **If `git push` fails, type `git push -u origin main` instead.**

## Question 11: Using git in your daily life

Now that everything is set up properly, working with Git is relatively straightforward. During a lab, you will work on your working tree, and then commit and push your work. We will simulate such a process. For that, we will create a new file `Readme.md` in the `csc_2f001_ep` directory with the following content:

```
# Using git in my daily life

To use git:
* `git add .` => recursively marks all the files reachable from the current directory as tracked
* `git commit -a -m "My beautiful commit message"` => create a commit
* `git push` => push the commit to the origin, which makes it visible to my professors
```

And type exactly the code of your Readme in the terminal. Once done, on the GitLab server, you should see the `Readme.md` file. You can also see that the content of this file is displayed directly on the server, which is great to explain users how to install or configure your project.

## Question 12: Cloning, pushing and pulling

In the second part of the course, you will have to work with teammates on a project. To collaborate, you will use git. It means that you will have several clones of your project, and you will have to synchronize them. We will simulate such a process. For that, we will create a second clone of your project. In the terminal, go to your home directory by typing `cd`. Then, copy the URL of the project by clicking on the Code icon on the GitLab server (use the URL that starts with `git`), and type:

```
git clone [URL that you have copied] my-teammate
```

If you explore the directory `my-teammate` with `ls`, you will see a full copy of the last commit.

In `my-teammate`, create a new commit. For that, modify the `Readme.md` file by adding some random content, and type:

```
git commit -a -m "My teammate is working"
git push # push the commit to the server
```

Go into your `csc_2f001_ep` directory. At this step, you do not yet see the modifications of your teammate. To include them in your local repository, you simply have to type:

```
git pull
```

If git asks you how you want to handle potential conflicts, use the `rebase` method.

You can check that you now see the modifications of your teammate.

## Question 13: Handling conflicts

While you work with your teammates, you will face conflicts. A conflict appears when two repositories diverge: one contains a commit that is not yet included in the other, and the other repository has also been modified (either only the working tree, or because it contains other commits).

We will simulate such a conflict. For that:

* In the `my-teammate` directory, edit `Readme.md` and remove your random content, then commit and push your modifications
* In the `csc_2f001_ep` directory, edit `lab1/hello.c` to print `Git is easy!` instead of `Hello, world!!!`. Compile and execute your new hello program. Commit your modifications, but without pushing them
* In the `csc_2f001_ep` directory, modify `lab1/hello.c` a second time to print `Git is easy! Heu.... maybe not so much?`. Do not commit, push, or pull anything.

At this step, we have two conflicting repositories.

```
GitLab server <- commit0 <--- commit1 <--- commit2
                                |            |
                                |            |-> Readme.md without the random content
                                |
                                |-> Readme.md with the random content
                                |
                                |            |-> hello.c with Git is easy
                                |            |
csc_2f001_ep <-- commit0 <--- commit1 <--- commit3 <.... working tree
                                                              |
                                                              |-> hello.c with maybe not so much
```

Here, the history of the repository located on the server and on your laptop matches up to commit1, but then totally diverges. If you type `git pull` in your `csc_2f001_ep`, git will first refuse because of the modifications in your working tree, which have not been committed and may be overridden if you pull the history from the server. To solve this problem, we will remove the problem of the pending modifications in the working tree from the equation. For that, you have to type:

```
git stash
```

This command "hides" your local changes. Technically, it sets them aside so that you can apply them later once the other conflicts are resolved. It means that now, you have two different commit histories that conflict, but at least, your working tree is clean, which makes the conflict easier to solve.

To solve the history conflict, you just have to type:

```
git pull
```

If git asks you how you want to handle the conflict, select the `rebase` method.

Under the hood, what git did is that it:

* canceled commit3 to revert to commit1 in your local repository (the history is commit0 <- commit1)
* pulled commit2 (the history is commit0 <- commit1 <- commit2)
* reapplied the modifications of commit3 on top of commit2, and then re-committed commit3 (the history is commit0 <- commit1 <- commit2 <- commit3)

Here, we are lucky: git solves the conflicts on a line-by-line basis, and since commit2 and commit3 modified different lines (in different files), git is able to merge the commits automatically. It may happen that you and your teammate modified the exact same line. In this case, you will have a message from git saying that you have to solve the conflict manually before continuing. At a high level, you have to:

* Edit the file where you have a conflict that git cannot solve, and find the lines that start with `<<<`. Here you can see both your version and the one pulled from origin. You have to remove the `<<<` lines, and select one of the versions (or adapt the content)
* Type `git add the-file-in-conflict` and commit with `git commit -a -m "Merge conflict"`,
* Continue to merge the conflict with `git pull --continue`.

At this step, the conflict between the histories is solved, but your local modification to print "not so easy" is not yet reintegrated. You can reintegrate it by typing:

```
git stash apply
```

This command will re-apply your stashed modifications to your local tree. If git is unable to merge the stashed modifications, it will add lines that start with `<<<` to your file, and as in the case of a merge issue during a `git pull`, you will have to manually merge the conflict.

At this time, your life is beautiful again, all the conflicts are merged, and you have this clean history:

```
GitLab server <- ... <--- commit2
                             |
                             |-> Readme.md without the random content
                             |
                             |            |-> hello.c with git is easy
                             |            |
csc_2f001_ep <-- ... <--- commit2 <--- commit3 <.... working tree
                                                         |
                                                         |-> hello.c with maybe not so much
```

Since the history prefix on the GitLab server and in your clone matches, you can commit your last modifications, and push your work so that commits 2 and 3 become visible to your teammates.

🎉 **Congratulations, you are now a git power user! You can find the important git command studied in this exercise [here](../resources/git.md).**
