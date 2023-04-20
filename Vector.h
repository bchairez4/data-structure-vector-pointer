/*****************************************************************************
*    Brian Chairez                                                           *
*    Goal: Manual implementation of std::vector using dynamic array pointers *
*****************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

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
        Vector(const int& capacity);
        Vector(const int& capacity, const T& data);
        Vector(Vector<T>& other);
        ~Vector();
        T& operator=(const Vector<T>& other);
        T& operator[](const int& i) const;
        T& at(const int& i) const;
        T& front() const;
        T& back() const;
        void push_front(const T& data);
        void push_back(const T& data);
        void replace(const T& replace, const T& data);
        void reverse();
        void pop_front();
        void pop_back();
        void erase(const int& i);
        void erase_elements(T& data);
        void clear();
        bool contains(const T& data) const;
        bool empty() const;
        int capacity() const;
        int size() const;
        int find(const T& data);
        int count(const T& data) const;
};

#endif
