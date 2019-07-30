#include <iostream>
#include "node.h"
#include "tree.h"
using namespace std;

void Node::AddKey(int place, NodeInfo key) {
	switch (place) {
	case 1: keys[0] = key; break;
	case 2: keys[1] = key; break;
	case 3: keys[2] = key; break;
	}
}

int Node::NumberOfKeys() {
	int num = 0;
	if (this->getKey1().process_name != " ")
		num++;
	if (this->getKey2().process_name != " ")
		num++;
	if (this->getKey3().process_name != " ")
		num++;
	return num;
}