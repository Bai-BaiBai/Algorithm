//
// Created by BaiZehong on 2019/5/8.
//

#ifndef ALGORITHM_BUBBLESORT_H
#define ALGORITHM_BUBBLESORT_H

#include <iostream>
using namespace std;

/**
 * 冒泡排序
 */
namespace BubbleSort{
    template <typename T>
    void BubbleSort(T arr[], int n){
        bool swapped;
        do{
            swapped = false;
            for (int i = 0; i < n-1; ++i) {
                if (arr[i] > arr[i+1]){
                    swap(arr[i], arr[i+1]);
                    swapped = true;
                }
            }
            n--;
        }while (swapped);
    }

    template <typename T>
    void BubbleSort2(T arr[], int n){
        int newn;
        do{
            newn = 0;
            for (int i = 0; i < n-1; ++i) {
                if (arr[i] > arr[i+1]){
                    swap(arr[i], arr[i+1]);
                    newn = i;//记录最后一次交换的位置，在此之后的元素下一轮不再扫描
                }
            }
            n = newn;
        }while (newn > 0);
    }
}

#endif //ALGORITHM_BUBBLESORT_H
