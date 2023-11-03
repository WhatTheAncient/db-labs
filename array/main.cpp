#include <iostream>
#include "array.cpp"

int main() {
    int* my_array;
    size_t size = 5;
    
    my_array = rut::initialize_array(size);
    
    std::cout << "Array: ";
    rut::printArray(my_array, size);
    
    int minVal = rut::find_min(my_array, size);
    int maxVal = rut::find_max(my_array, size);
    
    std::cout << "Minimum: " << minVal;
    std::cout << "\nMaximum: " << maxVal;
    std::cout << "\nSorted array: ";
    rut::printArray(rut::sort(my_array, size), size);
    std::cout << std::endl;

    if (my_array != nullptr) {
      delete[] my_array;
      my_array = nullptr;
    }
    
    return 0;
}