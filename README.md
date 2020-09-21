# Five in A Row

This project provides a UI for [five-in-a-row](https://en.wikipedia.org/wiki/Gomoku) games. 

Players can either play against each other or challenge a built-in AI. Matches can be saved and replayed later.

## Installation

This project works on MacOS. 

Install [Xcode](https://developer.apple.com/xcode/) and [openframeworks](https://openframeworks.cc). Download this project in Zip, open the Project Generator, and import "fantastic-finale" folder. Then you can open the project in Xcode. Run the fantastic-finale Release scheme in Xcode and you could see the UI as follows.

![alt text](https://github.com/CS126FA19/fantastic-finale-leoyang429/blob/master/fantastic-finale/bin/data/Screen%20Shot%202019-12-11%20at%203.00.10%20PM.png)

## Usage

The game is automatically set at play mode upon entering - that is, two human players play agianst each other. Click on the intersects to make a move.

Click the buttons to switch between modes.

Functions of Buttons:
 - Restart - reset the board, and quit AI mode
 - Undo - undo the last move
 - Save - save the current match by specifying a name for this match
 - Replay - search a saved game by its date and name, and then enter replay mode for this game
 - AI - play against AI, can choose play first or not
 - Exit - exit the game
 - Show Matches - list all the dates and names of recorded matches

For replay mode, click anywhere on the board to see the next move. You may also press space for the next move and backspace for previous move in replay mode.
