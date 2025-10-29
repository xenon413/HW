#include "my_header.h"

void Stack::push(Key_val item) {
	stack.add_head(item);
}

void Stack::push(string str) {
	stack.add_head(str);
}

void Stack::push(string key, string val) {
	stack.add_head(key, val);
}

Key_val Stack::pop() {
	return stack.remove_head();
}

bool Stack::is_empty() {
	return stack.is_empty();
}

string Stack::to_list() {
	return stack.to_list();
}