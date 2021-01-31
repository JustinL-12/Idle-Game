#include <vector>
#include "producers.h"

using namespace std;

// Path of save file
const string SAVE_FILE_NAME = "sav.txt";

// Gamestate class that holds all game data and also handles save file creation and use
class gamestate {
	public:
		// stored score
		long long total;
		vector<producer> producers; 
		
		// load current state from save file
		void loadState() {
			// Producer creation
			producers.push_back(producer(20, "Clicker Machine", 0, 1));
			producers.push_back(producer(200, "Clicker Factory", 0, 10));
			producers.push_back(producer(2000, "Clicker City", 0, 100));
			
			// Open file and check if it exists
			ifstream save_file(SAVE_FILE_NAME);
			if(!(save_file.good())) {
				// Create save file
				createSave();
				save_file.open(SAVE_FILE_NAME);
			}
			
			string input_read;
			getline(save_file, input_read);
			total = stoi(input_read);
			
			// Load producers 
			for (int i=0; i < producers.size(); i++) {
				getline(save_file, input_read);
				producers[i].amount = stoi(input_read);
			}
			
			save_file.close();
		}
		
		// save current state to save file
		void saveState() {
			ofstream save_file(SAVE_FILE_NAME);
			string out_write = to_string(total);
			save_file << out_write << endl;
			for (producer p : producers)
				save_file << to_string(p.amount) << endl;
			save_file.close();
		}
	
		// update score 
		void update() {
			// Add values for each producer * the quantity owned
			for(producer p : producers) {
				total += p.amount * p.production;
			}
		}
		
		// reset all values to 0
		void reset_state() {
			total = 0;
			for(int i=0; i<producers.size(); i++) {
				producers[i].amount = 0;
			}
		}
	
	private:
		// Create save file
		void createSave() {
			ofstream save_file("sav.txt");
			save_file << "0" << endl;
			for(producer p : producers) {
				save_file << "0" << endl;
			}
			save_file.close();
		}
	
};
