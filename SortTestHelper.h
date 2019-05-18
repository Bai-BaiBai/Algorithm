//
// Created by BaiZehong on 2019/5/8.
//

#ifndef ALGORITHM_SORTTESTHELPER_H
#define ALGORITHM_SORTTESTHELPER_H

#include <iostream>
#include <ctime>
#include <cassert>
using namespace std;

/**
 * 测试排序算法的辅助函数
 */
namespace SortTestHelper{

    //生成随机数组，每个元素的随机范围是[rangeL,rangeR]
    int* generateRandomArray(int n, int rangeL, int rangeR){
        assert(rangeL <= rangeR);
        int *arr = new int[n];
        srand(time(NULL));
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        }
        return arr;
    }

    //打印数组
    template <typename T>
    void printArray(T arr[], int n){
        for (int i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
        return;
    }

    //检查数组是否有序
    template <typename  T>
    bool isSorted(int arr[], int n){
        for (int i = 0; i < n-1; ++i) {
            if (arr[i] > arr[i+1]) return false;
        }
        return true;
    }

    template<typename T>
    void testSort(const string &sortName, void (*sort)(T[], int), T arr[], int n) {

        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();

//        assert(isSorted(arr, n));
        cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

        return;
    }

    //拷贝数组
    int* copyIntArray(int a[], int n){
        int *arr = new int[n];
        copy(a, a+n, arr);
        return arr;
    }
};
#endif //ALGORITHM_SORTTESTHELPER_H
