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

void initTerminal(struct termios &origTermios);
void restoreTerminal(struct termios origTermios);
