
# Annoying Viewer

## Description
It's an Image Viewer that is REAL annyoing to use, still it's fun.

## Features
- Image viewer
- Tic tac toe
- Password manager

## Notes

- **Future Enhancements**: I plan to improve the Tic-Tac-Toe bot by implementing more advanced algorithms to solve the game. The goal is to enhance its speed and optimize memory usage.

- **Testing Environment**: This project has been tested on an Ubuntu WSL2 environment with the VcXsrv server. While it runs smoothly in this setup, compatibility with other systems has not been thoroughly tested, so performance may vary, so I would love to know your experience running it.


## Prerequisites

Before you begin, ensure you have the following installed on your machine:

- **Raylib**: A simple and easy-to-use library to enjoy videogames programming.
  - You can download and install Raylib from the [official website](https://www.raylib.com/) or through your package manager:
    ```bash
    # On Ubuntu/Debian
    sudo apt-get install libraylib-dev

    # On macOS (using Homebrew)
    brew install raylib
    ```

- **C++ Compiler**: A compiler that supports C++11 or later (e.g., GCC, Clang, MSVC).
  - On Ubuntu/Debian, you can install GCC with:
    ```bash
    sudo apt-get install build-essential
    ```
  - On macOS, you can install Xcode Command Line Tools:
    ```bash
    xcode-select --install
    ```
  - On Windows, you can use MinGW or install Visual Studio with C++ support.

Once you have these prerequisites installed, you can proceed to the Installation proccess.

## Installation
#### Clone the Repository
To install the project, you will need to clone this repository to your local machine:

```bash
git clone git@github.com:a-marzouk01/annoying-viewer.git
cd annoying-viewer
```

## Usage

### Compiling the Project
To compile the project, navigate to the root directory of the cloned repository and run the following command:

```bash
make
```

This will compile the source code and generate an executable named main.

### Running the Project
After compiling, you can run the project using:

```console
./main <file>
```

### Recompiling the Project
If you need to recompile the project (e.g., after making changes to the code), you can clean the previous build artifacts by running:

```console
make clean
make
```

This will remove the existing compiled files and recompile the project from scratch.

