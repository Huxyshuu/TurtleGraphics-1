# Turtle Graphics

This project implements a Turtle Graphics simulation using the Qt framework. Turtle Graphics allows users to create visual patterns and designs by controlling a "turtle" that moves around the screen, leaving a trail as it goes. This application lets users command the turtle to move forward, turn, and change colors to hopefully create complex and dynamic graphics.

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

# Group
- Hugo Tamm
- Mathias Castrén
- Xiwei Zhao
- Giang Le

# Repository organization
The file structure will be as follows:
```
📦 Turtle-1
 ├─ 📂 doc
 ├─ 📂 libs
 ├─ 📂 plan
 ├─ 📂 src
 │  ├─ 📄 main.cpp
 │  ├─ 📄 mainwindow.cpp
 │  ├─ 📄 mainwindow.h
 │  └─ 📄 readme.md
 ├─ 📂 tests
 ├─ 📂 ui
 │ ...
 ├─ 📄 CMakeLists.txt
 ├─ 📄 README.md
...
```
Your project implementation should follow the skelaton organization in this repository.
See readme.md files in each folder.

# Project Implementation 
You must use git repository for the work on the project, making frequent enough commits so 
that the project group (and course staff) can follow the progress.

The completed project work will be demonstrated to the group's advisor at a demo session. 
The final demonstrations are arranged on week 50. After the final demonstrations project group 
evaluates another project, and self-evaluates own project. In addition, project members will 
give a confidential individual assessment of each group member

The course staff should be able to easily compile the project work using makefile and related 
instructions provided in the git repository. The final output should be in the **master branch** of the git repository.

# Working practices
Each project group is assigned an advisor from the project teaching personnel. 
There will be a dedicated Teams channel for each project topic to facilitate discussion between 
the groups in the same topic and the advisor. 

**The group should meet weekly.** The weekly meeting does not need to be long if there are no special issues 
to discuss, and can be taken remotely as voice/video chat on the group Teams channel (or Zoom or other similar tool), 
preferably at a regular weekly time. In the meeting the group updates:

- What each member has done during the week
- Are there challenges or problems? Discuss the possible solutions
- Plan for the next week for everyone
- Deviations and changes to the project plan, if any
- After the meetings, the meeting notes will be committed to the project repository in the `Meeting-notes.md` file. 
    * The commits within the week should have some commit messages referring to the meeting notes so 
      that the project advisor can follow the progress.  
    * **The meeting notes should be in English.**

> Everyone may not be able to participate to all meetings, but at least a couple of members should be present in each meeting. 
> Regular absence from meetings will affect in individual evaluation.

# Source code documentation
It is strongly recommended to use Doxygen to document your source code.
Please go over the *Project Guidelines* for details.

# TODOs (Date)
You can create a list of TODOs in this file.
The recommended format is:
- Saving function aka write to a file
- Downloadable picture of the map
- Change line color and width
- Sound (work in progress)
- Border limit
- Probably a lot of other cool stuff 