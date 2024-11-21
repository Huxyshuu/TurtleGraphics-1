# Meeting Notes
In this file, you are required to take notes for your weekly meetings. 
In each meeting, you are required to discuss:

1. What each member has done during the week?
2. Are there challenges or problems? Discuss the possible solutions
3. Plan for the next week for everyone
4. Deviations and changes to the project plan, if any


## Week 47 - Meeting 21.11.2024 15:00

**Participants**: 
1. Hugo Tamm
2. Xiwei Zhao
3. Giang Le
4. Mathias Castrén 

## Summary of works

1. Basic of the project/program have been completed
2. Turtle can turn and move on user input
3. Turtle displays trajectory
4. Terminal shows history of commands
5. upload a command txt file and run directly
6. Turtle could jump to one required coordinates and move forward smoothly

## Challenges

- struggling with the sound
- Animation crashing the program when typing another command while first one is still running
- Colour changing issues

## Actions

1. Xiwei
   - training the language processor
   - change line color and width
2. Mathias
   - Do unit tests of each class before you integrate it into the project to validate its operation.
   - Make a block in the map where the turle has to go (Gameify the turtle)
3. Giang
   - work on "save file" function
   - design more shapes saved as a txt file: heart, star, circle, rectangular, triangle, house.
4. Hugo
   - Make a queue for commands
   - Get valgrind running 

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 

Perfecting the **advanced** features and implementing additional features.

## TODOs:

- design our language processor using GPT: Xiwei

  - user: I would like to draw a heart

    -> Out: replay("heart_trajectory_history") (if *heart* feature has been recorded before, we could replay the trajectory)

    -> Out: we do not have this feature in history, could you create your own heart right now using some simple command? :) (if we do not have the *heart* history, could offer the help information for the user) 

  - user: I want to move it forward 100

    -> Out: forward 100

  - user: I want to put it at 100,100

    -> Out: go 100 100

  - user: pick up the pen and move the turtle at 100,100

    -> drawing_ = False; go 100 100

  - user: put down the turtle, turn 90 degrees and make it move forward 100

    -> drawing_ = True; turn 90; forward 100

- work on "save file" function: Giang
  
  - the file should be saved as a txt file with command history
- design more shapes saved as a txt file: heart, star, circle, rectangular, triangle, house. Giang
- change line color and width: Xiwei
- Do unit tests of each class
- Gameify the turtle
- Make a queue for commands
- run valgrind on the project 

