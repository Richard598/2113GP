#include"terminal.h"

void initTerminal(struct termios &origTermios) {
    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &origTermios);
    struct termios newTermios = origTermios;
    // Turn off canonical mode and local echo
    newTermios.c_lflag &= ~(ICANON | ECHO);
    // Set non-blocking: minimum characters to read is 0, timeout is 0 (meaning read returns immediately)
    newTermios.c_cc[VMIN] = 0;
    newTermios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    // Hide cursor (avoid cursor flickering during refresh)
    cout << "\033[?25l";
}

void restoreTerminal(struct termios origTermios) {
    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &origTermios);
    // Show cursor
    cout << "\033[?25h";
    cout.flush();
}
