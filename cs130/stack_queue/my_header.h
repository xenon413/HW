//did some extra stuff and small modification besides the requirement because I like coding

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;
const string PATH = "C:\\Users\\cheny\\Downloads\\Fall 2025 Test Files\\california.txt";

class Key_val {
public:
	string key, val;
	Key_val();
	Key_val(string key, string val);
};

class Linked_list {
private:
	class Node {
	public:
		Node* next = nullptr;
		Key_val item;
		Node();

		Node(string str, Node* next = nullptr, char sep = ':');

		Node(string key, string val, Node* next = nullptr);

		Node(Key_val item, Node* next = nullptr);
	};

	Node* head = nullptr, * tail = nullptr;

public:
	string about();

	Linked_list();

	void add_head(string str);
	void add_head(Key_val item);

	void add_tail(string str);
	void add_tail(Key_val item);

	string to_list();
	Key_val remove_head();
	bool is_empty();

	//extra
	void add_head(string key, string val);
	void add_tail(string key, string val);
};

class Stack {
private:
	Linked_list stack;

public:
	void push(Key_val item);
	void push(string str);
	void push(string key, string val);

	Key_val pop();
	bool is_empty();
	string to_list();
};

class Queue {
private:
	Linked_list queue;

public:
	void enqueue(Key_val item);
	void enqueue(string str);
	void enqueue(string key, string val);

	Key_val dequeue();
	bool is_empty();
	string to_list();
};

ostream& operator<<(ostream& os, const Key_val& kv);
