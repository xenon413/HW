#include<iostream>
#include<fstream>
#include<string>
using namespace std;
const string PATH = "my_test.txt";


class LinkedList {
private:

	class Node {
	public:
		Node* next = nullptr;
		string val = "";

		Node(string val, Node* next) {
			this->val = val;
			this->next = next;
		}

		Node(string val) {
			this->val = val;
		}

	};

	Node* head = nullptr;
	Node* tail = nullptr;
public:
	string about() {
		return "written by Chen Wang";
	}

	void add_head(string value) {
		// create node
		head = new Node(value, head);

		// case is empty
		if (!tail) tail = head;
	}

	void add_tail(string value) {
		// create node
		Node* temp = new Node(value);

		// case is empty
		if (!tail) head = tail = temp;

		// is is not empty
		else {
			tail->next = temp;
			tail = temp;
		}
	}

	bool is_empty() {
		return head == nullptr;
	}

	string to_list() {
		string res = "";
		Node* cur = head;
		int cnt = 1;

		while (cur != nullptr) {
			res += to_string(cnt++) + " " + cur->val + "\n";
			cur = cur->next;
		}
		return res;
	}
};

void testing(string path) {
	// create linked list
	LinkedList list1 = LinkedList(), list2 = LinkedList();

	// import file
	fstream file(path);

	// if open
	if (!file) {
		cout << "Error opening file!\n";
		return;
	}


	string line;
	// read line
	while (getline(file, line)) {
		// add nodes
		list1.add_head(line);
		list2.add_tail(line);
	}

	file.close();
	cout << list1.to_list() + "\n";
	cout << list2.to_list() + "\n";

}

int main() {
	testing(PATH);
}
