//索引堆
// Created by BaiZehong on 2019/6/16.
//

#ifndef ALGORITHM_INDEXMAXHEAP_H
#define ALGORITHM_INDEXMAXHEAP_H

#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;

template <typename Item>
class IndexMaxHeap {

private:
    Item *data;  //元素数组，只用来存储元素，位置不变
    int* indexes;//索引数组，用来存储元素在data中的索引，同时维持最大堆的性质，indexed[1]为堆顶
    int count; //元素数量
    int capacity;//堆容量

    void shiftUp(int k){
        //插入的元素不为根节点，且值大于父节点时，上浮
        while (k > 1 && data[indexes[k]] > data[indexes[k/2]]){ // 先从indexes中取出索引，再从data中取出元素，比较
            swap(indexes[k], indexes[k/2]);
            k /= 2;
        }
    }

    // k为要下沉元素的下标，当前k有孩子且孩子中的最大元素大于data[k]时才进行下沉
    void shiftDown(int k){
        while (k <= count/2){
            int j = k*2;
            //先判断右孩子是否存在，在比较左孩子和右孩子的大小
            if (j+1 <= count && data[indexes[j+1]] > data[indexes[j]]) j++;
            //j存储的是左右孩子中，大的元素的下标
            if (data[indexes[k]] >= data[indexes[j]]){ //此时说明下沉完成
                return;
            }
            swap(indexes[k], indexes[j]);
            k = j;
        }
    }
public:
    IndexMaxHeap(int capacity){
        data = new Item[capacity+1];//从索引1开始存储
        indexes = new int[capacity+1];
        count = 0;//存储该堆中的元素个数
        this -> capacity = capacity;
    }

    //将一个数组heapify
    MaxHeap(Item arr[], int n){
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

    ~MaxHeap(){
        delete [] data;
        delete [] indexes;
    }

    int size(){ return count;}
    bool isEmpty(){ return count == 0;}

    // 插入元素的同时需要指明它的索引i，对于用户来说，i是从0开始计算的
    void insert(Item item, int i){
        //将插入的数据放到堆的最下面，进行上浮操作
        assert(count+1 <= capacity); //这里只做判断，不进行扩容操作
        assert(i+1 >= 1 && i+1 <= capacity);//索引不能越界

        i++;
        data[i] = item;//将元素放到 data[i]的位置
        indexes[count+1] = i;//将元素的索引

        count ++;
        shiftUp(count);
    }

    //取出堆顶元素
    Item gatMax(){
        assert(count > 0);
        swap(indexes[1], indexes[count]); //将堆顶元素和堆底元素互换
        count --;//维护数量
        shiftDown(1);
        return data[indexes[count+1]]
    }

    // 返回堆顶元素的索引
    int getMaxItemIndex(){
        assert(count > 0);
        swap(indexes[1], indexes[count]);
        count--;
        shiftDown(1);
        return indexes[count+1] - 1; // 对于外部用户，索引值是从0开始，所以-1
    }

    // 通过索引值获取元素，需要外部来判断索引是否合法
    Item getItem(int i){
        // 这里不能用count判断i是否合法，count代表堆中的元素，也就是indexes中的有效元素个数
        // 在弹出堆顶元素时 该元素依然在data中存在，只是从indexes中删除掉了
        return data[i+1];// i从0开始
    }

    // 修改索引为i的元素
    void change(int i , Item newItem){
        i += 1; // 索引从1开始
        data[i] = newItem;

        // 找到indexes[j] == i, j代表变更元素在堆中的位置
        // 尝试shiftDown和shiftUp 来维持最大堆的性质
        for (int j = 1; j < count+1; ++j) {//最差时间复杂度为O(n+logn)
            if (indexes[j] == i){
                shiftDown(j);
                shiftUp(j);
                return;
            }
        }
    }
};

#endif //ALGORITHM_INDEXMAXHEAP_H
