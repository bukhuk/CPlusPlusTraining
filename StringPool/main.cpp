#include <iostream>

#include "string_pool.h"

int main() {
	Arena arena(1024);
	StringPool pool(arena);

	auto s1 = pool.add("hello");
	auto s2 = pool.add("hello");
	auto s3 = pool.add("world");

	if (s1.data() == s2.data()) {
        std::cout << "Interning works!\n";
    }

	if (s1 != s3) {
        std::cout << "Different strings handled.\n";
    }

	return 0;
}
