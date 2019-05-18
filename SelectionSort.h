//
// Created by BaiZehong on 2019/5/8.
//

#ifndef ALGORITHM_SELECTIONSORT_H
#define ALGORITHM_SELECTIONSORT_H

/**
 * 选择排序
 */
namespace SelectionSort{
    template <typename T>
    void selectionSort(T arr[], int n) {
        for (int i = 0; i < n; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (arr[j] < arr[minIndex]) minIndex = j;
            }
            swap(arr[minIndex], arr[i]);
        }
    }
}

#endif //ALGORITHM_SELECTIONSORT_H
