#pragma once

#include"block.h"
#include"art.h"
#include"terminal.h"

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
#include<fstream>

using namespace std;

extern ifstream fin;
extern ofstream fout;

enum DifficultyLevel { EASY = 0, MEDIUM, HARD, EXPERT };

class TetrisGame {
    public:
        int width;                          
        int height;                         
        vector<vector<char> > board;       
        TetrominoType currentType;          
        TetrominoType nextType;             
        int currentRotation;                
        int nextRotation;                   
        int currentRow, currentCol;         
        int score,bestscore=0;                         
        bool gameOver;                      
        struct termios origTermios;         
        bool isClearingAnimation = false;      
        int animationFrame = 0;                
        vector<int> linesToClear;              
        const int TOTAL_ANIMATION_FRAMES = 5; 
        DifficultyLevel difficulty;          
        int dropInterval;

        TetrisGame(int w=10, int h=20);

        void showStartScreen();
        DifficultyLevel selectDifficulty();
        void spawnPiece();
        bool checkCollision(TetrominoType type, int rotation, int row, int col);
        bool movePiece(int dr, int dc);
        bool rotatePiece();
        void lockPiece();
        void clearLines();
        void playClearAnimation();
        void performLineClear();
        void draw();
        void run();
        void showGameOverScreen();
        void resetGame();
        void lockCurrentAndSpawn();
};
