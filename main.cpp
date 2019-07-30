#include <iostream>
#include "tree.h"
#include "node.h"
#include <iostream>
#include <fstream>
using namespace std;

Tree& LoadingTree(Tree t) {
	string file_name;

	cout << "Enter the name of the file for keys to be read from" << endl;
	cin >> file_name;

	ifstream input_file(file_name);
	if (input_file.is_open()) {
		while (!input_file.eof()) {
			string name;
			int waittime, maxwaittime, exetime, timetocomplete;
			input_file >> name >> timetocomplete >> maxwaittime >> waittime >> exetime;
			t.InsertKey(NodeInfo(name, timetocomplete, maxwaittime, waittime, exetime));
		}
		input_file.close();
	}
	return t;
}

int main() {
	Tree t;
	int choice;
	
	cout << "Enter a number of action you'd like to execute" << endl;
	cout << "1. Create an empty tree" << endl;
	cout << "2. Load tree from a file" << endl;
	cout << "3. Add a node into the tree" << endl;
	cout << "4. Search nodes by current waiting time" << endl;
	cout << "5. Search nodes by current execution time" << endl;
	cout << "6. Delete a node from the tree" << endl;
	cout << "7. Write 2-3-4 tree" << endl;
	cout << "8. Write 2-3-4 tree as Red-Black Tree" << endl;
	cout << "9. Simulation of process scheduler step-by-step" << endl;
	cout << "10. Complete simulation of process scheduler with output file" << endl;
	cout << "0. Exit" << endl;
	cin >> choice;

	while (choice) {
		switch (choice) {
			case 1: Tree(); break;
			case 2: {
				if (t.getRoot() != nullptr) {
					cout << "A tree has already been created!" << endl;
					exit(0);
				}
				else
					t = LoadingTree(t);
			} break;
			case 3: {
				string proname;
				int timetocomplete, maxwaittime, waittime = 0, exetime = 0;
				cout << "Input a process name, time to complete and maximum waiting time" << endl;
				cin >> proname >> timetocomplete >> maxwaittime;
				t.InsertKey(NodeInfo(proname, timetocomplete, maxwaittime, waittime, exetime));
			} break;
			case 4: {
				int value;
				Node *Found;
				cout << "Enter a value that you'd like to search keys by" << endl;
				cin >> value;
				Found = t.SearchNode(value);
				if (Found)
					cout << "Key with this current waiting time is found in the tree!" << endl;
				else
					cout << "Key with this current waiting time doesn't exist in the tree" << endl;
			} break;
			case 5: {
				int value;
				Node *Found;
				cout << "Enter a value that you'd like to search keys by" << endl;
				cin >> value;
				Found = t.SearchNodeExeTime(value);
				if (Found)
					cout << "Key with this current execution time is found in the tree" << endl;
				else
					cout << "There is no key with this current execution time in the tree" << endl;
			} break;
			case 6: {
				int value;
				Node *key;
				NodeInfo FinalKey;
				cout << "Enter waiting time of a node you'd like to delete" << endl;
				cin >> value;
				key = t.SearchNode(value);
				if (key->getKey1().waiting_time == value)
					FinalKey = key->getKey1();
				else if (key->getKey2().waiting_time == value)
					FinalKey = key->getKey2();
				else if (key->getKey3().waiting_time == value)
					FinalKey = key->getKey3();
				t.DeleteKey(FinalKey);
			} break;
			case 7: {t.LevelTraverse(); cout << "\n"; } break;
			case 8: {
				t.RBTreeOut();
			} break;
			case 9: t.Simulation();
		}
		cout << "\n";
		cout << "Enter a number of action you'd like to execute" << endl;
		cout << "1. Create an empty tree" << endl;
		cout << "2. Load tree from a file" << endl;
		cout << "3. Add a node into the tree" << endl;
		cout << "4. Search nodes by current waiting time" << endl;
		cout << "5. Search nodes by current execution time" << endl;
		cout << "6. Delete a node from the tree" << endl;
		cout << "7. Write 2-3-4 tree" << endl;
		cout << "8. Write 2-3-4 tree as Red-Black Tree" << endl;
		cout << "9. Simulation of process scheduler step-by-step" << endl;
		cout << "10. Complete simulation of process scheduler with output file" << endl;
		cout << "0. Exit" << endl;
		cin >> choice;
	}
}