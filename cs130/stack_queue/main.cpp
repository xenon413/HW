#include "my_header.h"

vector<string> read_file(string path) {
	fstream file(path);
	vector<string>res;
	if (!file) {
		cout << "Error opening file!\n";
		return res;
	}

	// read line
	string line;

	while (getline(file, line)) {
		res.push_back(line);
	}

	file.close();
	return res;
}

void linked_list_test(vector<string> vec) {
	cout << "linked list test:\n";
	Linked_list list1, list2;

	// read line
	for(string i: vec) {
		// add nodes
		list1.add_head(i);
		list2.add_tail(i);
	}

	cout << list1.to_list() + "\n";
	cout << list2.to_list() + "\n";

}
void stack_queue_load1(Stack& s, Queue& q, vector<string>vec) {


	for (string i : vec) {
		s.push(i);
		q.enqueue(i);
	}

}

void stack_queue_load2(Stack& s, Queue& q, vector<string>vec) {

	for (string i : vec) {
		int pos = i.find(':');
		string key = i.substr(0, pos);
		string val = i.substr(pos + 1);
		s.push(key, val);
		q.enqueue(key, val);
	}

}

void stack_queue_load3(Stack& s, Queue& q, vector<string>vec) {
	for (string i : vec) {
		int pos = i.find(':');
		Key_val item = Key_val(i.substr(0, pos), i.substr(pos + 1));
		s.push(item);
		q.enqueue(item);
	}

}
void stack_queue_test(Stack s, Queue q) {

	//dequeue
	cout << "clear queue (dequeue all):\n";
	while (!q.is_empty()) {
		cout << q.dequeue()<<"\n";
	}

	//pop
	cout << "\nclear stack (pop all):\n";
	while (!s.is_empty()) {
		cout << s.pop() << "\n";
	}

	// add
	cout << "\nmanual add key val test1 to test5...\n";
	Key_val test1 = Key_val("test1_key", "test1_val");
	Key_val test2 = Key_val("test2_key", "test2_val");
	Key_val test3 = Key_val("test3_key", "test3_val");
	Key_val test4 = Key_val("test4_key", "test4_val");
	Key_val test5 = Key_val("test5_key", "test5_val");

	s.push(test1);
	s.push(test2);
	s.push(test3);
	s.push(test4);
	s.push(test5);

	q.enqueue(test1);
	q.enqueue(test2);
	q.enqueue(test3);
	q.enqueue(test4);
	q.enqueue(test5);

	//dequeue
	cout << "clear queue (dequeue all):\n";
	while (!q.is_empty()) {
		cout << q.dequeue() << "\n";
	}

	//pop
	cout << "\nclear stack (pop all):\n";
	while (!s.is_empty()) {
		cout << s.pop() << "\n";
	}

}


int main() {
	vector<string> vec = read_file(PATH);
	//linked_list_test(vec);
	Stack s1, s2, s3;
	Queue q1, q2, q3;
	//check all loads

	stack_queue_load1(s1, q1, vec);
	stack_queue_load2(s2, q2, vec);
	stack_queue_load3(s3, q3, vec);

	if (s1.to_list() == s2.to_list() && s2.to_list() == s3.to_list() && q1.to_list() == q2.to_list() && q2.to_list() == q3.to_list())
		cout << "all loads are the same\n\n";
	else
		cout << "error: loads aren't all the same\n\n";

	cout << "stack:\n" + s1.to_list()+"\n";
	cout << "queue:\n" + q1.to_list() + "\n";

	stack_queue_test(s1, q1);
}