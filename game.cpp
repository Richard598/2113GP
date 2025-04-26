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

// Try to rotate the current block (90 degrees clockwise), returns true if successful, false if failed. 
bool TetrisGame::rotatePiece() {
    int newRotation = (currentRotation + 1) % 4; // Calculate index of rotation state after rotation
    // Try to apply rotated shape at the same position, check for conflicts
    if (!checkCollision(currentType, newRotation, currentRow, currentCol)) {
        currentRotation = newRotation;
        return true;
    }
    return false; // Rotation would conflict, so don't rotate
}

// Lock the current block to the game board (called when it cannot fall further) 
void TetrisGame::lockPiece() {
    for (size_t i = 0; i < TetrominoShapes[currentType][currentRotation].size(); ++i) {
        const Point &p = TetrominoShapes[currentType][currentRotation][i];
        int r = currentRow + p.r;
        int c = currentCol + p.c;
        // Use block type first letter to fill grid
        char fillChar;
        switch(currentType) {
            case I: fillChar = 'I'; break;
            case J: fillChar = 'J'; break;
            case L: fillChar = 'L'; break;
            case O: fillChar = 'O'; break;
            case S: fillChar = 'S'; break;
            case T: fillChar = 'T'; break;
            case Z: fillChar = 'Z'; break;
        }
        if (r >= 0 && r < height && c >= 0 && c < width) {
            board[r][c] = fillChar;
        }
    }
}

void TetrisGame::clearLines() {
    linesToClear.clear();
    // detect lines that need to be cleared
    for (int r = height - 1; r >= 0; --r) {
        bool full = true;
        for (int c = 0; c < width; ++c) {
            if (board[r][c] == ' ') {
                full = false;
                break;
            }
        }
        if (full) {
            linesToClear.push_back(r);
        }
    }

    // If there are lines to clear, start the animation
    if (!linesToClear.empty()) {
        isClearingAnimation = true;
        animationFrame = 0;
        playClearAnimation(); // Play animation (blocking)
        performLineClear();   // Actually perform the clearing
    }
}

void TetrisGame::playClearAnimation() {
    for (int i = 0; i < TOTAL_ANIMATION_FRAMES; ++i) {
        animationFrame = i;
        draw(); // Redraw interface
        
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}


//Clear filled lines and update score 
void TetrisGame::performLineClear() {
    int linesCleared = 0;
    // Check each row from bottom to top
    for (int r = height - 1; r >= 0; --r) {
        bool full = true;
        for (int c = 0; c < width; ++c) {
            if (board[r][c] == ' ') {
                full = false;
                break;
            }
        }
        if (full) {
            // Clear this row, move all rows above down
            for (int rr = r; rr > 0; --rr) {
                board[rr] = board[rr - 1]; // Cover current row with the row above
            }
            // Set the top row to empty
            board[0] = vector<char>(width, ' ');
            // Since the current row was cleared, r needs to check the same row again (filled with content from above)
            ++linesCleared;
            ++r; // Adjust index to recheck this row
        }
    }
    // Increase score based on number of lines cleared and difficulty
    if (linesCleared > 0) {
        int baseScore;
        switch(linesCleared) {
            case 1: baseScore = 100; break;
            case 2: baseScore = 300; break;
            case 3: baseScore = 500; break;
            case 4: baseScore = 800; break;
            default: baseScore = 1000; break; // Theoretically maximum 4 lines at once
        }
        
        // Adjust score based on difficulty
        switch(difficulty) {
            case EASY:
                score += baseScore; // Base score
                break;
            case MEDIUM:
                score += baseScore * 1.2; // 20% bonus
                break;
            case HARD:
                score += baseScore * 1.5; // 50% bonus
                break;
            case EXPERT:
                score += baseScore * 2.0; // 100% bonus
                break;
        }
    }
    isClearingAnimation = false;
}


// Draw current game state to console 
void TetrisGame::draw() {
    // Get terminal size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    // Use ANSI escape sequences to move cursor to center and clear screen
    cout << "\033[H\033[J";
    
    
    
    // Calculate center position for the game board
    int boardStartRow = (w.ws_row - height - 4) / 2;
    int boardStartCol = (w.ws_col - width - 4) / 2;
    
    // Ensure position is valid
    boardStartRow = max(1, boardStartRow);
    boardStartCol = max(1, boardStartCol);
    
    // Draw title
    string title = "TETRIS";
    cout << "\033[" << boardStartRow << ";" << (w.ws_col - title.length()) / 2 << "H";
    cout << titleColor << "\033[1m" << title << "\033[0m" << endl;
    
    // Draw score 
    int scoreBoxWidth = 30;
    int scoreBoxStartCol = (w.ws_col - scoreBoxWidth) / 2;
    
    // Draw score box 
    cout << "\033[" << (boardStartRow + 1) << ";" << scoreBoxStartCol << "H";
    cout << borderColor << "╔══════════════════════════════╗" << endl;
    
    string scoreText = "Score: " + to_string(score);
    
    cout << "\033[" << (boardStartRow + 2) << ";" << scoreBoxStartCol << "H";
    cout << borderColor << "║" <<"\033["<< (w.ws_col - scoreText.length()) / 2<< "G" <<scoreColor << scoreText << "\033[0m" << borderColor << "\033["<< scoreBoxStartCol+scoreBoxWidth+1<<"G"<<"║" << endl;
    
    cout << "\033[" << (boardStartRow + 3) << ";" << scoreBoxStartCol << "H";
    cout << borderColor << "╚══════════════════════════════╝" << endl;
    
    // Draw game board
    cout << "\033[" << (boardStartRow + 5) << ";" << boardStartCol << "H";
    cout << borderColor << "╔";
    for (int c = 0; c < width; ++c) cout << "═";
    cout << "╗" << endl;
    
    // Draw each row 
    for (int r = 0; r < height; ++r) {
        cout << "\033[" << (boardStartRow + 6 + r) << ";" << boardStartCol << "H";
        cout << borderColor << "║";
        
        for (int c = 0; c < width; ++c) {
            bool isAnimatingLine = find(linesToClear.begin(), 
                                    linesToClear.end(), r) 
                                    != linesToClear.end();
        
            if (isAnimatingLine && isClearingAnimation) {
                // Enhanced animation effects
                if (animationFrame % 2 == 0) {
                    cout << "\033[48;5;226m\033[38;5;232m"; // Yellow background black text
                    cout << "✦";
                } else {
                    cout << "\033[48;5;208m\033[38;5;255m"; // Orange background white text
                    cout << "★";
                }
                cout << RESET;
                continue;
            }
            
            char ch = board[r][c];
            bool isActiveBlock = false;
            
            // Check if current active block occupies this cell
            for (size_t i = 0; i < TetrominoShapes[currentType][currentRotation].size(); ++i) {
                const Point &p = TetrominoShapes[currentType][currentRotation][i];
                if (r == currentRow + p.r && c == currentCol + p.c) {
                    isActiveBlock = true;
                    break;
                }
            }
            
            if (isActiveBlock) {
                // Display active block
                switch(currentType) {
                    case I: cout << ACTIVE_COLOR['I'] << "█" << RESET; break;
                    case J: cout << ACTIVE_COLOR['J'] << "█" << RESET; break;
                    case L: cout << ACTIVE_COLOR['L'] << "█" << RESET; break;
                    case O: cout << ACTIVE_COLOR['O'] << "█" << RESET; break;
                    case S: cout << ACTIVE_COLOR['S'] << "█" << RESET; break;
                    case T: cout << ACTIVE_COLOR['T'] << "█" << RESET; break;
                    case Z: cout << ACTIVE_COLOR['Z'] << "█" << RESET; break;
                }
            } else {
                // Display fixed block or empty space
                if (ch == ' ') {
                    cout << ' ';
                } else {
                    cout << COLOR[ch] << "█" << RESET;
                }
            }
        }
        
        cout << borderColor << "║" << endl;
    }
    
    // Draw bottom border
    cout << "\033[" << (boardStartRow + 6 + height) << ";" << boardStartCol << "H";
    cout << borderColor << "╚";
    for (int c = 0; c < width; ++c) cout << "═";
    cout << "╝" << endl;
    
    string controlText = "Controls: W/↑ Rotate | A/← Left | D/→ Right | S/↓ Drop | Q Quit";
    cout << "\033[" << (boardStartRow + 8 + height) << ";" << (w.ws_col - controlText.length()) / 2 << "H";
    cout << controlColor << "Controls: W/↑ Rotate | A/← Left | D/→ Right | S/↓ Drop | Q Quit" << endl;
    
    
    // Draw next piece preview 
    if (w.ws_col >= boardStartCol + width + 15) {
        // Position the next piece box to the right of the game board
        int nextBoxStartCol = boardStartCol + width + 4;
        
        // Draw the next piece box with proper borders
        cout << "\033[" << (boardStartRow + 5) << ";" << nextBoxStartCol << "H";
        cout << borderColor << "╔═══════════╗" << endl;
        
        // Draw the next piece label
        cout << "\033[" << (boardStartRow + 6) << ";" << nextBoxStartCol << "H";
        cout << borderColor << "║" << nextPieceColor << "   Next:   " << RESET << borderColor << "║" << endl;
        
        // Create a 4x4 grid for the preview
        vector<vector<bool>> previewGrid(4, vector<bool>(4, false));
        
        // Mark the positions of the next piece in the preview grid
        for (const Point& p : TetrominoShapes[nextType][nextRotation]) {
            if (p.r >= 0 && p.r < 4 && p.c >= 0 && p.c < 4) {
                previewGrid[p.r][p.c] = true;
            }
        }
        
        // Draw the preview grid
        for (int r = 0; r < 4; ++r) {
            cout << "\033[" << (boardStartRow + 7 + r) << ";" << nextBoxStartCol << "H";
            cout << borderColor << "║    ";
            
            for (int c = 0; c < 4; ++c) {
                if (previewGrid[r][c]) {
                    switch(nextType) {
                        case I: cout << ACTIVE_COLOR['I'] << "█" << RESET; break;
                        case J: cout << ACTIVE_COLOR['J'] << "█" << RESET; break;
                        case L: cout << ACTIVE_COLOR['L'] << "█" << RESET; break;
                        case O: cout << ACTIVE_COLOR['O'] << "█" << RESET; break;
                        case S: cout << ACTIVE_COLOR['S'] << "█" << RESET; break;
                        case T: cout << ACTIVE_COLOR['T'] << "█" << RESET; break;
                        case Z: cout << ACTIVE_COLOR['Z'] << "█" << RESET; break;
                    }
                } else {
                    cout << " ";
                }
            }
            
            cout << "   " << borderColor << "║" << endl;
        }
        
        // Draw the bottom border of the next piece box
        cout << "\033[" << (boardStartRow + 11) << ";" << nextBoxStartCol << "H";
        cout << borderColor << "╚═══════════╝" << endl;
    }
    
    cout.flush();
}
//Main game loop
void TetrisGame::run() {
    initTerminal(origTermios);
    showStartScreen();  // Show startup screen first
    
    //Input and output file stream
    ifstream fin;
    ofstream fout;

    // Select difficulty
    difficulty = selectDifficulty();
    
    // Set drop speed based on difficulty
    switch(difficulty) {
        case EASY:
            dropInterval = 600;  // Slower
            break;
        case MEDIUM:
            dropInterval = 500;  // Default speed
            break;
        case HARD:
            dropInterval = 400;  // Faster
            break;
        case EXPERT:
            dropInterval = 300;  // Very fast
            break;
    }
    
    spawnPiece(); // Generate first piece
    chrono::steady_clock::time_point lastDropTime = chrono::steady_clock::now();

    // Main game loop: continue until gameOver is true
    while (!gameOver) {
        // Check if drawing clear animation
        if (!isClearingAnimation) {
            // Handle user input (non-blocking)
            char ch;
            ssize_t n = read(STDIN_FILENO, &ch, 1);
            if (n == 1) {
                // If a character was read
                if (ch == '\033') {
                    // Might be arrow key start (ESC)
                    char seq[2];
                    if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1) {
                        // seq[0] should be '[', seq[1] is direction code
                        if (seq[0] == '[') {
                            switch(seq[1]) {
                                case 'A': // ↑
                                    rotatePiece();
                                    break;
                                case 'B': // ↓
                                    // Try to move down one cell
                                    if (!movePiece(1, 0)) {
                                        // If can't move down, lock and spawn new piece
                                        lockCurrentAndSpawn();
                                    }
                                    break;
                                case 'C': // →
                                    movePiece(0, 1);
                                    break;
                                case 'D': // ←
                                    movePiece(0, -1);
                                    break;
                            }
                        }
                    }
                } else {
                    // Handle single character controls
                    char input = ch;
                    if (input >= 'a' && input <= 'z') {
                        // Convert lowercase to uppercase for unified handling
                        input = input - 'a' + 'A';
                    }
                    switch(input) {
                        case 'W': // Rotate
                            rotatePiece();
                            break;
                        case 'A': // Move left
                            movePiece(0, -1);
                            break;
                        case 'D': // Move right
                            movePiece(0, 1);
                            break;
                        case 'S': // Move down (soft drop)
                            if (!movePiece(1, 0)) {
                                // If can't move down, piece has landed, lock and refresh new piece
                                lockCurrentAndSpawn();
                            }
                            break;
                        case 'Q': // Quit game
                            gameOver = true;
                            break;
                    }
                }
            }
            // Handle automatic piece dropping (time-based)
            chrono::steady_clock::time_point now = chrono::steady_clock::now();
            long elapsed = chrono::duration_cast<chrono::milliseconds>(now - lastDropTime).count();
            if (elapsed >= dropInterval) {
                // Time reached drop interval
                if (!movePiece(1, 0)) {
                    // Can't move down, meaning bottom reached or obstacle hit, lock current piece and spawn new piece
                    lockCurrentAndSpawn();
                }
                lastDropTime = now;
            }
        }
        // Draw current game state
        draw();
        // Short sleep to reduce CPU usage and control refresh rate
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    // Exit loop means game over

    //Get bestscore
    fout.open("score.txt",ios::app);
    fout << score <<' ';
    fout.close();
    int num=0;
    fin.open("score.txt");
    while(fin>>num) {
        if (num>=bestscore)
            bestscore = num;
    }
    fin.close();
    showGameOverScreen();


    restoreTerminal(origTermios);
}

// Display a beautiful game over screen with final score and restart option 
void TetrisGame::showGameOverScreen() {
    // Get terminal size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    
    
    // Fixed box dimensions
    const int boxWidth = 66;
    const int boxHeight = 12;
    
    // Function to draw the game over screen
    auto drawGameOverScreen = [&]() {
        // Get current terminal size
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        
        // Calculate center position
        int startRow = (w.ws_row - boxHeight) / 2;
        int startCol = (w.ws_col - boxWidth) / 2;
        
        // Ensure position is valid
        startRow = max(1, startRow);
        startCol = max(1, startCol);
        
        // Clear screen
        cout << "\033[H\033[J";
        
        // Draw the game over screen
        cout << "\033[" << startRow << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "╔════════════════════════════════════════════════════════════════╗\033[0m" << endl;
        
        cout << "\033[" << (startRow+1) << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "║\033[0m" << titleColor << "                  GAME OVER!\033[0m\033[1m" << borderColor <<"\033["<<startCol+boxWidth-1<<"G"<< "║\033[0m" << endl;
        
        cout << "\033[" << (startRow+2) << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "╠════════════════════════════════════════════════════════════════╣\033[0m" << endl;
        
        cout << "\033[" << (startRow+3) << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "║\033[0m" << scoreColor << "                  Final Score: " << score <<"\033[0m\033[1m" << borderColor <<  "\033["<<startCol+boxWidth-1<<"G"<< "║\033[0m" << endl;

        cout << "\033[" << (startRow+4) << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "║\033[0m" << scoreColor << "                  Record: "<<bestscore<<"\033[0m\033[1m" << borderColor <<  "\033["<<startCol+boxWidth-1<<"G"<< "║\033[0m" << endl;
        
        cout << "\033[" << (startRow+5) << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "║\033[0m" << difficultyColor << "                  Difficulty: ";
        switch(difficulty) {
            case EASY: cout << "Easy"; break;
            case MEDIUM: cout << "Medium"; break;
            case HARD: cout << "Hard"; break;
            case EXPERT: cout << "Expert"; break;
        }
        cout << "\033[0m\033[1m" << borderColor  <<"\033["<<startCol+boxWidth-1<<"G"<< "║\033[0m" << endl;
        
        cout << "\033[" << (startRow+6) << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "╠════════════════════════════════════════════════════════════════╣\033[0m" << endl;
        
        cout << "\033[" << (startRow+7) << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "║\033[0m" << instructionColor << "              Press SPACE to play again or Q to quit \033[0m\033[1m" << borderColor  <<"\033["<<startCol+boxWidth-1<<"G"<< "║\033[0m" << endl;
        
        cout << "\033[" << (startRow+8) << ";" << startCol << "H";
        cout << "\033[1m" << borderColor << "╚════════════════════════════════════════════════════════════════╝\033[0m" << endl;
        
        cout.flush();
    };
    
    // Initial draw
    drawGameOverScreen();
    
    // Store last terminal size
    struct winsize lastW = w;
    
    // Main loop for game over screen
    while (true) {
        // Check for terminal size changes
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        if (w.ws_row != lastW.ws_row || w.ws_col != lastW.ws_col) {
            lastW = w;
            drawGameOverScreen();
        }
        
        // Check for user input
        char ch;
        if (read(STDIN_FILENO, &ch, 1) > 0) {
            if (ch == ' ') {
                // Reset game state and restart
                resetGame();
                run();
                return;
            } else if (ch == 'q' || ch == 'Q') {
                // Quit game
                return;
            }
        }
        
        // Short sleep to reduce CPU usage
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

// Reset game state for a new game 
void TetrisGame::resetGame() {
    // Reset board
    board = vector<vector<char>>(height, vector<char>(width, ' '));
    
    // Reset game variables
    currentType = I;
    nextType = I;
    currentRotation = 0;
    nextRotation = 0;
    currentRow = 0;
    currentCol = 0;
    score = 0;
    gameOver = false;
    isClearingAnimation = false;
    animationFrame = 0;
    linesToClear.clear();
}


void TetrisGame::lockCurrentAndSpawn() {
    lockPiece();      // Lock the current block to the game board
    clearLines();     // Clear any complete lines and update score
    spawnPiece();     // Generate a new block
}
