# 2113GP
HKU ENGG1340/COMP2113 group15

# Team Members

- Dong Zhilin: 3036127555  
- Fan Richard Xu: 3036291033  
- Peng Bo: 3036128987  
- Zhou Zheng: 3036127737  

---

# Description of Tetris

Tetris is an iconic puzzle game that has captivated players since its creation in 1984. The objective is simple yet endlessly engaging: arrange falling geometric shapes, known as Tetriminos, to form complete horizontal lines on a grid. As each Tetrimino descends, players must rotate and position them strategically to fit together without gaps. When a line is completed, it clears, making room for more blocks. As the game progresses, the Tetriminos fall faster, demanding quick reflexes and sharp spatial thinking. With its minimalist design, addictive gameplay, and increasing difficulty, Tetris offers a timeless challenge that tests both skill and strategy, appealing to casual players and competitive high-scorers alike.

---

# Implemented Features

### R1: Generation of Random Events
Our game generated random permutation of block cells (different
shapes) in each loop of the game to create more variable game
experience for players; in each loop of the game, a previously noted
block will be created, and a new randomly generated block will be
exhibited to notify the player and help them make their playing
strategy.

### R2: Data Structures for Storing Data
Used vectors of boolean and string variables to generate the game
board and to reset the game board for a new round of game. Used
arrays to store different conditions and shapes of the block
permutations and alternatively stored their rotation status.  

### R3: Dynamic Memory Management
Our code barely used explicit dynamic memory management like using
the pointers or dynamic arrays, but we used many vectors, arrays,
and alike implicit dynamic memory management measures. Also we used
`ifstream` and `ofstream` to input streams from and output streams to files.  

### R4: File Input/Output
We manually extracted the scores of the players and output them into
a file named "score.txt" using the <fstream> library. The file
stores all the previous scores and would not be eliminated after
each run of the game. At the end of each round of game play, the
score (integer variables) stored in the file will be extracted and
print out the best score among the all the previous game plays.

### R5: Program Codes in Multiple Files
score.txt: an empty txt file(before the first compilation and game play)
used to store the data of previous game scores; Used to find the best
score amongst.

art.h: a header file used to declare the functions and initiate some
constant variables concerning the artistic text visual play and color
design in the game process.

terminal.h: a header file used to declare the included SLs and several
functions in the terminal.cpp file.

terminal.cpp: a cpp file whose main function will change the operating
system of the player: Previously users need to press enter to input to
the system; This function will allow the player input by simply pressing
on the buttons and type in their input content. The "pressing enter"
step was omitted to improve player's playing experience and convenience.

game.h: a header file used to declare the included SLs and several
functions in the game.cpp file. The functions include files input and
output. Also, it defined the user class and its public members used in
the main function of the game.

game.cpp: This is the central file that included the main function of
the game. More specifically, it fulfils its function of game board
editing, game play operations, scores counting, the final output to the
player and most importantly, the initiation and termination of the game
function.

block.h: a header file that included the declaration of the block cell
permutations (different shapes) used in the gameplay. It included the
different conditions and shapes of the block permutations and stored
their rotation status in arrays.

main.h: a header file that includes all the SLs that might be used
during the main body of the game.

main.cpp: a cpp file used to run the game.cpp file and initiate the game
for the player.

Makefile: This Makefile automates the compilation, linking, and
execution of a C++ Tetris project using strict C++11 standards
(`-pedantic-errors -std=c++11`). It defines rules to generate object
files (`main.o`, `terminal.o`, `game.o`), link them into an
executable (`main`), run the program (`./main`), and clean up build
artifacts (`*.o`, `main`). The `.PHONY` directive ensures
`clean` and `run` always execute, streamlining the build-test-clean
workflow.

### R6: Multiple Difficulty Levels
- **Easy**: Slow (beginners).  
- **Medium**: Balanced (casual).  
- **Hard**: Fast (challenging).  
- **Expert**: Very fast (experts).  

---

# Non-Standard C/C++ Libraries
N/A

---

# Compilation and Execution
1. Navigate to the project directory.  
2. Run:  
   ```bash
   make
