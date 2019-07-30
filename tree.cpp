#include <iostream>
#include "tree.h"
#include "node.h"
#include <queue>
#include <stack>
using namespace std;

Tree& Tree::InsertKey(NodeInfo key) {
	if (root == nullptr)
		root = new Node(key);
	else {

		Node *tmp = root;
		while (!tmp->NodeisLeaf()) {
			Node *tmp2 = tmp;
			if (tmp->getKey2().waiting_time >= key.waiting_time) {
				if (tmp->getKey1().process_name != " ")
					if ((tmp->getKey1().waiting_time >= key.waiting_time) && (tmp->getLeft()!=nullptr))
						tmp = tmp->getLeft();
					else
						tmp = tmp->getMiddleLeft();
				else
					tmp = tmp->getMiddleLeft();
			}
			else {
				if (tmp->getKey3().process_name != " ")
					if ((tmp->getKey3().waiting_time <= key.waiting_time) && (tmp->getRight()!=nullptr))
						tmp = tmp->getRight();
					else
						tmp = tmp->getMiddleRight();
				else
					tmp = tmp->getMiddleRight();
			}
		} //end while

		if (tmp->NodeisFull()) {
			//breakNode();
			Node *help = nullptr, *help2 = nullptr;
			if (key.waiting_time >= tmp->getKey2().waiting_time) {
				help = new Node(tmp->getKey1());
				if (tmp->getKey3().waiting_time >= key.waiting_time)
					help2 = new Node(key, tmp->getKey3());
				else
					help2 = new Node(tmp->getKey3(), key);
			}
			else {
				if (tmp->getKey1().waiting_time <= key.waiting_time)
					help = new Node(tmp->getKey1(), key);
				else
					help = new Node(key, tmp->getKey1());
				help2 = new Node(tmp->getKey3());
			} // Brejkovanje lista ako je pun

			NodeInfo help_key = tmp->getKey2();
			Node *tmp_old = tmp;
			tmp = tmp->getFather();

			if (tmp == nullptr) {
				root = new Node(help_key);
				root->changeMiddleLeft(help);
				root->changeMiddleRight(help2);
				root->getMiddleLeft()->changeFather(root);
				root->getMiddleRight()->changeFather(root);
			}

			Node *help3, *help4 = nullptr;
			while (tmp) {
				if (tmp == nullptr) break;
				if (!tmp->NodeisFull()) {
					if ((tmp->getKey1().process_name == " ") && (tmp->getKey3().process_name == " ")) {
						if (tmp->getKey2().waiting_time >= help_key.waiting_time) {
							tmp->AddKey(1, help_key);
							tmp->changeLeft(help);
							tmp->changeMiddleLeft(help2);
							help->changeFather(tmp);
							help2->changeFather(tmp);
						}
						else {
							tmp->AddKey(3, help_key);
							tmp->changeRight(help2);
							tmp->changeMiddleRight(help);
							help2->changeFather(tmp);
							help->changeFather(tmp);
						}
					}
					else if ((tmp->getKey1().process_name != " ") && (tmp->getKey1().waiting_time >= help_key.waiting_time) && (tmp->getKey3().process_name == " ")) {
						if ((tmp->getKey1().waiting_time == help_key.waiting_time) && (tmp->getKey2().waiting_time == help_key.waiting_time)) {
							if (tmp_old == tmp->getMiddleRight()) {
								tmp->AddKey(3, help_key);
								tmp->changeMiddleRight(help);
								tmp->changeRight(help2);
								help2->changeFather(tmp);
								help->changeFather(tmp);
							}
							else if (tmp_old == tmp->getMiddleLeft()) {
								tmp->changeRight(tmp->getMiddleRight());
								//tmp->changeMiddleRight(tmp->getMiddleLeft());
								tmp->changeMiddleRight(help2);
								tmp->changeMiddleLeft(help);
								tmp->AddKey(3, tmp->getKey2());
								//tmp->AddKey(2, tmp->getKey1());
								tmp->AddKey(2, help_key);
								help2->changeFather(tmp);
								help->changeFather(tmp);
							}
							else {
								tmp->changeRight(tmp->getMiddleRight());
								tmp->changeMiddleRight(tmp->getMiddleLeft());
								tmp->changeMiddleLeft(help2);
								tmp->changeLeft(help);
								tmp->AddKey(3, tmp->getKey2());
								tmp->AddKey(2, tmp->getKey1());
								tmp->AddKey(1, help_key);
								help2->changeFather(tmp);
								help->changeFather(tmp);
							}
						}
						else if (tmp_old == tmp->getMiddleLeft()) { ///////////////
							tmp->changeRight(tmp->getMiddleRight());
							//tmp->changeMiddleRight(tmp->getMiddleLeft());
							tmp->changeMiddleRight(tmp->getMiddleLeft());
							tmp->changeMiddleLeft(help2);
							tmp->changeLeft(help);
							tmp->AddKey(3, tmp->getKey2());
							//tmp->AddKey(2, tmp->getKey1());
							tmp->AddKey(2, help_key);
							help2->changeFather(tmp);
							help->changeFather(tmp);
						}
					}
					else if ((tmp->getKey1().process_name != " ") && (tmp->getKey1().waiting_time <= help_key.waiting_time) && (tmp->getKey2().waiting_time >= help_key.waiting_time) && (tmp->getKey3().process_name == " ")) {
						tmp->AddKey(3, tmp->getKey2());
						tmp->AddKey(2, help_key);
						tmp->changeRight(tmp->getMiddleRight());
						tmp->changeMiddleLeft(help);
						tmp->changeMiddleRight(help2);
						help2->changeFather(tmp);
						help->changeFather(tmp);
					}
					else if ((tmp->getKey1().process_name != " ") && (tmp->getKey1().waiting_time <= help_key.waiting_time) && (tmp->getKey2().waiting_time <= help_key.waiting_time) && (tmp->getKey3().process_name == " ")) {
						tmp->AddKey(3, help_key);
						tmp->changeMiddleRight(help);
						tmp->changeRight(help2);
						help2->changeFather(tmp);
						help->changeFather(tmp);
					}
					else if ((tmp->getKey3().process_name != " ") && (tmp->getKey3().waiting_time <= help_key.waiting_time) && (tmp->getKey1().process_name == " ")) {
						if ((tmp->getKey3().waiting_time == help_key.waiting_time) && (tmp->getKey2().waiting_time == help_key.waiting_time)) {
							if (tmp_old == tmp->getMiddleLeft()) {
								tmp->AddKey(1, help_key);
								tmp->changeLeft(help);
								tmp->changeMiddleLeft(help2);
								help2->changeFather(tmp);
								help->changeFather(tmp);
							}
							else if (tmp_old == tmp->getMiddleRight()) {
								tmp->changeLeft(tmp->getMiddleLeft());
								//tmp->changeMiddleRight(tmp->getMiddleLeft());
								tmp->changeMiddleRight(help2);
								tmp->changeMiddleLeft(help);
								tmp->AddKey(1, tmp->getKey2());
								//tmp->AddKey(2, tmp->getKey1());
								tmp->AddKey(2, help_key);
								help2->changeFather(tmp);
								help->changeFather(tmp);
							}
							else {
								tmp->changeLeft(tmp->getMiddleLeft());
								tmp->changeMiddleLeft(tmp->getMiddleRight());
								tmp->changeMiddleRight(help);
								tmp->changeRight(help2);
								tmp->AddKey(1, tmp->getKey2());
								tmp->AddKey(2, tmp->getKey1());
								tmp->AddKey(3, help_key);
								help2->changeFather(tmp);
								help->changeFather(tmp);
							}
						}
						else { /////////////////////////
							tmp->changeLeft(tmp->getMiddleLeft());
							//tmp->changeMiddleRight(tmp->getMiddleLeft());
							tmp->changeMiddleLeft(tmp->getMiddleRight());
							tmp->changeMiddleRight(help);
							tmp->changeRight(help2);
							tmp->AddKey(1, tmp->getKey2());
							//tmp->AddKey(2, tmp->getKey1());
							tmp->AddKey(2, help_key);
							help2->changeFather(tmp);
							help->changeFather(tmp);
						}
					}
					else if ((tmp->getKey3().process_name != " ") && (tmp->getKey3().waiting_time >= help_key.waiting_time) && (tmp->getKey2().waiting_time <= help_key.waiting_time) && (tmp->getKey1().process_name == " ")) {
						tmp->AddKey(1, tmp->getKey2());
						tmp->AddKey(2, help_key);
						tmp->changeLeft(tmp->getMiddleLeft());
						tmp->changeMiddleLeft(help);
						tmp->changeMiddleRight(help2);
						help2->changeFather(tmp);
						help->changeFather(tmp);
					}
					else if ((tmp->getKey3().process_name != " ") && (tmp->getKey3().waiting_time >= help_key.waiting_time) && (tmp->getKey2().waiting_time >= help_key.waiting_time) && (tmp->getKey1().process_name == " ")) {
						tmp->AddKey(1, help_key);
						tmp->changeMiddleLeft(help2);
						tmp->changeLeft(help);
						help2->changeFather(tmp);
						help->changeFather(tmp);
					}
					break;
				}

				NodeInfo help_key2 = tmp->getKey2();
				if (tmp->NodeisFull()) {
					if (help_key.waiting_time >= tmp->getKey2().waiting_time) {
						help3 = new Node(tmp->getKey1());
						help4 = new Node(help_key, tmp->getKey3());
					}
					else {
						help3 = new Node(tmp->getKey1(), help_key);
						help4 = new Node(tmp->getKey3());
					} //brejkovanje oca ako je i on pun
				}

				if (help3->NumberOfKeys() == 2) {
					if (tmp->NumberOfKeys() == 3) {
						help3->changeLeft(help);
						help3->changeMiddleLeft(help2);
						help3->changeMiddleRight(tmp->getMiddleLeft());
						help3->getMiddleRight()->changeFather(help3);
						help4->changeMiddleLeft(tmp->getMiddleRight());//
						help4->changeMiddleRight(tmp->getRight());//
						help4->getMiddleLeft()->changeFather(help4);//
						help4->getMiddleRight()->changeFather(help4);//
					}
					/*else {
						help3->changeLeft(tmp->getLeft());
						help3->changeMiddleLeft(help);
						help3->changeMiddleRight(help2);
						help3->getLeft()->changeFather(help3);
						help4->changeMiddleLeft(tmp->getMiddleRight());//
						help4->changeMiddleRight(tmp->getRight());//
						help4->getMiddleLeft()->changeFather(help4);//
						help4->getMiddleRight()->changeFather(help4);//
					}*/
					help->changeFather(help3);
					help2->changeFather(help3);
				}

				if (help3->NumberOfKeys() == 1) {
					if (tmp->NumberOfKeys() == 3)
						if (tmp->getKey1().waiting_time >= help->getKey2().waiting_time) {
							help3->changeMiddleLeft(help);
							help3->changeMiddleRight(help2);
							help->changeFather(help3);
							help2->changeFather(help3);
							help4->changeLeft(tmp->getMiddleLeft()); //
							help4->changeMiddleLeft(tmp->getMiddleRight()); //
							help4->changeMiddleRight(tmp->getRight());//
							help4->getLeft()->changeFather(help4);//
							help4->getMiddleLeft()->changeFather(help4);//
							help4->getMiddleRight()->changeFather(help4);//
						}
						else {
							help3->changeMiddleLeft(tmp->getLeft());
							help3->changeMiddleRight(tmp->getMiddleLeft());
							help3->getMiddleLeft()->changeFather(help3);
							help3->getMiddleRight()->changeFather(help3);
							help4->changeLeft(help);//
							help4->changeMiddleLeft(help2);//
							help4->changeMiddleRight(tmp->getRight());//
							help->changeFather(help4);//
							help2->changeFather(help4);//
							help4->getMiddleRight()->changeFather(help4);//
						}
				}

				/*if (help4->NumberOfKeys() == 1) {
					if (tmp->NumberOfKeys() == 3)
						if (tmp->getKey3().waiting_time <= help->getKey2().waiting_time)  {
							help4->changeMiddleLeft(help);
							help4->changeMiddleRight(help2);
							help->changeFather(help4);
							help2->changeFather(help4);
						}
						else {
							help4->changeMiddleLeft(tmp->getMiddleRight());
							help4->changeMiddleRight(tmp->getRight());
							help4->getMiddleLeft()->changeFather(help4);
							help4->getMiddleRight()->changeFather(help4);
						}
				}

				if (help4->NumberOfKeys() == 2) {
					if (tmp->getRight()->NumberOfKeys() == 3) {
						help4->changeMiddleRight(help2);
						help4->changeMiddleLeft(help);
						help4->changeLeft(tmp->getMiddleRight());
						help4->getLeft()->changeFather(help4);
					}
					else {
						help4->changeRight(tmp->getRight());
						help4->getRight()->changeFather(help4);
						help4->changeMiddleRight(help2);
						help4->changeMiddleLeft(help);
					}
					help->changeFather(help4);
					help2->changeFather(help4);
				}*/
				tmp_old = tmp;
				tmp = tmp->getFather();
				help = help3;
				help2 = help4;
				help_key = help_key2;

				if (tmp == nullptr) {
					root = new Node(help_key);
					root->changeMiddleLeft(help);
					root->changeMiddleRight(help2);
					root->getMiddleLeft()->changeFather(root);
					root->getMiddleRight()->changeFather(root);
				}
			} 
				delete tmp_old;
		}
		else {
			if (tmp->getKey1().process_name != " ") {
				if ((tmp->getKey1().waiting_time <= key.waiting_time) && (tmp->getKey2().waiting_time <= key.waiting_time))
					tmp->AddKey(3, key);
				else if ((tmp->getKey1().waiting_time <= key.waiting_time) && (tmp->getKey2().waiting_time >= key.waiting_time)) {
					tmp->AddKey(3, tmp->getKey2());
					tmp->AddKey(2, key);
				}
				else if ((tmp->getKey1().waiting_time >= key.waiting_time) && (tmp->getKey2().waiting_time >= key.waiting_time)) {
					tmp->AddKey(3, tmp->getKey2());
					tmp->AddKey(2, tmp->getKey1());
					tmp->AddKey(1, key);
				}
			}
			else if ((tmp->getKey3().process_name != " ") && (tmp->getKey3().process_name != key.process_name)) {
				if ((tmp->getKey2().waiting_time >= key.waiting_time) && (tmp->getKey3().waiting_time >= key.waiting_time))
					tmp->AddKey(1, key);
				else if ((tmp->getKey2().waiting_time <= key.waiting_time) && (tmp->getKey3().waiting_time >= key.waiting_time)) {
					tmp->AddKey(1, tmp->getKey2());
					tmp->AddKey(2, key);
				}
				else if ((tmp->getKey2().waiting_time <= key.waiting_time) && (tmp->getKey3().waiting_time <= key.waiting_time)) {
					tmp->AddKey(1, tmp->getKey2());
					tmp->AddKey(2, tmp->getKey3());
					tmp->AddKey(3, key);
					}
				}
			if ((tmp->getKey1().process_name == " ") && (tmp->getKey3().process_name == " ")) {
				if (tmp->getKey2().waiting_time >= key.waiting_time)
					tmp->AddKey(1, key);
				else
			tmp->AddKey(3, key);
			}
		} //end else
	}
	return *this;
}

void Tree::LevelTraverse() {

		queue<Node*> s1;
		queue<Node*> s2;
		s1.push(root);
		Node* help;
		if (root == nullptr) return;
		while (!s1.empty() || !s2.empty()) {
			cout << endl;
			while (!s1.empty()) {
				help = s1.front();
				s1.pop();
				cout << "    ";
				if (help->getKey1().process_name != " ")cout << " " << help->getKey1().process_name;
				if (help->getKey2().process_name != " ")cout << " " << help->getKey2().process_name;
				if (help->getKey3().process_name != " ")cout << " " << help->getKey3().process_name;
				for (int i = 0; i <4; i++)
					if (help->getSons(i)) s2.push(help->getSons(i));
			}
			cout << endl;
			while (!s2.empty()) {
				help = s2.front();
				s2.pop();
				cout << "    ";
				if (help->getKey1().process_name != " ")cout << " " << help->getKey1().process_name;
				if (help->getKey2().process_name != " ")cout << " " << help->getKey2().process_name;
				if (help->getKey3().process_name != " ")cout << " " << help->getKey3().process_name;
				for (int i = 0; i < 4; i++)
					if (help->getSons(i)) s1.push(help->getSons(i));
			}
		}
}

Node* Tree::SearchNodeExeTime(int value) {
	Node *tmp = root;

	while (tmp) {
		if ((value == tmp->getKey1().execution_time) || (value == tmp->getKey2().execution_time) || (value == tmp->getKey3().execution_time))
			return tmp;
		if ((value < tmp->getKey1().execution_time) && (tmp->getKey1().process_name != " "))
			tmp = tmp->getLeft();
		else if ((value > tmp->getKey1().execution_time) && (value <= tmp->getKey2().execution_time))
			tmp = tmp->getMiddleLeft();
		else if ((value > tmp->getKey2().execution_time) && (value <= tmp->getKey3().execution_time))
			tmp = tmp->getMiddleRight();
		else if ((value > tmp->getKey2().execution_time) && (value > tmp->getKey3().execution_time) && (tmp->getKey3().process_name == " "))
			tmp = tmp->getMiddleRight();
		else
			tmp = tmp->getRight();
	}
	return nullptr;
}

Node* Tree::SearchNode(int value) {
	Node *tmp = root;

	while (tmp) {
		if ((value == tmp->getKey1().waiting_time) || (value == tmp->getKey2().waiting_time) || (value == tmp->getKey3().waiting_time))
			return tmp;
		if ((value < tmp->getKey1().waiting_time) && (tmp->getKey1().process_name != " "))
			tmp = tmp->getLeft();
		else if ((value > tmp->getKey1().waiting_time) && (value <= tmp->getKey2().waiting_time))
			tmp = tmp->getMiddleLeft();
		else if ((value > tmp->getKey2().waiting_time) && (value <= tmp->getKey3().waiting_time))
			tmp = tmp->getMiddleRight();
		else if ((value > tmp->getKey2().waiting_time) && (value > tmp->getKey3().waiting_time) && (tmp->getKey3().process_name == " "))
			tmp = tmp->getMiddleRight();
		else
			tmp = tmp->getRight();
	}
	return nullptr;
}

Node* Tree::FindSuccessor(Node *Found, int value) {

	Node *tmp = Found;
	if (value == Found->getKey1().waiting_time)
		tmp = tmp->getMiddleLeft();
	else if (value == Found->getKey2().waiting_time)
		tmp = tmp->getMiddleRight();
	else if (value == Found->getKey3().waiting_time)
		tmp = tmp->getRight();

	if (tmp) {
		while ((tmp->getLeft() != nullptr) || (tmp->getMiddleLeft() != nullptr)) {
			if (tmp->getLeft() != nullptr)
				tmp = tmp->getLeft();
			else
				tmp = tmp->getMiddleLeft();
		}
		return tmp;
	}
	else
		if (tmp->getFather())
			return tmp->getFather();
}

Tree& Tree::DeleteKey(NodeInfo value) {
	
	if (root == nullptr) {
		cout << "You can't delete from an empty tree" << endl;
		return *this;
	}

	Node *help, *help2 = nullptr; 
	Node *bro1, *bro2;
	int i, i2, foundkey = 0;
	Node *Found=nullptr, *searching;
	NodeInfo temporary;
	//Found = SearchNode(value.waiting_time);
	//help = Found;

	searching = root;
	stack<Node*> s1;
	s1.push(searching);
	while (!s1.empty()) {
		if ((searching->getKey1().process_name == value.process_name) || (searching->getKey2().process_name == value.process_name) || (searching->getKey3().process_name == value.process_name)) {
			Found = searching;
			help = searching;
			break;
		}
		for (i = 0;i < 4;i++) {
			if (searching->getPointer(i)) {
				s1.push(searching->getPointer(i));
			}
		}
		searching = s1.top();
		s1.pop();
	}

	if (Found == nullptr) {
		cout << "You can't delete a node that doesn't exist in a tree!" << endl;
		return *this;
	}
	if (help == nullptr)
		return *this;

	if ((Found->getKey1().waiting_time == value.waiting_time) && (Found->getKey1().process_name != " ")) {
		i = 0;
		temporary = Found->getKey1();
	}
	else if ((Found->getKey2().waiting_time == value.waiting_time) && (Found->getKey2().process_name != " ")) {
		i = 1;
		temporary = Found->getKey2();
	}
	else if ((Found->getKey3().waiting_time == value.waiting_time) && (Found->getKey3().process_name != " ")) {
		i = 2;
		temporary = Found->getKey3();
	}

	if (!help->NodeisLeaf()) {
		Node *help3 = FindSuccessor(help, temporary.waiting_time);
		if (help3->getKey1().process_name != " ") {
			i2 = 0;
		}
		else if (help3->getKey2().process_name != " ") {
			i2 = 1;
		}
		else if (help3->getKey3().process_name != " ") {
			i2 = 2;
		}

		temporary = help3->getKeys(i2);
		help->changeKeys(help3->getKeys(i2), i);
		help = help3;
		i = i2;
	}

	while (help) {

		if (help->NumberOfKeys() > 1) {
			if ((help->getKey1().waiting_time == temporary.waiting_time) && (help->getKey1().process_name != " ")) {
				help->changeKey1(NodeInfo(" ", 0, 0, 0, 0));
				help->changeMiddleLeft(help2);
				help->changeLeft(nullptr);
			}
			else if (help->getKey2().waiting_time == temporary.waiting_time) {
				if (help->getKey3().process_name != " ") {
					help->changeKey2(help->getKey3());
					help->changeKey3(NodeInfo(" ", 0, 0, 0, 0));
					if (help->getMiddleRight()) 
						help->changeMiddleLeft(help->getMiddleRight());
					if (help->getRight())
						help->changeMiddleRight(help->getRight());
					help->changeRight(nullptr);
				}
				else {
					help->changeKey2(help->getKey1());
					help->changeKey1(NodeInfo(" ", 0, 0, 0, 0));
					if (help->getMiddleLeft())
						help->changeMiddleRight(help->getMiddleLeft());
					if (help->getLeft())
						help->changeMiddleLeft(help->getLeft());
					help->changeLeft(nullptr);
				}
			}
			else if (help->getKey3().waiting_time == temporary.waiting_time) {
				help->changeKey3(NodeInfo(" ", 0, 0, 0, 0));
				help->changeMiddleRight(help2); 
				help->changeRight(nullptr);
			}
			
			return *this;
		}
		else {
			Node *tmp_new = help->getFather();
			int can = 0, flag = 0;

			if (tmp_new->getLeft() == help) {
				flag = 0;
				bro2 = nullptr;
				bro1 = tmp_new->getMiddleLeft();
			}
			else if (tmp_new->getMiddleLeft() == help) {
				flag = 1;
				bro1 = tmp_new->getMiddleRight();
				bro2 = tmp_new->getLeft();
			}
			else if (tmp_new->getMiddleRight() == help) {
				flag = 2;
				bro1 = tmp_new->getRight();
				bro2 = tmp_new->getMiddleLeft();
			}
			else if (tmp_new->getRight() == help) {
				flag = 3;
				bro2 = tmp_new->getMiddleRight();
				bro1 = nullptr;
			}

			if (bro1)
				can = bro1->NumberOfKeys() - 1;
			else
				can = 0;

			if (can) {
				help->changeKeys(tmp_new->getKeys(flag) ,1);
				int k = 0;
				if (bro1->getKey1().process_name != " ")
					k = 0;
				else if (bro1->getKey2().process_name != " ")
					k = 1;
				else if (bro1->getKey3().process_name != " ")
					k = 2;
				if (help->getMiddleRight() == help2)
					help->changeMiddleLeft(help2);
				help->changePointer(bro1->getPointer(k), 2);
				if (help->getMiddleRight())
					help->getMiddleRight()->changeFather(help);
				bro1->changePointer(nullptr, k);
				tmp_new->changeKeys(bro1->getKeys(k), flag);
				if (bro1->getKey2().process_name == bro1->getKeys(k).process_name) {
					if (bro1->getKey3().process_name != " ") {
						bro1->changeKey2(bro1->getKey3());
						bro1->changeKey3(NodeInfo(" ", 0, 0, 0, 0));
						if (bro1->getMiddleRight())
							bro1->changeMiddleLeft(bro1->getMiddleRight());
						if (bro1->getRight())
							bro1->changeMiddleRight(bro1->getRight());
						bro1->changeRight(nullptr);
					}
				}
					else
						bro1->changeKeys(NodeInfo(" ", 0, 0, 0, 0), k);
				return *this;
			}

			if (bro2)
				can = bro2->NumberOfKeys() - 1;
			else
				can = 0;

			if (can) {
				flag--;
				help->changeKeys(tmp_new->getKeys(flag), 1);
				int k = 0;
				if (bro2->getKey3().process_name != " ")
					k = 2;
				else if (bro2->getKey2().process_name != " ")
					k = 1;
				else if (bro2->getKey1().process_name != " ")
					k = 0;
				if (help->getMiddleLeft() == help2)
					help->changeMiddleRight(help2);
				help->changePointer(bro2->getPointer(k + 1), 1);
				if (help->getMiddleLeft())
					help->getMiddleLeft()->changeFather(help);
				bro2->changePointer(nullptr, k+1);
				tmp_new->changeKeys(bro2->getKeys(k), flag);

				if (bro2->getKey2().process_name == bro2->getKeys(k).process_name) {
					if (bro2->getKey1().process_name != " ") {
						bro2->changeKey2(bro2->getKey1());
						bro2->changeKey1(NodeInfo(" ", 0, 0, 0, 0));
						if (bro2->getMiddleLeft())
							bro2->changeMiddleRight(bro2->getMiddleLeft());
						if (bro2->getLeft())
							bro2->changeMiddleLeft(bro2->getLeft());
						bro2->changeLeft(nullptr);
					}
				}
				else
					bro2->changeKeys(NodeInfo(" ",0,0,0,0), k);
				return *this;
			}

			if (bro1) {
				help->changeKeys(tmp_new->getKeys(flag), 1);
				help->changeKeys(bro1->getKey2(), 2);
				temporary = tmp_new->getKeys(flag);
				help->changePointer(bro1->getPointer(1), 2);
				help->changePointer(bro1->getPointer(2), 3);
				help->changePointer(help2, 1);
				if (tmp_new->getLeft() == bro1)
					tmp_new->changeLeft(nullptr);
				else if (tmp_new->getMiddleLeft() == bro1)
					tmp_new->changeMiddleLeft(nullptr);
				else if (tmp_new->getMiddleRight() == bro1)
					tmp_new->changeMiddleRight(nullptr);
				else if (tmp_new->getRight() == bro1)
					tmp_new->changeRight(nullptr);
				delete bro1;
				bro1 = nullptr;
				if (!help->NodeisLeaf()) {
					help->getMiddleRight()->changeFather(help);
					help->getRight()->changeFather(help);
				}
				help2 = help;
				help = help->getFather();

				if (help == root) {
					if (root->NumberOfKeys() > 1) {
						if ((help->getKey1().waiting_time == temporary.waiting_time) && (help->getKey1().process_name != " ")) {
							help->changeKey1(NodeInfo(" ", 0, 0, 0, 0));
							help->changeMiddleLeft(help->getLeft());
							help->changeLeft(nullptr);
						}
						else if (help->getKey2().waiting_time == temporary.waiting_time) {
							if (help->getKey3().process_name != " ") {
								help->changeKey2(help->getKey3());
								help->changeKey3(NodeInfo(" ", 0, 0, 0, 0));
								if (help->getMiddleRight())
									help->changeMiddleLeft(help->getMiddleRight());
								if (help->getRight())
									help->changeMiddleRight(help->getRight());
								help->changeRight(nullptr);
							}
							else {
								help->changeKey2(help->getKey1());
								help->changeKey1(NodeInfo(" ", 0, 0, 0, 0));
								if (help->getMiddleLeft())
									help->changeMiddleRight(help->getMiddleLeft());
								if (help->getLeft())
									help->changeMiddleLeft(help->getLeft());
								help->changeLeft(nullptr);
							}
						}
						else if (help->getKey3().waiting_time == temporary.waiting_time) {
							help->changeKey3(NodeInfo(" ", 0, 0, 0, 0));
							help->changeMiddleRight(help->getRight());
							help->changeRight(nullptr);
						}
						//help2->changeFather(root);
						else if (root->getKey1().process_name == " ") {
							root->changeLeft(nullptr);
							if (root->getKey2().waiting_time > help2->getKey2().waiting_time)
								root->changeMiddleLeft(help2);
							else
								root->changeMiddleRight(help2);
						}
						else if (root->getKey3().process_name == " ") {
							root->changeRight(nullptr);
							if (root->getKey2().waiting_time > help->getKey2().waiting_time)
								root->changeMiddleLeft(help2);
							else
								root->changeMiddleRight(help2);
						}
					}
					else {
						root = help2;
						root->changeFather(nullptr);
						delete help;
					}
					return *this;
				}
			}
			else {
				flag--;
				help->changeKeys(tmp_new->getKeys(flag), 1);
				help->changeKeys(bro2->getKey2(), 0);
				temporary = tmp_new->getKeys(flag);
				if (flag == 2) {
					tmp_new->changePointer(help, 2);
					tmp_new->changePointer(nullptr, 3);
				}
				help->changePointer(bro2->getPointer(2), 1);
				help->changePointer(bro2->getPointer(1), 0);
				help->changePointer(help2, 2);
				if (tmp_new->getLeft() == bro2)
					tmp_new->changeLeft(nullptr);
				else if (tmp_new->getMiddleLeft() == bro2)
					tmp_new->changeMiddleLeft(nullptr);
				else if (tmp_new->getMiddleRight() == bro2)
					tmp_new->changeMiddleRight(nullptr);
				else if (tmp_new->getRight() == bro2)
					tmp_new->changeRight(nullptr);
				delete bro2;
				bro2 = nullptr;
				if (!help->NodeisLeaf()) {
					help->getLeft()->changeFather(help);
					help->getMiddleLeft()->changeFather(help);
				}
				help2 = help;
				help = help->getFather();

				if (help == root) {
					if (root->NumberOfKeys() > 1) {
						if ((help->getKey1().waiting_time == temporary.waiting_time) && (help->getKey1().process_name != " ")) {
							help->changeKey1(NodeInfo(" ", 0, 0, 0, 0));
							help->changeMiddleLeft(help->getLeft());
							help->changeLeft(nullptr);
						}
						else if (help->getKey2().waiting_time == temporary.waiting_time) {
							if (help->getKey3().process_name != " ") {
								help->changeKey2(help->getKey3());
								help->changeKey3(NodeInfo(" ", 0, 0, 0, 0));
								if (help->getMiddleRight())
									help->changeMiddleLeft(help->getMiddleRight());
								if (help->getRight())
									help->changeMiddleRight(help->getRight());
								help->changeRight(nullptr);
							}
							else {
								help->changeKey2(help->getKey1());
								help->changeKey1(NodeInfo(" ", 0, 0, 0, 0));
								if (help->getMiddleLeft())
									help->changeMiddleRight(help->getMiddleLeft());
								if (help->getLeft())
									help->changeMiddleLeft(help->getLeft());
								help->changeLeft(nullptr);
							}
						}
						else if (help->getKey3().waiting_time == temporary.waiting_time) {
							help->changeKey3(NodeInfo(" ", 0, 0, 0, 0));
							help->changeMiddleRight(help->getRight());
							help->changeRight(nullptr);
						}

						root->changePointer(help2, 2);
						help2->changeFather(root);
						root->changePointer(nullptr, 3);
					}
					else {
						root = help2;
						delete help;
					}
					return *this;
				}
			}
		}
	}		
}

void Tree::RBTreeOut() {
	struct Elem {
		Node *member;
		int position;
		Elem *next=nullptr;
		Elem(Node *mem, int pos) : member(mem) {position = pos; };
	public:
	};
	Elem *first, *last, *next_level_list, *this_level_list;
	
	if (root != nullptr) {
		first = new Elem(root, 1);
		last = first;
	}
	else {
		cout << "You can't print a tree that doesn't exist" << endl;
		return;
	}

	next_level_list = first;
	while (next_level_list) {
		next_level_list = first;
		this_level_list = next_level_list;
		next_level_list = nullptr;
		first = next_level_list;
		last = first;
		cout << "\n";
		
		while (this_level_list) {
			if (this_level_list->position == 1) {
				cout << this_level_list->member->getKey2().process_name << " (" << this_level_list->member->getKey2().waiting_time << ") (" << this_level_list->member->getKey2().time_to_complete<< ") B ";

				if (this_level_list->member->getKey1().process_name != " ") {
					if (first == nullptr) {
						first = new Elem(this_level_list->member, 0);
						last = first;
					}
					else {
						last->next = new Elem(this_level_list->member, 0);
						last = last->next;
					}
				}
				else if (this_level_list->member->getMiddleLeft() != nullptr) {
						if (first == nullptr) {
							first = new Elem(this_level_list->member->getMiddleLeft(), 1);
							last = first;
						}
						else {
							last->next = new Elem(this_level_list->member->getMiddleLeft(), 1);
							last = last->next;
						}
					}

			if (this_level_list->member->getKey3().process_name != " ") {
				if (first == nullptr) {
					first = new Elem(this_level_list->member, 2);
					last = first;
				}
				else {
					last->next = new Elem(this_level_list->member, 2);
					last = last->next;
				}
			}
					else if (this_level_list->member->getMiddleRight() != nullptr)
						if (first == nullptr) {
							first = new Elem(this_level_list->member->getMiddleRight(), 1);
							last = first;
						}
						else {
							last->next = new Elem(this_level_list->member->getMiddleRight(), 1);
							last = last->next;
						}
				}
			else {
				cout << this_level_list->member->getKeys(this_level_list->position).process_name<< " (" << this_level_list->member->getKeys(this_level_list->position).waiting_time << ") (" << this_level_list->member->getKeys(this_level_list->position).time_to_complete << ") R ";

				if ((this_level_list->member->getKey1().process_name != " ") && (this_level_list->position ==0)) {
					if (this_level_list->member->getLeft() != nullptr)
						if (first == nullptr) {
							first = new Elem(this_level_list->member->getLeft(), 1);
							last = first;
						}
						else {
							last->next = new Elem(this_level_list->member->getLeft(), 1);
							last = last->next;
						}
					if (this_level_list->member->getMiddleLeft() != nullptr) 
						if (first == nullptr) {
							first = new Elem(this_level_list->member->getMiddleLeft(), 1);
							last = first;
						}
						else {
							last->next = new Elem(this_level_list->member->getMiddleLeft(), 1);
							last = last->next;
						}
				}

				if ((this_level_list->member->getKey3().process_name != " ") && (this_level_list->position==2)) {
					if (this_level_list->member->getMiddleRight() != nullptr)
						if (first == nullptr) {
							first = new Elem(this_level_list->member->getMiddleRight(), 1);
							last = first;
						}
						else {
							last->next = new Elem(this_level_list->member->getMiddleRight(), 1);
							last = last->next;
						}
					if (this_level_list->member->getRight() != nullptr) 
						if (first == nullptr) {
							first = new Elem(this_level_list->member->getRight(), 1);
							last = first;
						}
						else {
							last->next = new Elem(this_level_list->member->getRight(), 1);
							last = last->next;
						}
				}
			}
			this_level_list = this_level_list->next;
		}
		next_level_list = first;
	}
}


void Tree::Simulation() {
	Node* tmp;
	NodeInfo KeytoDelete;
	int timeslice;

	cout << "Enter a time slice of your simulation" << endl;
	cin >> timeslice;
	tmp = root;

	while (root->NumberOfKeys()!=0) {
		while (!tmp->NodeisLeaf()) {
			if (tmp->getLeft() != nullptr)
				tmp = tmp->getLeft();
			else
				tmp = tmp->getMiddleLeft();
		}

		if (tmp->getKey1().process_name != " ")
			KeytoDelete = tmp->getKey1();
		else
			KeytoDelete = tmp->getKey2();

		if (!root->NodeisLeaf())
			*this = this->DeleteKey(KeytoDelete);
		else if (root->NumberOfKeys() > 1)
			*this = this->DeleteKey(KeytoDelete);
		else {
			root->AddWaitingTime(1, timeslice);
			root->MinusTimeLeft(1, timeslice);
			if (root->getKey2().time_to_complete < 0) {
				root->changeKey2(NodeInfo(" ", 0, 0, 0, 0));
			}
			continue;
		}
		LevelTraverse();
		KeytoDelete.execution_time += timeslice;
		KeytoDelete.time_to_complete -= timeslice;
		if (KeytoDelete.waiting_time >= KeytoDelete.max_waiting_time)
			KeytoDelete.waiting_time -= KeytoDelete.max_waiting_time;
		/*
		Node *searching = root;
		stack<Node*> s1;
		stack <NodeInfo> s2;
		s1.push(searching);
		while (!s1.empty()) {
			for (int i = 0;i < 3;i++) {
				if (searching->getKeys(i).process_name != " ") {
					searching->AddWaitingTime(i, timeslice);
					if (searching->getKeys(i).waiting_time >= searching->getKeys(i).max_waiting_time) 
						s2.push(searching->getKeys(i));
				}
			}
			for (int i = 0;i < 4;i++) {
				if (searching->getPointer(i)) {
					s1.push(searching->getPointer(i));
				}
			}
			searching = s1.top();
			s1.pop();
		}
	*/
		if (KeytoDelete.time_to_complete > 0)
			*this = this->InsertKey(KeytoDelete);
		tmp = root;
		/*
		while (!s2.empty()) {
			KeytoDelete = s2.top();
			s2.pop();
			DeleteKey(KeytoDelete);
			KeytoDelete.waiting_time -= KeytoDelete.max_waiting_time;
			InsertKey(KeytoDelete);
		}*/
	} root = nullptr;
}

Tree::~Tree() {}