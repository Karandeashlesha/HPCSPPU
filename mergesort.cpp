#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <omp.h>

using namespace std;

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortSequential(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSortParallel(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortParallel(arr, l, m);
            #pragma omp section
            mergeSortParallel(arr, m + 1, r);
        }

        merge(arr, l, m, r);
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

    // Sequential Merge Sort
    auto start_sequential = chrono::steady_clock::now();
    mergeSortSequential(arr_sequential, 0, n - 1);
    auto end_sequential = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds_sequential = end_sequential - start_sequential;
    cout << "Sequential Merge Sort: " << elapsed_seconds_sequential.count() << " seconds" << endl;

    // Parallel Merge Sort
    auto start_parallel = chrono::steady_clock::now();
    mergeSortParallel(arr_parallel, 0, n - 1);
    auto end_parallel = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds_parallel = end_parallel - start_parallel;
    cout << "Parallel Merge Sort: " << elapsed_seconds_parallel.count() << " seconds" << endl;

    // Check if the parallel version is faster
    if (elapsed_seconds_parallel < elapsed_seconds_sequential) {
        cout << "Parallel Merge Sort is faster." << endl;
    } else {
        cout << "Sequential Merge Sort is faster." << endl;
    }

    return 0;
}
