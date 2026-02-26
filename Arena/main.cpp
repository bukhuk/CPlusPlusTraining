#include <iostream>
#include <string>
#include <list>

#include "arena_allocator.h"

int main() {
	const int iterations = 100'000;
	
	{
		auto start = std::chrono::high_resolution_clock::now();

		std::list<int> std_list;
		for (int i = 0; i < iterations; i++) {
			std_list.push_back(i);
		}

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "Standart std::list: " << diff.count() << std::endl;
	}

	{
		Arena arena(1 << 25);
		ArenaAllocator<int> alloc(arena);

		auto start = std::chrono::high_resolution_clock::now();

		std::list<int, ArenaAllocator<int>> arena_list(alloc);

		for (int i = 0; i < iterations; i++) {
			arena_list.push_back(i);
		}

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "Arena std::list: " << diff.count() << std::endl;
	}

	return 0;
}
