#include <iostream>
#include "data_buffer.h"

int main() {
	DataBuffer buffer(256);
	buffer.append_many(1, 2, 3, 4, 5);

	BufferView bv = buffer.view_as<int>();

	auto it = bv.begin();
	while (it != bv.end()) {
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;

	return 0;
}
