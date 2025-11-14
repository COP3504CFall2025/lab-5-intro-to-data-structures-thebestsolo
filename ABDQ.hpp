#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

    void resize()
    {
        T* new_array = new T[capacity_ * SCALE_FACTOR];
        for (size_t i = 0; i < curr_size_; ++i) {
            new_array[i] = array_[i];
        }
        delete[] array_;
        array_ = new_array;
        capacity_ *= 2;
    }

public:
    // Big 5 + Parameterized Constructor
    ABDQ() : array_(new T[1]), capacity_(1), curr_size_(0) {}
    explicit ABDQ(const size_t capacity) : array_(new T[capacity]), capacity_(capacity), curr_size_(0) {}
    ABDQ(const ABDQ& other)
    {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; ++i) {
            array_[i] = other.array_[i];
        }
    }
    ABDQ& operator=(const ABDQ& rhs)
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
    ABDQ(ABDQ&& other) noexcept
    {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }
    ABDQ& operator=(ABDQ&& rhs) noexcept
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
    ~ABDQ() noexcept override
    {
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override
    {
        if (curr_size_ == capacity_) {
            resize();
        }
        for (std::size_t i = curr_size_; i > 0; --i) {
            array_[i] = array_[i - 1];
        }
        array_[0] = item;
        curr_size_++;
    }
    void pushBack(const T& item) override
    {
        if (curr_size_ == capacity_) {
            resize();
        }
        array_[curr_size_] = item;
        curr_size_++;
    }

    // Deletion
    T popFront() override
    {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty");
        }
        T element = std::move(array_[0]);
        for (std::size_t i = 1; i < curr_size_; ++i) {
            array_[i - 1] = array_[i];
        }
        curr_size_--;
        return element;
    }
    T popBack() override
    {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty");
        }
        curr_size_--;
        T element = std::move(array_[curr_size_]);
        return element;
    }

    // Access
    const T& front() const override
    {
        return array_[0];
    }
    const T& back() const override
    {
        return array_[curr_size_ - 1];
    }

    // Getters
    std::size_t getSize() const noexcept override
    {
        return curr_size_;
    }

};
