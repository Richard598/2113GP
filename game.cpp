#include"game.h"

void TetrisGame::showStartScreen() {
    while(true) {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
        // Clear screen and center display
        cout<<"\033[H\033[J";
        for(int i=0;i<TETRIS_ART.size();i++) {
            cout << "\033[" << (w.ws_row/2-3+i) << ";" 
                << (w.ws_col - TETRIS_ART[0].length()/3)/2 << "H"  
                << TETRIS_ART[i] << endl;
        }
        // Display prompt text
        cout<<endl;
        cout << "\033[" 
            << (w.ws_col - PRESS_START.size())/2 << "G" 
            << PRESS_START << flush;
    
        // Wait for space key
    
        char ch;
        if(read(STDIN_FILENO, &ch, 1) > 0) {
            if(ch == ' ') break;
        }
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

//Display difficulty selection interface and return selected difficulty 
DifficultyLevel TetrisGame::selectDifficulty() {
    // Difficulty options
    vector<string> difficultyOptions = {
        "Easy",
        "Medium",
        "Hard",
        "Expert"
    };
    
    // Difficulty descriptions
    vector<string> difficultyDescriptions = {
        "Suitable for beginners, blocks fall slowly",
        "Standard difficulty, balanced gameplay",
        "Challenge mode, blocks fall faster",
        "Extreme difficulty, blocks fall very fast"
    };
    
    
    int selectedOption = 0;
    bool selectionConfirmed = false;
    
    
    // Function to draw the interface
    auto drawInterface = [&]() {
        // Get current terminal size
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        
        // Clear screen
        cout << "\033[H\033[J";
        
        // Calculate center position
        int boxWidth = 60;
        int boxHeight = 12;
        int startRow = (w.ws_row - boxHeight) / 2;
        int startCol = (w.ws_col - boxWidth) / 2;
        
        // Ensure position is valid
        startRow = max(1, startRow);
        startCol = max(1, startCol);
        
        // Display title
        cout << "\033[" << startRow << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "╔════════════════════════════════════════════════════════════════╗\033[0m" << endl;
        cout << "\033[" << (startRow+1) << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "║\033[0m" << titleColor << "     Select Difficulty - Use ↑/↓ to choose, Enter to confirm\033[0m\033[1m" << borderColor << "    ║\033[0m" << endl;
        cout << "\033[" << (startRow+2) << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "╠════════════════════════════════════════════════════════════════╣\033[0m" << endl;
        
        // Display options
        for (int i = 0; i < difficultyOptions.size(); i++) {
            cout << "\033[" << (startRow+3+i) << ";" << startCol << "H";
            cout << "\033[1m" << borderColor << "║\033[0m  ";
            
            if (i == selectedOption) {
                cout << "\033[1m" << difficultyColors[i] << "▶ " << difficultyOptions[i] << "\033[0m";
                // Display description
                cout << "\033[" << (startRow+8) << ";" << startCol << "H";
                cout << "\033[1m" << borderColor << "║\033[0m  " << descriptionColor << difficultyDescriptions[i] << "\033[0m";
            } else {
                cout << "  " << difficultyColors[i] << difficultyOptions[i] << "\033[0m";
            }
            
            cout << "\033[" << (startRow+3+i) << ";" << (startCol+boxWidth+5) << "H";
            cout << "\033[1m" << borderColor << "║\033[0m";
        }
        
        // Display bottom border
        cout << "\033[" << (startRow+7) << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "╠════════════════════════════════════════════════════════════════╣\033[0m" << endl;
        cout << "\033[" << (startRow+9) << ";" << startCol<< "H" ;
        cout << "\033[1m" << borderColor << "╚════════════════════════════════════════════════════════════════╝\033[0m" << endl;
        cout<<"\033[" << (startRow+8) << ";" << startCol+boxWidth+5 << "H"<<borderColor<<"\033[1m║\033[0m";
        
        // Display control instructions
        cout << "\033[" << (startRow+11) << ";" << startCol << "H";
        cout << instructionColor << "Use ↑/↓ to select difficulty, press Enter to confirm\033[0m" << endl;
        
        cout.flush();
    };
    
    // Initial draw
    drawInterface();
    
    // Main loop
    while (!selectionConfirmed) {
        // Handle user input
        char ch;
        if (read(STDIN_FILENO, &ch, 1) > 0) {
            if (ch == '\033') {
                // Might be arrow keys
                char seq[2];
                if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1) {
                    if (seq[0] == '[') {
                        switch(seq[1]) {
                            case 'A': // ↑
                                selectedOption = (selectedOption - 1 + difficultyOptions.size()) % difficultyOptions.size();
                                drawInterface(); // Redraw immediately to update selection
                                break;
                            case 'B': // ↓
                                selectedOption = (selectedOption + 1) % difficultyOptions.size();
                                drawInterface(); // Redraw immediately to update selection
                                break;
                        }
                    }
                }
            } else if (ch == '\n') {
                // Enter key confirms selection
                selectionConfirmed = true;
            }
        }
        
        // Check for terminal size changes
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        static struct winsize lastW = w;
        
        if (w.ws_row != lastW.ws_row || w.ws_col != lastW.ws_col) {
            lastW = w;
            drawInterface();
        }
        
        // Short sleep to reduce CPU usage
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    
    
    // Get current terminal size for confirmation screen
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int boxWidth = 60;
    int startRow = (w.ws_row - 4) / 2;
    int startCol = (w.ws_col - boxWidth) / 2;
    
    // Ensure position is valid
    startRow = max(1, startRow);
    startCol = max(1, startCol);
    
    // Display selection confirmation animation
    cout << "\033[H\033[J";
    cout << "\033[" << startRow << ";" << startCol << "H";
    cout << "\033[1m" << borderColor << "╔════════════════════════════════════════════════════════════════╗\033[0m" << endl;
    cout << "\033[" << (startRow+1) << ";" << startCol << "H";
    cout << "\033[1m" << borderColor << "║\033[0m" << titleColor << "            Selected: " << difficultyColors[selectedOption] << difficultyOptions[selectedOption] << "\033["<<startCol+65<<"G"<<"\033[0m\033[1m" << borderColor << "║\033[0m" << endl;
    cout << "\033[" << (startRow+2) << ";" << startCol << "H";
    cout << "\033[1m" << borderColor << "╚════════════════════════════════════════════════════════════════╝\033[0m" << endl;
    
    // Short delay before starting the game
    this_thread::sleep_for(chrono::milliseconds(800));
    
    // Return selected difficulty
    return static_cast<DifficultyLevel>(selectedOption);
}

TetrisGame::TetrisGame(int w,int h) : width(w), height(h), board(h, vector<char>(w, ' ')),
                                    currentType(I), nextType(I), currentRotation(0), nextRotation(0),
                                    currentRow(0), currentCol(0),
                                    score(0), gameOver(false),
                                    difficulty(MEDIUM), dropInterval(500) {}



//Generate a new block at the top of the game board
void TetrisGame::spawnPiece() {
    // If it's the first time generating a block, generate both current and next blocks
    if (currentType == I && currentRotation == 0 && currentRow == 0 && currentCol == 0) {
        // Randomly generate current block type
        static std::mt19937 gen((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(0, 6);
        currentType = static_cast<TetrominoType>(dist(gen));
        currentRotation = 0;
        
        // Randomly generate next block type
        nextType = static_cast<TetrominoType>(dist(gen));
        nextRotation = 0;
    } else {
        // Use next block as current block
        currentType = nextType;
        currentRotation = nextRotation;
        
        // Randomly generate new next block
        static std::mt19937 gen((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(0, 6);
        nextType = static_cast<TetrominoType>(dist(gen));
        nextRotation = 0;
    }
    
    // Set the starting position of the new block at the top center
    // Calculate the width of the block shape in its initial rotation state for horizontal centering
    int shapeMinCol = INT32_MAX, shapeMaxCol = INT32_MIN;
    for (size_t i = 0; i < TetrominoShapes[currentType][currentRotation].size(); ++i) {
        const Point &p = TetrominoShapes[currentType][currentRotation][i];
        if (p.c < shapeMinCol) shapeMinCol = p.c;
        if (p.c > shapeMaxCol) shapeMaxCol = p.c;
    }
    int shapeWidth = shapeMaxCol - shapeMinCol + 1;
    currentRow = 0;
    currentCol = (width - shapeWidth) / 2;
    // Check if the new block immediately conflicts with existing blocks
    if (checkCollision(currentType, currentRotation, currentRow, currentCol)) {
        gameOver = true;
    }
}

//Check if the given block type, rotation state, and position conflicts with boundaries or already placed blocks
bool TetrisGame::checkCollision(TetrominoType type, int rotation, int row, int col) {
    for (size_t i = 0; i < TetrominoShapes[type][rotation].size(); ++i) {
        const Point &p = TetrominoShapes[type][rotation][i];
        int boardR = row + p.r;
        int boardC = col + p.c;
        // Check boundaries
        if (boardR < 0 || boardR >= height || boardC < 0 || boardC >= width) {
            return true;
        }
        // Check if the position already has a block
        if (board[boardR][boardC] != ' ') {
            return true;
        }
    }
    return false;
}

// Try to move the current block, dr: row displacement, dc: column displacement. Returns true if successful, false if failed. 
bool TetrisGame::movePiece(int dr, int dc) {
    int newRow = currentRow + dr;
    int newCol = currentCol + dc;
    if (!checkCollision(currentType, currentRotation, newRow, newCol)) {
        currentRow = newRow;
        currentCol = newCol;
        return true;
    }
    return false;
}
