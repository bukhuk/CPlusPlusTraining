#include <iostream>

#include "static_string.h"

int main() {
	constexpr StaticString s1 = "Hello";
	constexpr StaticString s2 = " world";
	constexpr auto res = s1 + s2;

	static_assert(res.size() == 11);
	static_assert(res[0] == 'H');
	static_assert(res[6] == 'w');

	std::cout << res.c_str() << std::endl;
	
	return 0;
}
