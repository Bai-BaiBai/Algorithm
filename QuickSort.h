//
// Created by BaiZehong on 2019/5/9.
//

#ifndef ALGORITHM_QUICKSORT_H
#define ALGORITHM_QUICKSORT_H

#include "InsertionSort.h"

#include <iostream>
using namespace std;

/**
 * 快速排序
 */
namespace QuickSort{

    //三路快速排序处理 arr[l...r]
    //将arr[l...r]分为 < v ; == v; > v 三部分，之后递归的对 < v和 > v 的部分进行排序
    template <typename T>
    void __quickSort3Ways(T arr[], int l, int r){
        if (r-l <= 15){
            InsertionSort::insertionSort(arr, l, r);
            return;
        }

        //partition操作
        swap(arr[l], arr[rand()%(r-l+1) + l]);
        T e = arr[l];
        int lt = l;//arr[l+1..lt] < e
        int gt = r+1; //arr[gt...r] > e
        int i = l+1;//arr[lt+1...i) = e , i为当前要检查的元素
        while (i < gt){
            if (arr[i] < e){
                swap(arr[lt+1], arr[i]);
                lt++;
                i++;
            }else if(arr[i] > e){
                swap(arr[gt-1], arr[i]);
                gt--;
            }else{
                i++;
            }
        }
        swap(arr[l], arr[lt]);//此时arr[lt...gt) = e；arr[l...lt-1] < e
        __quickSort3Ways(arr, l, lt-1);
        __quickSort3Ways(arr, gt, r);

    }

    //三路快排
    template <typename T>
    void quickSort3Ways(T arr[], int n){
        srand(time(NULL));
        __quickSort3Ways(arr, 0, n-1);
    }

    //双路快排
    template <typename T>
    int __partition2(T arr[], int l, int r){
        swap(arr[l], arr[rand()%(r-l+1) + l]);

        T e = arr[l];
        int i = l+1, j = r;
        while (true){
            while (i <= r && arr[i] < e) i++; //这里注意不能有等于的情况，双路快排就是为了将等于的情况分散开，使两棵子树大小相近
            while (j >= l+1 && arr[j] > e) j--;
            if (i >= j) break;
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
        swap(arr[l], arr[j]);//break后，如果i=j说明arr[j]和arr[l]相等，如果j < i 此时arr[j] < arr[l] ，将arr[l]换到中间和arr[j]换

        return j;
    }

    //对arr[l...r]部分进行partition操作
    //使arr[l...r]中，arr[l...p-1] < arr[p]; arr[p+1...r] > arr[p]，返回分割点p
    template <typename T>
    int __partition(T arr[], int l, int r){

        swap(arr[l], arr[rand()%(r-l+1) + l]);//随机基准数，避免每次都选到最小的，导致成为链表

        T v = arr[l];//分区的基准数
        //arr[l+1...j] < e;  arr[j+1...i) > e; arr[i]为当前需要比较的元素
        int j = l;
        for (int i = l+1; i <= r; i++) {
            if (arr[i] < v){
                swap(arr[++j], arr[i]);
            }
        }
        swap(arr[l], arr[j]);
        return j;
    }

    template <typename T>
    void __quickSort(T arr[], int l, int r){
//        if (l >= r) return;
        if (r-l <= 15){//和归并排序一样，元素个数小于16个时，直接使用插入排序
            InsertionSort::insertionSort(arr, l, r);
            return;
        }

        int p = __partition2(arr, l, r);
        __quickSort(arr, l, p-1);
        __quickSort(arr, p+1, r);
    }

    template <typename T>
    void quickSort(T arr[], int n){
        srand(time(NULL));
        __quickSort(arr, 0, n-1);
    }
}

#endif //ALGORITHM_QUICKSORT_H
