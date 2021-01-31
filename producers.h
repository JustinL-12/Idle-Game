// This class is a structure to hold data about a producer - an upgrade that automatically generates score on an interval
using namespace std;

class producer {
	public:
		int cost;
		string name;
		int amount;
		int production;
		
	producer(int the_cost, string the_name, int the_amount, int the_production) {
		cost = the_cost;
		name = the_name;
		amount = the_amount;
		production = the_production;
	}
		
};
