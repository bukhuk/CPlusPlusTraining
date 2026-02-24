#include <vector>
#include <cstddef>
#include <type_traits>
#include <memory>
#include <stdexcept>

struct DestructionTask {
	void* ptr;
	void (*destroyer)(void*);
	DestructionTask* prev = nullptr;
};

class Arena {
	std::vector<std::byte> data_;
	DestructionTask* last_task_ = nullptr;
	size_t offset_ = 0;

public:
	explicit Arena(size_t size) : data_{std::vector<std::byte>(size)} {}

	template<typename T, typename... Args>
	T* alloc(Args&&... args) {
		size_t align = alignof(T);
		size_t start = (offset_ + align - 1) & ~(align - 1);

		if (start + sizeof(T) > data_.size()) {
			throw std::bad_alloc();
		}

		void* ptr = &data_[start];
		T* obj = new (ptr) T(std::forward<Args>(args)...);

		offset_ = start + sizeof(T);
		
		if constexpr (!std::is_trivially_destructible_v<T>) {
			size_t align_dt = alignof(DestructionTask);
			size_t start_dt = (offset_ + align_dt - 1) & ~(align_dt - 1);

			if (start_dt + sizeof(DestructionTask) > data_.size()) {
				obj->~T();
				throw std::bad_alloc();
			}

			DestructionTask* task = new (&data_[start_dt]) DestructionTask{
				obj,
				[](void* p) { static_cast<T*>(p)->~T(); },
				last_task_
			};

			last_task_ = task; 
			offset_ = start_dt + sizeof(DestructionTask);
		}	

		return obj;
	}

	void reset() {
		while (last_task_ != nullptr) {
			last_task_->destroyer(last_task_->ptr);
			last_task_ = last_task_->prev;
		}
		offset_ = 0;
	}

	~Arena() {
		reset();
	}
};
