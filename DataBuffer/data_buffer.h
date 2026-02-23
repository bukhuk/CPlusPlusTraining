#include <type_traits>
#include <cstring>
#include <stdexcept>
#include <cstdint> 
#include <utility>

template<typename T>
struct BufferView {
    T* start;
    T* finish;

    T* begin() const { return start; }
    T* end() const { return finish; }
};

class DataBuffer {
    uint8_t* data_;
    size_t size_;
    size_t capacity_;

public:
    DataBuffer() : data_{nullptr}, size_{0}, capacity_{0} {}

    explicit DataBuffer(size_t capacity) : data_{new uint8_t[capacity]}, size_{0}, capacity_{capacity} {}

    DataBuffer(const DataBuffer& other) = delete;

    DataBuffer(DataBuffer&& other) noexcept : data_{other.data_}, size_{other.size_}, capacity_{other.capacity_} {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    DataBuffer& operator=(DataBuffer& other) = delete;

    DataBuffer& operator=(DataBuffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        return *this;
    }

    template<typename T>
    void append(T value) {
        static_assert(std::is_trivial_v<T>, "Only trivial types allowed!");
        size_t new_size_ = (size_ + alignof(T) - 1) & ~(alignof(T) - 1);
        if (new_size_ + sizeof(T) > capacity_) {
            throw std::runtime_error("Buffer overflow");
        }
        size_ = new_size_;
        std::memcpy(data_ + size_, &value, sizeof(T));
        size_ += sizeof(T);
    }

    template<typename... Args>
    void append_many(Args&&... args) {
        (append(std::forward<Args>(args)), ...);
    }

    template<typename T>
    auto view_as() {
        if (size_ % sizeof(T) != 0) {
            throw std::runtime_error("Buffer has remainder");
        }

        return BufferView<T>{reinterpret_cast<T*>(data_),
                          reinterpret_cast<T*>(data_ + size_)};
    }

    ~DataBuffer() {
        delete[] data_;
    }
};
