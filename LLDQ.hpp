#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() : list(LinkedList<T>()) {}

    // Core Insertion Operations
    void pushFront(const T& item) override
    {
        list.addHead(item);
    }
    void pushBack(const T& item) override
    {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override
    {
        if(list.getCount() == 0)
        {
            throw std::runtime_error("Empty");
        }
        T value = list.getHead()->data;
        list.removeHead();
        return value;
    }
    T popBack() override
    {
        if(list.getCount() == 0)
        {
            throw std::runtime_error("Empty");
        }
        T value = list.getTail()->data;
        list.removeTail();
        return value;
    }

    // Element Accessors
    const T& front() const override
    {
        return list.getHead()->data;
    }
    const T& back() const override
    {
        return list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override
    {
        return list.getCount();
    }

    void PrintForward() const
    {
        list.printForward();
    }

    void PrintReverse() const
    {
        list.printReverse();
    }
};






