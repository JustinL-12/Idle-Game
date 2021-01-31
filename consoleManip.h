// This file contains various functions that handle outputting data to the command line

// output only game information numbers to console to avoid flickering
void output_nums(gamestate& game_info) {
	
	// Info outputs
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (SHORT)15, (SHORT)0 };
    SetConsoleCursorPosition(hOut, coord);
	
	cout << game_info.total;	
	int count = 4;
	for (producer p : game_info.producers) {
		coord.X = 5 + (p.name).length() + 2 + (to_string(p.production)).length() + 6;
		coord.Y = count;
		SetConsoleCursorPosition(hOut, coord);
		cout << to_string(p.amount) << endl;
		count++;
	}
}

// output labels and static text
void output_labels(gamestate& game_info) {
	// clear screen
	system("cls");
	cout << "Current total: " << endl;
	cout << "Production: ";
	cout << endl << endl << "Producers: " << endl;
	for (producer p : game_info.producers) {
		cout << "     " << p.name << " (" << to_string(p.production) << "/s) : \n";
	}
	cout << endl << endl << "Controls: " << endl;
	cout << "     Space to manually generate clicks" << endl
		 << "     P to purchase producers" << endl
		 << "     Esc to quit" << endl;
} 

// Function to set no cursor highlight on the command line
void noCursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Purchase select screen
void purchaseScreen(gamestate& game_info) {
	// clear screen
	system("cls");
	
	// Print options
	cout << "Select purchase option by pressing corresponding num key:" << endl << endl;
	int count = 1;
	for (producer p : game_info.producers) {
		cout << "     " << to_string(count++) << ")  " << p.name << "  -  Cost: " << to_string(p.cost) << endl;
	}
	cout << "     Esc to cancel" << endl;
	
	// Wait for key press
	while(!_kbhit) { }
	char key = _getch();
	
	// Process selection
	if (key == 27) {
		return;
	}
	for (int i=0; i<((game_info.producers).size()); i++) {
		if ((key - '0') == i+1) {
			// Check for available cost
			if (game_info.total < game_info.producers[i].cost)
				return;
			
			// Purchase producer
			game_info.total -= game_info.producers[i].cost;
			game_info.producers[i].amount += 1;
		}
	}s
}








