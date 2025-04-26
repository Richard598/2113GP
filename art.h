#pragma once

#include<string>
#include<vector>
#include<map>

using namespace std;

const vector<string> TETRIS_ART = {
    "\033[38;5;196m▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓▓  ▓▓▓▓    ▓▓▓▓▓▓",
    "\033[38;5;208m   ▓▓     ▓▓           ▓▓     ▓▓    ▓▓   ▓▓   ▓▓      ",
    "\033[38;5;226m   ▓▓     ▓▓▓▓▓▓       ▓▓     ▓▓▓▓▓▓▓▓   ▓▓     ▓▓▓▓  ",
     "\033[38;5;46m   ▓▓     ▓▓           ▓▓     ▓▓  ▓▓     ▓▓         ▓▓",
     "\033[38;5;33m   ▓▓     ▓▓▓▓▓▓▓▓     ▓▓     ▓▓    ▓▓  ▓▓▓▓  ▓▓▓▓▓▓  \033[0m"
};

const vector<string> difficultyColors = {
    "\033[38;5;22m",  // Dark green - Easy
    "\033[38;5;18m",  // Dark blue - Medium
    "\033[38;5;130m", // Dark orange - Hard
    "\033[38;5;88m"   // Dark red - Expert
};

const string borderColor = "\033[38;5;18m"; // Dark blue
const string titleColor = "\033[38;5;18m"; // Dark blue
const string descriptionColor = "\033[38;5;18m"; // Dark blue
const string instructionColor = "\033[38;5;88m"; // Dark red

// Define block color codes
static map<char,string> COLOR = {
    {'I',"\033[38;5;51;48;5;51m"},  // I-Cyan
    {'J',"\033[38;5;33;48;5;33m"},  // J-Blue 
    {'L',"\033[38;5;208;48;5;208m"}, // L-Orange
    {'O',"\033[38;5;226;48;5;226m"}, // O-Yellow
    {'S',"\033[38;5;46;48;5;46m"},  // S-Green
    {'T',"\033[38;5;129;48;5;129m"}, // T-Purple  
    {'Z',"\033[38;5;196;48;5;196m"}  // Z-Red
};

const string BORDER_COLOR = "\033[38;5;255m"; // White border
const string RESET = "\033[0m";

// Define bright color constants
static map<char,string> ACTIVE_COLOR = {
    {'I',"\033[38;5;87;48;5;87m"},  // I-Bright cyan
    {'J',"\033[38;5;39;48;5;39m"},  // J-Bright blue 
    {'L',"\033[38;5;214;48;5;214m"}, // L-Bright orange
    {'O',"\033[38;5;226;48;5;226m"}, // O-Bright yellow
    {'S',"\033[38;5;46;48;5;46m"},  // S-Bright green
    {'T',"\033[38;5;129;48;5;129m"}, // T-Bright purple  
    {'Z',"\033[38;5;196;48;5;196m"}  // Z-Bright red
};

// Define colors for UI elements - using darker colors

const string controlColor = "\033[38;5;22m"; // Dark green
const string nextPieceColor = "\033[38;5;130m"; // Dark orange
const string scoreColor = "\033[38;5;130m";  // Orange
const string difficultyColor = "\033[38;5;33m";  // Blue

const string PRESS_START = "Press SPACE to start";
