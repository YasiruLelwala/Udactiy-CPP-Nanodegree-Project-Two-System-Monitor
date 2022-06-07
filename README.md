# CppND-System-Monitor

## Overview

In this project, I built a process manager for the Linux operating system that roughly resembles the program, **htop** (a standard program for monitoring Linux systems).

Linux stores the processes running on the system in lots of different files. 

The project required reading from these files, structuring the data, processing it, and then formatting it for output to the terminal. As such, this program required many different classes to handle different types of data, and different tasks.

![System Monitor](images/monitor.png)

## Project structure

The project starts with a **main() function**. 

1. A **System object** is instantiated. This object represents the **underlying Linux operating system** and is composed of a few other objects:
    1. A **container of Thread objects.** 
    2. A **Processor object.** 
2. The **System object,** the **Thread objects,** the **Processor object;** all of these objects call **functions** that exist in the **LinuxParser namespace.** 
    1. These **functions** essentially **parse data** from the **Linux file system** (in the **proc** directory) ****that provide information about the status of all these different objects. 
3. The **main() function** can parse the created **System object** to the **NCursesDisplay namespace** which takes the **System object** and displays it out to the screen.



## Instructions

1. Clone the project repository: `git clone https://github.com/udacity/CppND-System-Monitor-Project-Updated.git`

2. Build the project: `make build`

3. Run the resulting executable: `./build/monitor`
![Starting System Monitor](images/starting_monitor.png)

### Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts



