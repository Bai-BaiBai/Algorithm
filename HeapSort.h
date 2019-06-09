// 堆排序
// Created by BaiZehong on 2019/6/9.
//

#ifndef ALGORITHM_HEAPSORT_H
#define ALGORITHM_HEAPSORT_H

#include "MaxHeap.h"

//堆排序
// O(nlogn)
// 总体时间复杂度不如归并和快排，适用于动态维护的排序
namespace HeapSort{
    template <typename T>

    //第1版，逐个将元素插入到堆中，然后出堆
    void heapSort1(T arr[], int n){
        MaxHeap<T> maxHeap = MaxHeap<T>(n);
        for (int i = 0; i < n; ++i) {
            maxHeap.insert(arr[i]);//时间复杂度是O(nlogn)
        }
        //由小到大排列
        for (int j = n-1; j >= 0 ; ++j) {
            arr[j] = maxHeap.gatMax();
        }
    }

    //第2版，优化插入操作，将数组直接作为一个堆
    //从最后一个非叶子节点开始遍历，检查是否大于它的孩子节点，否则进行shiftDown
    //只需要遍历一半的元素即可完成heapify（因为最后一个非叶子节点的下标是 n/2）
    //   因为需要使用到内部函数，新增加一个构造函数接收一个数组为参，完成该方法
    void heapSort2(T arr[], int n){
        MaxHeap<T> maxHeap = MaxHeap<T>(arr, n);//heapify时间复杂度是O(n)级别，额外的空间为O(n)
        for (int j = n-1; j >= 0 ; ++j) {
            arr[j] = maxHeap.gatMax();
        }
    }

    //将arr数组在[i..n)范围内对第i个元素shiftDown操作
    void __shiftDown(T arr[], int n, int i){
        while (i*2+1 < n){//从0索引
            int j = i*2+1;
            if (j+1 < n && arr[j+1] > arr[j]){
                j ++;
            }
            if (arr[i] >= arr[j]) break;
            swap(arr[i], arr[j]);
            i = j;
        }
    }

    //原地堆排序，空间复杂度降到O(1)，直接使用arr数组
    //从0开始存储，下标表示：left(i*2 +1),  right(i*2+2),  parent( (i-1)/2 )
    void heapSort3(T arr[], int n){
        //heapify
        for (int i = (n-1)/2; i >= 0 ; i--) {
            __shiftDown(arr, n, i);
        }
        //翻转，因为是最大堆，返回数组需要是从小到大排序
        for (int j = n-1; j > 0; j--) {
            swap(arr[0], arr[j]);//将当前最大的元素放置到合适的位置
            __shiftDown(arr, j, 0);//每一轮将arr[0]放置到合适的位置，也就是选出当前数组中最大的元素。要注意每次都要排除掉末尾一个元素
        }
    }

}
#endif //ALGORITHM_HEAPSORT_H
