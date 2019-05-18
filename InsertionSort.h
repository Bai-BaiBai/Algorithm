//
// Created by BaiZehong on 2019/5/8.
//

#ifndef ALGORITHM_INSERTIONSORT_H
#define ALGORITHM_INSERTIONSORT_H

#include <iostream>

using namespace std;

/**
 * 插入排序
 */
namespace InsertionSort{
    template <typename T>
    void insertionSort(T arr[], int n){
        for (int i = 1; i < n; ++i) {
            T e = arr[i];//存放每一次内层循环要插入的元素
            int j;//保存元素e应该插入的位置
            for (j = i; j > 0 && e < arr[j-1]; j--) {//元素和前一个比，如果小于就将前一个元素向后移
                arr[j] = arr[j-1];
            }
            arr[j] = e;
        }
        return;
    }

    template <typename T>
    void insertionSort(T arr[], int l, int r){
        for (int i = l+1; i <= r; ++i) {
            T e = arr[i];
            int j;
            for (j = i; j > l && e < arr[j-1]; j--) {
                arr[j] = arr[j-1];
            }
            arr[j] = e;
        }
        return;
    }
}

#endif //ALGORITHM_INSERTIONSORT_H
