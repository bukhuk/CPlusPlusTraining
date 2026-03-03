#include <threadsafe_stack.h>
#include <iostream>

int main() {
	threadsafe_stack<int> st;
	st.push(5);
	std::cout << *st.pop() << std::endl;
	return 0;
}
