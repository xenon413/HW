#include "my_header.h"

Key_val::Key_val() = default;

Key_val::Key_val(string key, string val) {
	this->key = key;
	this->val = val;
}

ostream& operator<<(ostream& os, const Key_val& kv) {
	os << kv.key << ":" << kv.val;
	return os;
}