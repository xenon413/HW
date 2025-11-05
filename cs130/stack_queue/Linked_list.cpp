#include "my_header.h"

//node construct
Linked_list::Node::Node() = default;

Linked_list::Node::Node(string str, Node* next, char sep) { 
	int pos = str.find(sep); 
	this->item = Key_val(str.substr(0, pos), str.substr(pos + 1)); 
	this->next = next; 
}

Linked_list::Node::Node(string key, string val, Node* next):item(key, val), next(next) {}

Linked_list::Node::Node(Key_val item, Node* next):item(item), next(next) {}

Linked_list::Linked_list() = default;

//remove head
Key_val Linked_list::remove_head() {
	if (is_empty()) return Key_val(); 
	Key_val res = head->item; 
	Node* temp = head; 
	head = head->next; 
	//case 1e 
	if (!head)tail = nullptr; 
	delete temp; 
	return res; 
}

// add head
void Linked_list::add_head(string str) { 
	// create node 
	head = new Node(str, head); 
	// case is empty 
	if (!tail) tail = head; 
}

void Linked_list::add_head(Key_val item) {
	head = new Node(item, head);
	if (!tail) tail = head;
}

void Linked_list::add_head(string key, string val) { 
	head = new Node(key, val, head); 
	if (!tail) tail = head; 
}

// add tail
void Linked_list::add_tail(string key, string val) { 
	// create node 
	Node* temp = new Node(key, val); 
	// case is empty 
	if (!tail) head = tail = temp; 
	// case is not empty 
	else { 
		tail->next = temp; 
		tail = temp; 
	} 
}

void Linked_list::add_tail(Key_val item) { 
	// create node 
	Node* temp = new Node(item); 
	// case is empty 
	if (!tail) head = tail = temp;
	// case is not empty 
	else { 
		tail->next = temp; 
		tail = temp; 
	} 
}

void Linked_list::add_tail(string str) { 
	// create node 
	Node* temp = new Node(str); 
	// case is empty 
	if (!tail) head = tail = temp; 
	// case is not empty 
	else { 
		tail->next = temp; 
		tail = temp; 
	} 
}

// util
string Linked_list::about() {
	return "this is a linked list";
}

bool Linked_list::is_empty() {
	return !head;
}

string Linked_list::to_list() { 
	string res = ""; 
	Node* cur = head;
	int cnt = 1; 
	while (cur != nullptr) { 
		res += to_string(cnt++) + " " + cur->item.key + cur->item.val + "\n"; 
		cur = cur->next; 
	} 
	return res; 
}
