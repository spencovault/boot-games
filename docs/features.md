# Planned Features and Tasks

Below are the current planned features, user stories, and task backlog for the project.

Legend:

* F: Feature
* U: User story
* T: Task
* P: Points

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
  * T10 (5P) Ability to update individual cursor positions with a new character
  or color.
    * T10.1 (2P) Functionality to change cursor position.
    * T10.2 (1P) Functionality to change symbol at the cursor.
    * T10.3 (2P) Functionality to change foreground and background color at the cursor.
  * T11 (3P) Ability to easily draw different shapes
    * T11.1 (1P) Functionality to draw a filled rectangle.
    * T11.2 (1P) Functionality to draw a line
    * T11.3 (1P) Functionality to draw a bordered rectangle.
* U2. As a UI developer I want to be able to create simple menus so that my
users have a simple and clear interface.
  * T20 (16P) Ability to create buttons and labels that are selectable with
  keyboard controls
    * T20.1 (6P) Functionality to use keyboard input to interact with menus.
    * T20.2 (2P) Functionality to define ordering of buttons to navigate between
    the previous or next buttons.
    * T20.3 (3P) Functionality to activate an event from a button press.
    * T20.4 (5P) Functionality to display buttons at a specific screen position.
* U3. As a game developer I want to be able to display scores to my users so they
can get feedback on their performance.
  * T30 (7P) Ability to store and display a score to the user.
    * T30.1 (2P) Functionality to store and update the user's score.
    * T30.2 (3P) Functionality to display the score to the user.
    * T30.3 (2P) Functionality to reset the score.
* U4. As a game developer I want to be able to handle user keyboard input so they
can control aspects of my game.
  * T40 (10P) Ability to capture keyboard input from the user.
    * T40.1 (5P) Investigate how keyboard input can be gathered from the system.
    * T40.2 (2P) Functionality to track key presses and releases.
    * T40.3 (3P) Functionality to activate system events from keyboard input.
* U5. As a game developer I want to be able to generate unique experiences so
that my games are not boring.
  * T50 (4P) Create a random number generator.
    * T50.1 (2P) Determine a good random seed candidate.
    * T50.2 (1P) Functionality to generate pseudo-random numbers from the seed.
    * T50.3 (1P) Functionality to specify range of values for the random numbers.
* U6. As a videogame player I want to play snake so that I can have fun.
  * T60 (23P) Implement the game Snake using the developed libraries.
    * T60.1 (4P) Functionality for updating the position and shape of the snake model.
    * T60.2 (2P) Determine the scoring metrics to be used.
    * T60.3 (3P) Implement collision detection for snake-food and snake-snake interactions.
    * T60.4 (3P) Implement the snake growing and the user's score increasing
    when the snake eats food.
    * T60.5 (3P) Implement a lose condition when the snake bites itself.
    * T60.6 (4P) Implement player controls for the snake.
    * T60.7 (2P) Implement a simple menu to start a new game.
    * T60.8 (2P) Implement a score display so the user can see their performance.
  * T61 (3P) Investigate how to do header linking for the bootloader compilation.
  * T62 (4P) Investigate how to use a binary larger than 512B.
