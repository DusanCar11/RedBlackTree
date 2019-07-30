#pragma once
#include <iostream>
#include <string>
#include "node.h"
using namespace std;

class Tree {
private:
	Node *root = nullptr;
public:
	Tree() {};
	Node* getRoot() { return root; }
	Tree& InsertKey(NodeInfo key);
	Node* SearchNode(int value);
	Node* SearchNodeExeTime(int value);
	Tree& DeleteKey(NodeInfo key);
	Node* FindSuccessor(Node *Found, int value);
	void RBTreeOut();
	void Simulation();
	void LevelTraverse();
	~Tree();
};
