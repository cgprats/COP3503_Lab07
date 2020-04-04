#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

mt19937 random_mt;

class State {
	private:
		string _state;
		string _pci;
		string _pop;
		string _mhi;
		string _houseCount;
	public:
		State(string, string, string, string, string);
		void DisplayState();
};

State::State(string state, string pci, string pop, string mhi, string houseCount) {
	_state = state;
	_pci = pci;
	_pop = pop;
	_mhi = mhi;
	_houseCount = houseCount;
}

void State::DisplayState() {
	cout << _state << endl;
	cout << "Population: " << _pop << endl;
	cout << "Per Capita Income: " << _pci << endl;
	cout << "Median Household Income: " << _mhi << endl;
	cout << "Number of Households: " << _houseCount << endl;
}

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void RollDice(int numberOfRolls, int numberOfSides) {
	map<int, int> rollCount;
	for (int i = 1; i <= numberOfRolls; i++) {
		rollCount.emplace(i, 0);
	}
	int rollVal;
	for (int i = 1; i <= numberOfRolls; i++) {
		rollVal = Random(1, numberOfSides);
		rollCount[rollVal] += 1;
	}
	for (int i = 1; i <= numberOfSides; i++) {
		cout << i << ": " << rollCount[i] << endl;
	}
}

int main()
{
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);


		cout << "Number of times to roll the die: ";
      // user input
		int numberOfRolls;
		cin >> numberOfRolls;

		cout << "Number of sides on this die: ";
      // user input
		int numberOfSides;
		cin >> numberOfSides;

		// Roll Dice
		RollDice(numberOfRolls, numberOfSides);
	}
	else if (option == 2)
	{
	   // Load the states
	ifstream stateFile; 
	stateFile.open("states.csv");
	map<string, State> states;
	string state;
	string pci;
	string pop;
	string mhi;
	string houseCount;
	while (!stateFile.eof()) {
		getline(stateFile, state, ',');
		getline(stateFile, pci, ',');
		getline(stateFile, pop, ',');
		getline(stateFile, mhi, ',');
		getline(stateFile, houseCount);
		if (state != "State") {
			State tempState(state, pci, pop, mhi, houseCount);
			states.emplace(state, tempState);
		}
	}

	   // Get input for option 1 (show all states) or 2 (do a search for a particular state)
	cout << "1. Print all states" << endl;
	
	cout << "2. Search for a state" << endl;
	cin >> option;
	auto it = states.begin();
	if (option == 1) {
		for (; it != states.end(); it++) {
			it->second.DisplayState();
		}
	}
	if (option == 2) {
		cin >> state;
		it = states.find(state);
		if (it == states.end()) {
			cout << "No match found for " << state;
		}
		else {
			it->second.DisplayState();
		}
	}
	}

	return 0;
}

