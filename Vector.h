/*****************************************************************************
*    Brian Chairez                                                           *
*    Goal: Manual implementation of std::vector using dynamic array pointers *
*    Progess: Basic implementation and functions are complete                *
*****************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template <class T>
class Vector{
    private:
        int capacity_;
        int size_;
        T* array_;

        void resize_();
        void shrink_();
    public:
        Vector();
        Vector(int& capacity);
        Vector(int& capacity, T& data);
        Vector(Vector<T>& other);
        ~Vector();
        T& operator=(const Vector<T>& other);
        T& operator[](const int& i);
        void push_front(T& data);
        void push_back(T& data);
        T& at(int& i);
        T& front();
        T& back();
        void replace(T& replace, T& data);
        void reverse();
        void pop_front();
        void pop_back();
        void erase(const int& i);
        void erase_elements(T& data);
        void clear();
        bool contains(T& data);
        bool empty() const;
        int capacity() const;
        int size() const;
        int find(T& data);
        int count(T& data);
        void print();
};

#endif
