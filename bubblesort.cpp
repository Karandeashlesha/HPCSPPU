//Write a program to implement Parallel Bubble Sort using OpenMP. Use existing algorithms and measure the performance of sequential and parallel algorithms.
#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <omp.h>

using namespace std;

// Function to perform bubble sort
void bubbleSortSequential(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Parallel bubble sort implementation using OpenMP
void bubbleSortParallel(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        #pragma omp parallel for
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void printVector(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

int main() {
    int n = 10000; // Size of vector
    vector<int> arr(n), arr_sequential(n), arr_parallel(n);

    // Initialize arrays with random values
    srand(42);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
        arr_sequential[i] = arr[i];
        arr_parallel[i] = arr[i];
    }

    // Sequential Bubble Sort
    auto start_sequential = chrono::steady_clock::now();
    bubbleSortSequential(arr_sequential);
    auto end_sequential = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds_sequential = end_sequential - start_sequential;
    cout << "Sequential Bubble Sort: " << elapsed_seconds_sequential.count() << " seconds" << endl;

    // Parallel Bubble Sort
    auto start_parallel = chrono::steady_clock::now();
    bubbleSortParallel(arr_parallel);
    auto end_parallel = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds_parallel = end_parallel - start_parallel;
    cout << "Parallel Bubble Sort: " << elapsed_seconds_parallel.count() << " seconds" << endl;

    // Check if the parallel version is faster
    if (elapsed_seconds_parallel < elapsed_seconds_sequential) {
        cout << "Parallel Bubble Sort is faster." << endl;
    } else {
        cout << "Sequential Bubble Sort is faster." << endl;
    }

    return 0;
}
