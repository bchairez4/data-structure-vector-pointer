#include "Vector.h"
#include "VectorHelper.cpp"

/*****************************************************************************
    Constructors/ Destructor
*****************************************************************************/
// Default Constructor: At minimum, vector has capacity of 1.
// Time Complexity: O(N) but N is 1, so O(1)
template <class T>
Vector<T>::Vector() : capacity_(1), size_(0), array_(nullptr) {
    array_ = new T[capacity_];
}

// Set Constructor: Creates vector of specified capacity.
// Time Complexity: O(N), where N is given by the capacity
template <class T>
Vector<T>::Vector(const int& capacity) : capacity_(capacity), size_(0), array_(nullptr) {
    if (capacity_ <= 0) {
        capacity_ = 1;
    }
    array_ = new T[capacity_];
}

// Fill Constructor: Creates vector of specified capacity.
// Time Complexity: O(N), where N is given by the capacity
template <class T>
Vector<T>::Vector(const int& capacity, const T& data) : capacity_(capacity), size_(0), array_(nullptr) {
    if (capacity_ <= 0) {
        capacity_ = 1;
    }
    array_ = new T[capacity_];

    for (int i = 0; i < capacity_; ++i) {
        array_[i] = data;
        ++size_;
    }
}

// Copy Constructor: Creates a deep copy of other vector
// Time Complexity: O(N), where N is the number of elements in other
template <class T>
Vector<T>::Vector(Vector<T>& other) : capacity_(1), size_(0), array_(nullptr) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    array_ = new T[capacity_];

    deepcopy(array_, other.array_, size_);
}

// Destructor: Handles memory management upon destruction
// Time Complexity: O(N), delete[] is used
template <class T>
Vector<T>::~Vector() {
    memoryManage(array_);
    capacity_ = 1;
    size_ = 0;
}

/*****************************************************************************
    Operator Overloading
*****************************************************************************/
// Time Complexity: O(N), where N is the number of elements in other
template <class T>
T& Vector<T>::operator=(const Vector<T>& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    array_ = new T[capacity_];

    deepcopy(array_, other.array_, size_);
}

// Time Complexity: O(1)
template <class T>
T& Vector<T>::operator[](const int& i) {
    return array_[i];
}

/*****************************************************************************
    Data Modification
*****************************************************************************/
// Pushes data to the beginning of the vector, shifts the rest of the elements over
// Time Complexity: O(N), where N is the number of elements that need to be scooted over
template <class T>
void Vector<T>::push_front(const T& data) {
    if (size_ >= capacity_ - 1) {
        resize_();
    }

    T* new_array = new T[capacity_];

    //Add to the beginning and increment size counter
    new_array[0] = data;
    ++size_;

    //push front involves scooting: shift everything over by 1
    int temp_i = 1;
    for (int i = 0; i < size_; ++i) {
        new_array[temp_i] = array_[i];
        ++temp_i;
    }

    swap(array_, new_array);
    memoryManage(new_array);
}

// @param: T& data , where data is a single arbitrary element of type T
// Pushes data to the very end of the array
// Time Complexity: O(1) amortized, O(N) worst case
template <class T>
void Vector<T>::push_back(const T& data) {
    if (size_ >= capacity_ - 1) {
        resize_();
    }

    //Add to the end and increment size counter
    array_[size_] = data;
    ++size_;

}

// @param: T& replace , where replace is the object you are looking to replace
// @param: T& data , where data is the object replace is going to be replaced with
// Replaces all instances of replace found with data
// Time Complexity: O(N), where N is the number of elements in vector
template <class T>
void Vector<T>::replace(const T& replace, const T& data) {
    if (empty()) {
        std::cout << "The Vector is empty. Failed to replace()" << '\n';
        return;
    }

    for (int i = 0; i < size_; ++i) {
        if (array_[i] == replace) {
            array_[i] = data;
        }
    }
}

// Reverses the order of the vector
// Time Complexity: O(N), where N is the number of elements in the vector
template <class T>
void Vector<T>::reverse() {
    if (empty()) {
        std::cout<<"Failed to execute reverse. The vector is empty." <<'\n';
    }

    T* new_array = new T[capacity_];

    int temp_i = 0;
    for (int i = size_ - 1; i >= 0; --i) {
        new_array[temp_i] = array_[i];
        ++temp_i;
    }

    swap(array_, new_array);

    memoryManage(new_array);
}

// Deletes the first element in the array
// Time Complexity: O(N), where N is the number of elements remaining in the vector
template <class T>
void Vector<T>::pop_front() {
    if (empty()) {
        std::cout << "Failed to execute popFront. The Vector is currently empty." << '\n';
        return;
    }

    T* new_array = new T[capacity_];

    //Copy everything except the first element
    int temp_i = 1;
    for (int i = 0; i < size_; ++i) {
        new_array[i] = array_[temp_i];
        ++temp_i;
    }

    //Decrement size to reflect change
    --size_;

    swap(array_, new_array); 
    memoryManage(new_array);
}

// Deletes the last element in the array
// Time Complexity: O(N), where N is the number of elements remaining in the vector
template <class T>
void Vector<T>::pop_back() {
    if (empty()) {
        std::cout << "Failed to execute popBack. The Vector is currently empty." << '\n';
        return;
    }
    
    T* new_array = new T[capacity_];

    //Copy everything except the last element
    int updated_size = size_ - 1;
    deepcopy(new_array, array_, updated_size);

    //reflect change to size
    size_ = updated_size;

    swap(array_, new_array); 
    memoryManage(new_array);
}

// Time Complexity: O(N), where N is the number of elements remaining in the vector
template <class T>
void Vector<T>::erase(const int& i_loc) {
    if (empty()) {
        std::cout << "The Vector is empty. Failure to erase()" << '\n';
        return;
    }

    //if youre just trying to get rid of the front or back take advantage of already written functions
    if (i_loc == size_ - 1) {
        pop_back();
        return;
    }
    else if (i_loc == 0) {
        pop_front();
        return;
    }

    //else manually go through array and delete the element
    T* temp_array = new T[capacity_];
    int temp_i = 0;

    for (int i = 0; i < size_; ++i) {
        if (i == i_loc) {
            ++temp_i;
            --size_;
        }

        temp_array[i] = array_[temp_i];
        ++temp_i;
    }
    
    swap(array_, temp_array);
    memoryManage(temp_array);
}

// @param: T& data , where data is the object within the vector you want to erase 
// Goes thorugh vector, deletes all instances of specified data
// Time Complexity: O(N), where N is the number of elements in the vector
template <class T>
void Vector<T>::erase_elements(T& data) {
    if (empty()) {
        std::cout << "Failed to execute erasure. Vector is empty." << '\n';
        return;
    }

    T* new_array = new T[capacity_];
    int temp_size = size_;  //keeps track of deletions
    int temp_i = 0;         //postional counter to help with skipping in for loop

    //The 'deleting' process is actually just skipping when refilling into new array
    for (int i = 0; i < size_; ++i) {
        
        // If you find what you want to delete, 'skip' it, reflect size change
        if (array_[i] == data) {
            ++temp_i;
            --temp_size;
        }

        new_array[i] = array_[temp_i];
        ++temp_i;       //increment with i
    }

    //Update size to reflect deletions.
    size_ = temp_size;

    swap(array_, new_array);
    memoryManage(new_array);
}

// Deletes current vector, resets to default: capacity 1 and size 0
// Time Complexity: O(N), delete[] used
template <class T>
void Vector<T>::clear() {
    if (empty()) {
        return;
    }

    memoryManage(array_);
    size_ = 0;
    capacity_ = 1;
    array_ = new T[capacity_];

}

/*****************************************************************************
    Data Accessing
*****************************************************************************/
// Time Complexity: O(1)        !!WARNING: UNDEFINED BEHAVIOR IF USED WHEN EMPTY
template <class T>
T& Vector<T>::at(const int& i) {
    return array_[i];
}

// Time Complexity: O(1)        !!WARNING: UNDEFINED BEHAVIOR IF USED WHEN EMPTY
template <class T>
T& Vector<T>::front() const{
    return array_[0];
}

// Time Complexity: O(1)        !!WARNING: UNDEFINED BEHAVIOR IF USED WHEN EMPTY
template <class T>
T& Vector<T>::back() const{
    return array_[size_ - 1];
}

/*****************************************************************************
    Data Observation
*****************************************************************************/
// Searches array to see if data is in, boolean return
// Time Complexity: O(N), where N is the number of elements in the vector
template <class T>
bool Vector<T>::contains(const T& data) const {
    if (empty()) {
        return false;
    }

    for (int i = 0; i < size_; ++i) {
        if (array_[i] == data) {
            return true;
        }
    }
    
    return false;
}

// Time Complexity: O(1)
template <class T>
bool Vector<T>::empty() const {
    return size_ == 0;
}

// Time Complexity: O(1)
template <class T>
int Vector<T>::capacity() const {
    return capacity_;
}

// Time Complexity: O(1)
template <class T>
int Vector<T>::size() const {
    return size_;
}

// Searches array to find first occurence of data, returns -1 if not found
// Time Complexity: O(N), where N is the number of elements in the vector
template <class T>
int Vector<T>::find(const T& data) {
    return search(array_, size_, data);
}

// Counts the number of times a certain element appears in the array
// Time Complexity: O(N), where N is the number of elements in the vector
template <class T>
int Vector<T>::count(const T& data) const {
    if (empty()) {
        std::cout << "The Vector is empty. Failed to perform count" << '\n';
        return 0;
    }
    int count = 0;

    for (int i = 0; i < size_; ++i) {
        if (array_[i] == data) {
            ++count;
        }
    }

    return count;
}

/*****************************************************************************
    Private Functions
*****************************************************************************/
// Dynamically doubles capacity of existing array
// Time Complexity: O(N), where N is the number of elements being copied over
template <class T>
void Vector<T>::resize_() {
    capacity_ *= 2;
    
    T* new_array = new T[capacity_];
    deepcopy(new_array, array_, size_);
    swap(array_, new_array);
    memoryManage(new_array);
}

// shrinks array to fit current size
// Time Complexity: O(N), where N is the number of elements being copied over
template <class T>
void Vector<T>::shrink_() {
    if (empty()) {
        std::cout << "Failed to execute shrinking. Vector is empty" << '\n';
        return;
    }

    if (size_ == capacity_) {
        std::cout << "Already shrunk enough." << '\n';
        return;
    }

    //Update capacity: shrink_s to size
    capacity_ = size_;
    T* shrunk_array = new T[capacity_];

    deepcopy(shrunk_array, array_, size_);
    swap(array_, shrunk_array);

    memoryManage(shrunk_array);

}