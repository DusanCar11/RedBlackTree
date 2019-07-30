#pragma once
#include <iostream>
#include <string>
using namespace std;

struct NodeInfo {
	string process_name = " ";
	int time_to_complete = 0;
	int max_waiting_time = 0;
	int waiting_time = 0;
	int execution_time = 0;
	NodeInfo() {};
	NodeInfo(string proname, int timetocomp, int maxwaittime, int waittime, int exetime) : process_name(proname), time_to_complete(timetocomp), max_waiting_time(maxwaittime), waiting_time(waittime), execution_time(exetime) {};
	NodeInfo(NodeInfo& key) : process_name(key.process_name), time_to_complete(key.time_to_complete), max_waiting_time(key.max_waiting_time), waiting_time(key.waiting_time), execution_time(key.execution_time) {};
	NodeInfo(string proname, int timetocomp, int maxwaittime) : process_name(proname), time_to_complete(timetocomp), max_waiting_time(maxwaittime) {};
	friend ostream& operator<< (ostream& it, NodeInfo& p) {
		return  it << p.process_name << " ttc " << p.time_to_complete << " mwt: " << p.max_waiting_time << " wt: " << p.waiting_time << " et: " << p.execution_time << endl;
	}
};

class Node {
private:
	NodeInfo keys[3];
	Node *pointers[4], *father=nullptr;
public:
	Node(NodeInfo key) { keys[1] = key; for (int i = 0; i < 4; i++) pointers[i] = nullptr; };
	Node(NodeInfo onekey, NodeInfo twokey) {
		if (onekey.waiting_time > twokey.waiting_time) {
			keys[0] = twokey; keys[1] = onekey;
		}
		else {
			keys[0] = onekey;
			keys[1] = twokey;
		}
		for (int i = 0; i < 4; i++) pointers[i] = nullptr;
	}
	int NumberOfKeys();
	void AddKey(int place, NodeInfo key);
	NodeInfo getKey1() { return keys[0]; }
	NodeInfo getKey2() { return keys[1]; }
	NodeInfo getKey3() { return keys[2]; }
	NodeInfo getKeys(int x) { return keys[x]; }
	Node* getLeft() { return pointers[0]; }
	Node* getMiddleLeft() { return pointers[1]; }
	Node* getMiddleRight() { return pointers[2]; }
	Node* getRight() { return pointers[3]; }
	Node* getFather() { return father; }
	Node* getPointer(int i) { return pointers[i]; }
	void AddWaitingTime(int i, int value) { keys[i].waiting_time += value; }
	void MinusTimeLeft(int i, int value) { keys[i].time_to_complete -= value; }
	void changeProcessName(int i, string value) { keys[i].process_name = value; }
	void changeWaitingTime(int i, int value) { keys[i].waiting_time = value; }
	void changeMaxWaitingTime(int i, int value) { keys[i].max_waiting_time = value; }
	void changeExeTime(int i, int value) { keys[i].execution_time = value; }
	void changeTimeLeft(int i, int value) { keys[i].time_to_complete = value; }
	void changeLeft(Node* newpointer) { pointers[0] = newpointer; }
	void changeMiddleLeft(Node* newpointer) { pointers[1] = newpointer; }
	void changeMiddleRight(Node* newpointer) { pointers[2] = newpointer; }
	void changeRight(Node* newpointer) { pointers[3] = newpointer; }
	void changeFather(Node* newpointer) { father = newpointer; }
	void changePointer(Node* newpointer, int i) { pointers[i] = newpointer; }
	void changeKey1(NodeInfo newinfo) { keys[0] = newinfo; }
	void changeKey2(NodeInfo newinfo) { keys[1] = newinfo; }
	void changeKey3(NodeInfo newinfo) { keys[2] = newinfo; }
	void changeKeys(NodeInfo newinfo, int value) { keys[value] = newinfo; }
	Node* getSons(int i) { return pointers[i]; }
	bool NodeisFull() { if ((keys[0].process_name == " ") || (keys[1].process_name == " ") || (keys[2].process_name == " ")) return false; else return true; }
	bool NodeisLeaf() { if ((pointers[0] == nullptr) && (pointers[1] == nullptr) && (pointers[2] == nullptr) && (pointers[3] == nullptr)) return  true; else return false; }
};

