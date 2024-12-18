<img src="https://i.imgur.com/5iHKjee.png" align="right"
     alt="KokkiKawaii logo" width="304" height="178">

# Turtle Graphics

This project implements a Turtle Graphics simulation using the Qt framework. Turtle Graphics allows users to create visual patterns and designs by controlling a "turtle" that moves around the screen, leaving a trail as it goes. This application lets users command the turtle to move, turn, change color of the trail and play a little game.

## Features
- **Interactive Controls**: Move the turtle with basic commands like forward and turn.
- **GUI Integration**: Built with Qt's `QGraphicsView` or `QGraphicsScene` for smooth, responsive graphics.
- More coming soon in 2025

## Getting Started
1. Clone the repository.
2. Install Qt (5.x or later).
3. Build and run the project using Qt Creator or the command line.

## Example Commands
- **Forward**: Move the turtle forward by a specified number of steps.
- **Turn**: Rotate the turtle a specified angle.
- **Pen Up**: Stop drawing the trail
- **Pen Down**: Continue drawing the trail
- **Color(R,G,B)** Change color of the trail
- **...**

# Group
- Hugo Tamm
- Mathias Castrén
- Xiwei Zhao
- Giang Le

# Repository organization
The file structure will be as follows:
```
📦 TurtleGraphics-1
 ├─ 📂 doc
 ├─ 📂 libs
 ├─ 📂 plan
 ├─ 📂 src
 │  ├─ 📄 main.cpp
 │  ├─ 📄 mainwindow.cpp
 │  ├─ 📄 mainwindow.h
 │  ├─ ...
 │  └─ 📄 readme.md
 ├─ 📂 tests
 ├─ 📂 ui
 │ ...
 ├─ 📄 CMakeLists.txt
 ├─ 📄 README.md
...
```

# Instructions for Building and Using the Software

## How to Compile the Program
Follow these steps to compile the program from the Git repository.

### 1. Clone the Repository
Ensure Git is installed, then run the following commands:

```bash
git clone https://github.com/Huxyshuu/TurtleGraphics-1  
cd TurtleGraphics-1
```

### 2. Install Dependencies
The program requires the **Qt framework** and **CMake**.

#### Qt Framework:
- **Linux:** Run the command:  
  ```bash
  sudo apt install qt6-default
  ```
- **Windows/macOS:** Download and install **Qt Creator** from the [official Qt website](https://www.qt.io).

#### CMake:
- **Linux:** Run the command:  
  ```bash
  sudo apt install cmake
  ```
- **macOS:** Run the command:  
  ```bash
  brew install cmake
  ```
- **Windows:** Download and install CMake from [cmake.org](https://cmake.org).

### 3. Build the Program
Navigate to the project directory and run the following commands:

1. Configure the build process based on the `CMakeLists.txt` file:  
   ```bash
   cmake .
   ```

2. Compile the source files and generate an executable file:  
   ```bash
   make
   ```

### 4. Run the Program
After building, run the program using:  
```bash
./turtle_1
```
