- **11/20/19** Designed the game board
  - Failed to integrate mysqlc++.h because missing dependencies in mysql.h and decided to use plain texts to store matches
  - Integrated ofxButtons and ofxNotifications
  - Drew the board and stones
  - Enabled players to click on the board to make moves
  - Added BGM and click sound
  - Added evaluation of the board (who wins)
  - Still need some decoration

- **11/21/19** Added features to the game
  - Added Restart and Retract buttons
  - Added desktop notification indicating who wins
  - Decorated the board and stone with images
  - Added Save and Replay buttons
  - Added Dialog box for user input of match name
  - Added Replay Feature
  - Enabled Replay by pressing Space
  - Still need to improve the history match selection process (possibly add an index)
  - Still need to break down the code

- **11/25/19** Refactored the code
  - Added Gomoku class to record the board
  - Migrated functions such as adding stones to board to Gomoku class
  - Added Exit Button to exit the game
  - Enabled Catch for Unit Testing
  - Still need to fix other issues brought up on Nov. 21
  - Still need to write unit tests for Gomoku class

- **11/26/19** Developed AI
  - Implemented & Tested Evaluate function for AI
  - Implemented Minimax & Alpha-beta pruning for AI (current thinking depth is 4)
  - Tested AI by playing against it myself
  - Still need unit testing for AI

- **12/4/19** Improved AI
  - Evaluatee the possible moves and sort them first to optimize minimax pruning
  - Reached thinking depth of 6 (can beat myself in many cases)
  - Fixed bugs about saving matches
  - Added "show history matches" feature
