# Planned Features and Tasks

Below are the current planned features, user stories, and task backlog for the project.

Legend:

* F: Feature
* U: User story
* T: Task

## Features

* F1. 2D ASCII graphics system
  * U1
* F2. Keyboard input system
  * U4, U2
* F3. Random number generator
  * U5
* F4. Menu system
  * U2
* F5. Scoring system
  * U3, U2
* F6. Bootloader game to utilize features F1-F5
  * U1, U2, U3, U4, U5, U6

## User Stories

* U1. As a game developer I want to be able to display simple graphics so that I
can make games.
  * T10 Ability to update individual cursor positions with a new character or color
    * T10.1 Functionality to change cursor position
    * T10.2 Functionality to change symbol at the cursor
    * T10.3 Functionality to change foreground and background color at the cursor
* U2. As a UI developer I want to be able to create simple button menus so that
my users have a simple and clear interface.
  * T20 Ability to create buttons that are selectable with keyboard controls
    * T20.1 Functionality to use keyboard input to interact with menus.
    * T20.2 Functionality to define ordering of buttons to navigate between the
    previous or next buttons.
    * T20.3 Functionality to activate an event from a button press.
    * T20.4 Functionality to display buttons at a specific screen position.
* U3. As a game developer I want to be able to display scores to my users so they
can get feedback on their performance.
  * T30 Ability to store and display a score to the user.
    * T30.1 Functionality to store and update the user's score.
    * T30.2 Functionality to display the score to the user.
    * T30.3 Functionality to reset the score.
* U4. As a game developer I want to be able to handle user keyboard input so they
can control aspects of my game.
  * T40 Ability to capture keyboard input from the user.
    * T40.1 Investigate how keyboard input can be gathered from the system.
    * T40.2 Functionality to track key presses and releases.
    * T40.3 Functionality to activate system events from keyboard input.
* U5. As a game developer I want to be able to generate a unique experience for
each player so that my games are not boring.
  * T50 Create a random number generator.
    * T50.1 Determine a good random seed candidate.
    * T50.2 Functionality to generate pseudo-random numbers from the seed.
    * T50.3 Functionality to specify range of values for the random numbers.
* U6. As a videogame player I want to play snake so that I can have fun.
  * T60 Implement the game Snake using the developed libraries.
    * T60.1 Functionality for updating the position and shape of the snake model.
    * T60.2 Determine the scoring metrics to be used.
    * T60.3 Implement collision detection for snake-food and snake-snake interactions.
    * T60.4 Implement the snake growing and the user's score increasing when the
    snake eats food.
    * T60.5 Implement a lose condition when the snake bites itself.
    * T60.6 Implement player controls for the snake.
    * T60.7 Implement a simple menu to start a new game.
    * T60.8 Implement a score display so the user can see their performance.
  * T61 Investigate how to do header linking for the bootloader compilation.
