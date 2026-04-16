#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <iomanip>
using namespace std;

/* -------------------------------------------------
   Utility Function: Generate Large Random Array
--------------------------------------------------*/
void generateRandomArray(vector<int> &arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

/* -------------------------------------------------
   Sequential Bubble Sort
--------------------------------------------------*/
void sequentialBubbleSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

/* -------------------------------------------------
   Parallel Bubble Sort (Odd-Even Transposition)
--------------------------------------------------*/
void parallelBubbleSort(vector<int> &arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            #pragma omp parallel for
            for (int j = 0; j < n - 1; j += 2) {
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
            }
        } else {
            #pragma omp parallel for
            for (int j = 1; j < n - 1; j += 2) {
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
            }
        }
    }
}

/* -------------------------------------------------
   Merge Function
--------------------------------------------------*/
void merge(vector<int> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

/* -------------------------------------------------
   Sequential Merge Sort
--------------------------------------------------*/
void sequentialMergeSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/* -------------------------------------------------
   Parallel Merge Sort (OpenMP Tasks)
--------------------------------------------------*/
void parallelMergeSort(vector<int> &arr, int left, int right, int depth = 0) {
    if (left < right) {
        int mid = (left + right) / 2;

        if (depth <= 4) {  // limit task creation depth
            #pragma omp task
            parallelMergeSort(arr, left, mid, depth + 1);

            #pragma omp task
            parallelMergeSort(arr, mid + 1, right, depth + 1);

            #pragma omp taskwait
        } else {
            sequentialMergeSort(arr, left, mid);
            sequentialMergeSort(arr, mid + 1, right);
        }

        merge(arr, left, mid, right);
    }
}

/* -------------------------------------------------
   MAIN FUNCTION
--------------------------------------------------*/
int main() {
    int n = 20000;  // Large input (>1000)
    srand(time(0));

    vector<int> arr1(n), arr2(n), arr3(n), arr4(n);

    generateRandomArray(arr1, n);
    arr2 = arr1;
    arr3 = arr1;
    arr4 = arr1;

    double start, end;
    double bubbleSeqTime, bubbleParTime, mergeSeqTime, mergeParTime;

    // Sequential Bubble Sort
    start = omp_get_wtime();
    sequentialBubbleSort(arr1);
    end = omp_get_wtime();
    bubbleSeqTime = end - start;
    cout << "Sequential Bubble Sort Time: " 
         << bubbleSeqTime << " seconds\n";

    // Parallel Bubble Sort
    start = omp_get_wtime();
    parallelBubbleSort(arr2);
    end = omp_get_wtime();
    bubbleParTime = end - start;
    cout << "Parallel Bubble Sort Time: " 
         << bubbleParTime << " seconds\n";
    cout << "Bubble Sort Speedup: " 
         << fixed << setprecision(2) << (bubbleSeqTime / bubbleParTime) << "x\n\n";

    // Sequential Merge Sort
    start = omp_get_wtime();
    sequentialMergeSort(arr3, 0, n - 1);
    end = omp_get_wtime();
    mergeSeqTime = end - start;
    cout << "Sequential Merge Sort Time: " 
         << mergeSeqTime << " seconds\n";

    // Parallel Merge Sort
    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        parallelMergeSort(arr4, 0, n - 1);
    }
    end = omp_get_wtime();
    mergeParTime = end - start;
    cout << "Parallel Merge Sort Time: " 
         << mergeParTime << " seconds\n";
    cout << "Merge Sort Speedup: " 
         << fixed << setprecision(2) << (mergeSeqTime / mergeParTime) << "x\n";

    return 0;
}