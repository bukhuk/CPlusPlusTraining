#include <array>
#include <string_view>

template <size_t N>
struct StaticString {
	char data[N]{};
	size_t length = N - 1;

	constexpr StaticString(const char (&str)[N]) {
		for (size_t i = 0; i < N; i++) {
			data[i] = str[i];
		}
	}

	constexpr StaticString() = default;
	
	constexpr char operator[](size_t i) const { return data[i]; }
	constexpr size_t size() const { return length; }
	constexpr const char* c_str() const { return data; }
};

template <size_t N>
StaticString(const char (&str)[N]) -> StaticString<N>;

template <size_t N, size_t M>
constexpr auto operator+(StaticString<N> lhs, StaticString<M> rhs) {
	StaticString<N + M - 1> result;
	
	for (size_t i = 0; i < N - 1; i++) {
		result.data[i] = lhs[i];
	}

	for (size_t i = 0; i < M; i++) {
		result.data[N + i - 1] = rhs[i];
	}

	return result;
}
