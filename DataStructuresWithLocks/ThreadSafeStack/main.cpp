#include <iostream>
#include <threadsafe_stack.h>

int main() {
    threadsafe_stack<int> st;
    st.push(5);
    std::cout << *st.pop() << std::endl;
    return 0;
}
