#include <iostream>
#include <string>

#include "arena.h"

int main() {
	Arena arena(1024 * 1024);
	auto ptr = arena.alloc<std::string>("Hello world!");
	std::cout << *ptr << std::endl;
	return 0;
}
