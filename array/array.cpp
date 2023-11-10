#include <iostream>
#include <algorithm>

#pragma once

namespace rut {
  /**
   * Initializes an array with a given size and fills it from std::cin.
   *
   * @param size The size of the array.
   * @return A pointer to the dynamically allocated array.
   */
  int* initialize_array(const size_t size) {
      int* arr = new int[size];
      std::cout << "Enter " << size << " integers, separated by newlines:" << std::endl;
      for (size_t i = 0; i < size; i++) {
          if (!(std::cin >> arr[i])) {
              std::cerr << "Invalid input. Exiting." << std::endl;
              exit(1);
          }
      }
      return arr;
  }

  /**
   * Print the elements of the array.
   *
   * @param arr The array to be printed.
   * @param size The size of the array for printing.
   */
  void printArray(const int* arr, const size_t size) {
      for (size_t i = 0; i < size - 1; i++) {
          std::cout << arr[i] << ", ";
      }
      std::cout << arr[size - 1] << std::endl;
  }

  /**
   * Find the minimum value in the array.
   *
   * @param arr The array to be searched.
   * @param size The size of the array.
   * @return The minimum value in the array.
   */
  int find_min(const int* arr, const size_t size) {
      if (size == 0) {
          return 0; // Return 0 for an empty array.
      }
      int min = arr[0];
      for (size_t i = 1; i < size; i++) {
          if (arr[i] < min) {
              min = arr[i];
          }
      }
      return min;
  }

  /**
   * Find the maximum value in the array.
   *
   * @param arr The array to be searched.
   * @param size The size of the array.
   * @return The maximum value in the array.
   */
  int find_max(const int* arr, const size_t size) {
      if (size == 0) {
          return 0; // Return 0 for an empty array.
      }
      int max = arr[0];
      for (size_t i = 1; i < size; i++) {
          if (arr[i] > max) {
              max = arr[i];
          }
      }
      return max;
  }

  /**
   * Sorts array in ascending order.
   *
   * @param arr The array to be sorted.
   * @param size The size of the array.
   * @return Sorted array.
   */
  int* sort(int* arr, const size_t size) {
    if (size == 0 || size == 1 || arr == nullptr) {
      return arr;
    }

    for (size_t i = 0; i < size; i++) {
      for (size_t j = i + 1; j < size; j++) {
        if (arr[i] > arr[j]) {
          std::swap(arr[i], arr[j]);
        }
      }
    }

    return arr;
  }
}