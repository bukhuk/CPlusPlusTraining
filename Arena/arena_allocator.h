#include <arena.h>

template <typename T>
class ArenaAllocator {
	Arena* arena_;

public:
	using value_type = T;
	
	explicit ArenaAllocator(Arena& arena) : arena_{&arena} {}

	template <typename U>
	ArenaAllocator(const ArenaAllocator<U>& other) : arena_{other.arena_} {}

	T* allocate(size_t n) {
		return static_cast<T*>(arena_->alloc_raw(n * sizeof(T), alignof(T)));
	}

	void deallocate(T* p, size_t n) noexcept {}

	template <typename U> friend class ArenaAllocator;	
};
