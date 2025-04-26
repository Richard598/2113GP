#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include<map>
#include <random>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>
#include<algorithm>

using namespace std;

/** Coordinate structure, representing row and column coordinates of a block relative to its shape origin */
struct Point {
    int r;
    int c;
};

/** Enumeration representing the seven types of Tetrominoes */
enum TetrominoType { I = 0, J, L, O, S, T, Z };

/** 
 * Define the rotation forms of each Tetromino.
 * Use an array of 7 elements, each element has 4 rotation states, each state consists of 4 Point coordinates.
 * Coordinates are relative to the top-left origin of the block shape.
 */
static const array<array<array<Point,4>,4>, 7> TetrominoShapes = {{
    // I block (long bar)
    {{
        // Rotation state 0: horizontal
        {{{0,0}, {0,1}, {0,2}, {0,3}}}, 
        // State 1: vertical
        {{{0,0}, {1,0}, {2,0}, {3,0}}}, 
        // State 2: horizontal (same as state 0)
        {{{0,0}, {0,1}, {0,2}, {0,3}}}, 
        // State 3: vertical (same as state 1)
        {{{0,0}, {1,0}, {2,0}, {3,0}}}
    }},
    // J block (J-shaped)
    {{
        // State 0: vertical, bottom extends one cell to the left
        {{{0,1}, {1,1}, {2,1}, {2,0}}}, 
        // State 1: horizontal, top extends one cell to the left
        {{{0,0}, {1,0}, {1,1}, {1,2}}}, 
        // State 2: vertical, top extends one cell to the right
        {{{0,0}, {0,1}, {1,0}, {2,0}}}, 
        // State 3: horizontal, bottom extends one cell to the right
        {{{0,0}, {0,1}, {0,2}, {1,2}}}
    }},
    // L block (L-shaped)
    {{
        // State 0: vertical, bottom extends one cell to the right
        {{{0,0}, {1,0}, {2,0}, {2,1}}}, 
        // State 1: horizontal, top extends one cell to the right
        {{{0,2}, {1,0}, {1,1}, {1,2}}}, 
        // State 2: vertical, top extends one cell to the left
        {{{0,0}, {0,1}, {1,1}, {2,1}}}, 
        // State 3: horizontal, bottom extends one cell to the left
        {{{0,0}, {0,1}, {0,2}, {1,0}}}
    }},
    // O block (square)
    {{
        // All rotation states are the same (2x2 square)
        {{{0,0}, {0,1}, {1,0}, {1,1}}}, 
        {{{0,0}, {0,1}, {1,0}, {1,1}}}, 
        {{{0,0}, {0,1}, {1,0}, {1,1}}}, 
        {{{0,0}, {0,1}, {1,0}, {1,1}}}
    }},
    // S block (S-shaped)
    {{
        // State 0: horizontal (shape is S with diagonal from bottom-left to top-right)
        {{{0,1}, {0,2}, {1,0}, {1,1}}}, 
        // State 1: vertical
        {{{0,0}, {1,0}, {1,1}, {2,1}}}, 
        // State 2: horizontal (rotated 180°, actually similar to Z's horizontal)
        {{{0,0}, {0,1}, {1,1}, {1,2}}}, 
        // State 3: vertical (rotated 270°, shape similar to Z's vertical)
        {{{0,1}, {1,0}, {1,1}, {2,0}}}
    }},
    // T block (T-shaped)
    {{
        // State 0: T facing up (protrusion at the top)
        {{{0,1}, {1,0}, {1,1}, {1,2}}}, 
        // State 1: T facing right
        {{{0,0}, {1,0}, {2,0}, {1,1}}}, 
        // State 2: T facing down
        {{{0,0}, {0,1}, {0,2}, {1,1}}}, 
        // State 3: T facing left
        {{{0,1}, {1,0}, {2,1}, {1,1}}}
    }},
    // Z block (Z-shaped)
    {{
        // State 0: horizontal (shape is Z with diagonal from top-left to bottom-right)
        {{{0,0}, {0,1}, {1,1}, {1,2}}}, 
        // State 1: vertical
        {{{0,1}, {1,0}, {1,1}, {2,0}}}, 
        // State 2: horizontal (rotated 180°, actually similar to S's horizontal)
        {{{0,1}, {0,2}, {1,0}, {1,1}}}, 
        // State 3: vertical (rotated 270°, shape similar to S's vertical)
        {{{0,0}, {1,0}, {1,1}, {2,1}}}
    }}
}};
