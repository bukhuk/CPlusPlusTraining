#include <../Arena/arena.h>

#include <string_view>
#include <unordered_set>
#include <cstring>

class StringPool {
	Arena& arena_;
	std::unordered_set<std::string_view> pool_;

public:
	explicit StringPool(Arena& arena) : arena_{arena} {}

	std::string_view add(std::string_view s) {
		auto it = pool_.find(s);
		if (it != pool_.end()) return *it;

		char* mem = static_cast<char*>(arena_.alloc_raw(s.size()));
		std::memcpy(mem, s.data(), s.size());

		std::string_view result(mem, s.size());
		pool_.insert(result);
		return result;
	}
};
