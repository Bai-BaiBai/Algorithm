//
// Created by BaiZehong on 2019/5/8.
//

#ifndef ALGORITHM_SHELLSORT_H
#define ALGORITHM_SHELLSORT_H

#include "InsertionSort.h"

/**
 * 希尔排序
 */
namespace ShellSort{
    template <typename T>
    void shellSort(T arr[], int n){

        int gap = 1;
        while( gap < n/3 )
            gap = 3 * gap + 1;
        do {
            for (int i = gap; i < n; i++) {
                T e = arr[i];
                int j;
                for (j = i; j >= gap && e < arr[j - gap]; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = e;
            }
            gap = gap/3;
        }while (gap > 0);
    }
}

#endif //ALGORITHM_SHELLSORT_H
