//
// 最小堆
// Created by BaiZehong on 2019/6/8.
//

#ifndef ALGORITHM_MINHEAP_H
#define ALGORITHM_MINHEAP_H
#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;

template <typename Item>
class MinHeap {

private:
    Item *data;
    int count;
    int capacity;
    void shiftUp(int k){
        //插入的元素不为根节点，且值小于父节点时，上浮
        while (k > 1 && data[k] < data[k/2]){
            swap(data[k], data[k/2]);
            k /= 2;
        }
    }

    // k为要下沉元素的下标，当前k有孩子且孩子中的最大元素大于data[k]时才进行下沉
    void shiftDown(int k){
        while (k <= count/2){
            int j = k*2;
            //先判断右孩子是否存在，在比较左孩子和右孩子的大小
            if (j+1 <= count && data[j+1] < data[j]) j++;
            //j存储的是左右孩子中，大的元素的下标
            if (data[k] <= data[j]){ //此时说明下沉完成
                return;
            }
            swap(data[k], data[j]);
            k = j;
        }
    }
public:
    MinHeap(int capacity){
        data = new Item[capacity+1];//从索引1开始存储
        count = 0;//存储该堆中的元素个数
        this -> capacity = capacity;
    }

    //将一个数组heapify
    MinHeap(Item arr[], int n){
        data = new Item[n+1];
        capacity = n;
        for (int i = 0; i < n; ++i) {
            data[i+1] = arr[i];
        }
        count = n;
        for (int j = count/2; j > 0 ; j--) {//从最后一个非叶子节点开始，向前逐个进行shiftDown操作
            shiftDown(data[j]);
        }
    }

    ~MinHeap(){
        delete [] data;
    }

    int size(){ return count;}
    bool isEmpty(){ return count == 0;}
    void insert(Item item){
        //将插入的数据放到堆的最下面，进行上浮操作
        assert(count+1 <= capacity); //这里只做判断，不进行扩容操作
        data[count+1] = item;
        count ++;
        shiftUp(count);
    }
    Item gatMin(){
        assert(count > 0);
        swap(data[1], data[count]);
        count --;
        shiftDown(1);
        return data[count+1];
    }
};


#endif //ALGORITHM_MINHEAP_H
