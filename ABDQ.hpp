#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* array_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t curr_size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

    void resize()
    {
        capacity_ *= SCALE_FACTOR;
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

public:
    // Big 5 + Parameterized Constructor
    ABDQ() : array_(new T[1]), capacity_(1), curr_size_(0), front_(0), back_(0) {}
    explicit ABDQ(const size_t capacity) : array_(new T[capacity]), capacity_(capacity), curr_size_(0), front_(0), back_(0) {}
    ABDQ(const ABDQ& other)
    {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; ++i) {
            array_[i] = other.array_[i];
        }
        front_ = other.front_;
        back_ = other.back_;
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
        front_ = rhs.front_;
        back_ = rhs.back_;
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
        other.front_ = 0;
        other.back_ = 0;
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
        rhs.front_ = 0;
        rhs.back_ = 0;
        return *this;
    }
    ~ABDQ() noexcept
    {
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override
    {
        if (curr_size_ == capacity_) {
            resize();
        }
        for (std::size_t i = curr_size_; i > 0; --i) {
            array_[back_] = array_[i - 1];
        }
        array_[front_] = item;
        curr_size_++;
    }
    void pushBack(const T& item) override
    {
        if (curr_size_ == capacity_) {
            resize();
        }
        array_[back_] = item;
        curr_size_++;
    }

    // Deletion
    T popFront() override
    {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty");
        }
        curr_size_--;
        if (curr_size_ <= capacity_ / SCALE_FACTOR) {
            downsize();
        }
        T element = std::move(array_[front_]);
        for (std::size_t i = 1; i < curr_size_; ++i) {
            array_[i - 1] = array_[i];
        }
        return element;
    }
    T popBack() override
    {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty");
        }
        curr_size_--;
        if (curr_size_ <= capacity_ / SCALE_FACTOR) {
            downsize();
        }
        T element = std::move(array_[back_]);
        return element;
    }

    // Access
    const T& front() const override
    {
        return array_[front_];
    }
    const T& back() const override
    {
        return array_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override
    {
        return curr_size_;
    }

};
