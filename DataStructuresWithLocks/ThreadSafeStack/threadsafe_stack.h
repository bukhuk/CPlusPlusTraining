#include <exception>
#include <mutex>
#include <stack>

struct empty_stack : std::exception {
    const char *what() const noexcept override {
        return "Stack is empty";
    }
};

template <typename T> class threadsafe_stack {
    std::stack<T> data_;
    mutable std::mutex m;

  public:
    threadsafe_stack() {}

    threadsafe_stack(const threadsafe_stack &other) {
        std::lock_guard<std::mutex> lock(other.m);
        data_ = other.data_;
    }

    threadsafe_stack &operator=(const threadsafe_stack &other) = delete;

    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        data_.push(std::move(new_value));
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if (data_.empty())
            throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data_.top())));
        data_.pop();
        return res;
    }

    void pop(T &value) {
        std::lock_guard<std::mutex> lock(m);
        if (data_.empty())
            throw empty_stack();
        value = std::move(data_.top());
        data_.pop();
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(m);
        return data_.empty();
    }
};
