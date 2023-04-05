/*****************************************************************************
    Helper Functions: DRY(Don't Repeat Yourself) 
*****************************************************************************/
// Copies the contents from array2 to array1 given a size
template <class T>
void deepcopy(T* &array1, T* &array2, int& size) {
    for (size_t i = 0; i < size; ++i) {
        array1[i] = array2[i];
    }
}

// Deletes array and sets array ptr to null
template <class T>
void memoryManage(T* &array) {
    delete [] array;
    array = nullptr;
}

// Searches a given array for a specified element, returns i location of first occurence of element
template <class T>
int search(T* &array, int& size, T& data) {
    int i_loc = -1;

    for (int i = 0; i < size; ++i) {
        if (array[i] == data) {
            return i;
        }
    }

    return i_loc;
}

// Swaps pointers between two arrays
template <class T>
void swap(T* &array1, T* &array2) {
    T* temp_array_ptr = array1;
    array1 = array2;
    array2 = temp_array_ptr;
    temp_array_ptr = nullptr;
}

