#include "my_header.h"

void Queue::enqueue(Key_val item) {
	queue.add_tail(item);
}

void Queue::enqueue(string str) {
	queue.add_tail(str);
}

void Queue::enqueue(string key, string val) {
	queue.add_tail(key, val);
}

Key_val Queue::dequeue() {
	return queue.remove_head();
}

bool Queue::is_empty() {
	return queue.is_empty();
}

string Queue::to_list() {
	return queue.to_list();
}