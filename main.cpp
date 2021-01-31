// A simple, command-line idle game 
// Written by Justin Long, 2021

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>
#include <conio.h>

#include "gamestate.h"
#include "consoleManip.h"

using namespace std;

// Function declarations
void start(gamestate& game_info);
void output(gamestate& game_info);
int keyCheck(gamestate& game_info);

// how often the total score is auto-updated
const int UPDATE_DELAY = 1000;

int main() {
	
	// Disable cursor in console
	noCursor();
			
	// Load gamestate information														
	gamestate game_info;
	game_info.loadState();
	
	output_labels(game_info);
	
	// Start game
	start(game_info);

	// Save game
	game_info.saveState();
	
	system("cls");
	
}

// Main game event loop
void start(gamestate& game_info) {
	
	time_t timer;
	time(&timer);
	time_t prev_time = timer;
	
	double startTime = GetTickCount();
	
	while (true) {
		double currentTime = GetTickCount() - startTime;
		if (currentTime >= UPDATE_DELAY) {
			
			// update and output
			game_info.update();
			
			// update previous time
			startTime = GetTickCount();
		}
		
		// Check for key commands from player
		if (keyCheck(game_info) == -1) 
			return; // Esc key pressed to exit
		
		output_nums(game_info);
		
	}
	
}

// Process keyboard controls
int keyCheck(gamestate& game_info) {
	
	// Flags for previous presses (prevents just holding down space key to generate points)
	static bool spaceFlag = false;
	if (!(GetKeyState(VK_SPACE) & 0x8000)) {
		spaceFlag = false;
	}
		
	// check for key press
	if (_kbhit()) {
		char key = _getch();
		
		switch(key) {
			// General manual adder (clicking for most idle games)
			case ' ':
				if (spaceFlag == true)
					return 0;
				game_info.total += 1;
				spaceFlag = true;
				break;
			
			// escape key pressed
			case 27:
				return -1;
				break;
				
			// P - purchase screen selected
			case 'p':
				purchaseScreen(game_info);
				output_labels(game_info);
				break;
			
			// R - reset selected
			case 'r':		
				game_info.reset_state();
				output_labels(game_info);
				break;
		}
		
	}
	return 0;
	
}


