# Live-Linux-System-Monitor

This is a Linux System Monitor implemented as part of course project assigned to me by Udacity. 

<img src="images/LiveLinuxMonitor.gif"/>

# Note
The entirity of this project is not my work. The code under tagline `//I implemented : -----------` are the code blocks I have personally implemented. NCurses display and rest of the starter code was provided by Udacity. You are welcome to develop this project on your local linux machine. 
These are the files I have contributed to:
`format.cpp`
`linux_parser.cpp`
`process.cpp`
`processor.cpp`


## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output. Make sure to install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository: `git clone https://github.com/udacity/CppND-System-Monitor-Project-Updated.git`

2. Build the project: `make build`

3. Run the resulting executable: `./build/monitor`
