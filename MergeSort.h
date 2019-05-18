//
// Created by BaiZehong on 2019/5/9.
//

#ifndef ALGORITHM_MERGESORT_H
#define ALGORITHM_MERGESORT_H

#include "InsertionSort.h"

/**
 * 归并排序
 */
namespace MergeSort{

    //对arr[l...mid]和arr[mid+1...r]两部分合并
    template <typename T>
    void __merge(T arr[], int l, int mid, int r){
        T aux[r-l+1]; //作为辅助数组，方便比较
        for (int i = l; i <= r; ++i) {
            aux[i-l] = arr[i];//因为aux数组有l的偏移量，所以减去l
        }
        int i = l, j = mid+1;
        for (int k = l; k <= r; ++k) {

            if(i > mid){ //前两步判断索引合法性
                arr[k] = aux[j-l];
                j++;
            }else if(j > r){
                arr[k] = aux[i-l];
                i++;
            }else if(aux[i-l] < aux[j-l]){
                arr[k] = aux[i-l];
                i++;
            }else{
                arr[k] = aux[j-l];
                j++;
                // if(aux[i-1] > aux[j-1]) count += mid+1-i  count为逆序对的数量
            }
        }
    }

    template <typename T>
    void __mergeSort(T arr[], int l, int r){
//        if (l >= r) return;
        if (r-l <= 15){//当数组元素少于等于16个时，直接用插入排序，n小时O(n^2)比O(nlogn)快
            InsertionSort::insertionSort(arr, l, r);
            return;
        }

        int mid = (l+r)/2;
        __mergeSort(arr, l, mid);
        __mergeSort(arr, mid+1, r);
        if (arr[mid] > arr[mid+1]) {//对归并排序优化，如果这两个部分已经有序则不用再进行merge操作
            __merge(arr, l, mid, r); //对两个排好序的子数组进行合并
        }
    }

    //对数组[l...r]进行归并排序
    template <typename T>
    void mergeSort(T arr[], int n){
        __mergeSort(arr, 0, n-1);
    }

    template <typename T>
    void mergeSortBU(T arr[], int n){//自底向上的进行归并排序
        //第一次每个元素作为一个子数组，下一次size*2个元素作为一个子数组，直到合并成一个数组为止
        for (int size = 1; size <= n; size += size) {
            //每两个size的数组合并成一个数组，即i+size-1作为mid，合并后的数组[0,size*2-1],[size*2,size*4-1]....[,n-1]
            for (int i = 0; i+size < n; i += size+size) {
                if (arr[i+size-1] > arr[i+size]) {//如果arr[mid]是小于arr[mid+1]的那么就没必要进行合并了
                    __merge(arr, i, i + size - 1, min(i + size + size - 1, n - 1));
                }
            }
        }
    }
}

#endif //ALGORITHM_MERGESORT_H
