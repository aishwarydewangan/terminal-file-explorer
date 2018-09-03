# Terminal File Explorer

A simple terminal based file explorer having capabalities such as create file/directory, copy file/directory, move file/directory, delete file/directory, etc..

**Run this application on MacOS only.**

### Assumptions
* **Absolute Path** is used in the project.
* To exit from the application, press **q** when in **Normal Mode**.
* Terminal Size: 28x100 or Fullscreen
* Delete takes multiple arguments. (It was not mentioned in the assignment description)
* Status shows status of lastest executed command.
* File Name/Directory Name should not have any spaces between them.

### Compile and Execute

There is a *makefile* included in the project. Following commands compiles and generates binary:

```sh
$ make
$ ./explorer <absolute_path>
```

### Commands

Following is the list of commands implemented as well as its syntax. The syntax of most of the command(s) is taken directly from assignment pdf file.

| Command | Syntax |
| ------ | ------ |
| create_file | create_file <file_name> <destination_path> |
| create_file | create_dir <dir_name> <destination_path> |
| copy | copy <source(s)> <destination_directory> |
| move | move <source(s)> <destination_directory> |
| rename | rename <old_filename> <new_filename> |
| delete | delete <source(s)> <destination_directory> |
| snapshot | snapshot <folder> <dumpfile> |

### Developed By
Aishwary Dewangan <br/>
M.Tech. CSIS <br/>
Roll No.: **2018202016** <br/>
GitLab Handle: **aish_2018202016** <br/>

### Credits
Thank you all TA's @ OS. :)