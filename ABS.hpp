#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : array_(new T[1]), capacity_(1), curr_size_(0) {}
    explicit ABS(const size_t capacity) : array_(new T[capacity]), capacity_(capacity), curr_size_(0) {}
    ABS(const ABS& other)
    {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; ++i) {
            array_[i] = other.array_[i];
        }
    }
    ABS& operator=(const ABS& rhs)
    {
        if (this == &rhs) {
            return *this;
        }
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; ++i) {
            array_[i] = rhs.array_[i];
        }
        return *this;
    }
    ABS(ABS&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_)
    {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }
    ABS& operator=(ABS&& rhs) noexcept
    {
        if (this == &rhs) {
            return *this;
        }
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;
        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        return *this;
    }
    ~ABS() noexcept
    {
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override
    {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept
    {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept
    {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override
    {
        if (curr_size_ >= capacity_) {
            resize();
        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override
    {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty");
        }
        return array_[curr_size_ - 1];
    }

    T pop() override
    {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty");
        }
        curr_size_--;
        if (curr_size_ * 4 <= capacity_ && curr_size_ > 0) {
            downsize();
        }
        T element = std::move(array_[curr_size_]);
        return element;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

    void resize()
    {
        capacity_ *= scale_factor_;
        T* new_array = new T[capacity_];
        for (size_t i = 0; i < curr_size_; ++i) {
            new_array[i] = array_[i];
        }
        delete[] array_;
        array_ = new_array;
    }
    
    void downsize()
    {
        capacity_ /= scale_factor_;
        T* new_array = new T[capacity_];
        for (size_t i = 0; i < curr_size_; ++i) {
            new_array[i] = array_[i];
        }
        delete[] array_;
        array_ = new_array;
    }
};
