# Tetris

Installation

To install simply run
```
$ git clone https://github.com/its007Kevin/tetris.git
```
Unlike regular tetris, this version can be played through the command line.

## Commands 
```
left: moves the current block one cell to the left. If this is not possible (left edge of the board,
or block in the way), the command has no effect.

right: same as above, but to the right.

down: same as above, but one cell downward.

clockwise: rotates the block 90 degrees clockwise, as described earlier. If the rotation cannot
be accomplished without coming into contact with existing blocks, the command has no effect.
counterclockwise as above, but counterclockwise.

drop: drops the current block. It is (in one step) moved downward as far as possible until
it comes into contact with either the bottom of the board or a block. This command also
triggers the next block to appear.

levelup: Increases the difficulty level of the game by one. The block showing as next still
comes next, but subsequent blocks are generated using the new level. If there is no higher
level, this command has no effect.

leveldown: Decreases the difficulty level of the game by one. The block showing as next still
comes next, but subsequent blocks are generated using the new level. If there is no lower
level, this command has no effect.

norandom file: Relevant only during levels 3 and 4, this command makes these levels non-
random, instead taking input from the sequence file, starting from the beginning. This is
to facilitate testing.

random: Relevant only during levels 3 and 4, this command restores randomness in these levels.
sequence file Executes the sequence of commands found in file. This is to facilitate the
construction of test cases.

I, J, L, etc. Useful during testing, these commands replace the current undropped block with
the stated block. Heaviness is detemined by the level number. Note that, for heavy blocks,
these commands do not cause a downward move.

restart: Clears the board and starts a new game.
```
## Command-line interface

In addition, our game also supports commands passed to the game as arguments before the game is ran.
```
-text: runs the program in text (ascii) only mode

-seed <seed>: sets the random number generators' seed

-scriptfile <file>: uses <file> as the source of blocks for level 0.

-startlevel <level>: Starts the game on <level>, otherwise the game defaults to level 0.

-enablebonus: Enables the hold block feature
```
Example usage
```
./quadris -startlevel 2 -enablebonus
```

