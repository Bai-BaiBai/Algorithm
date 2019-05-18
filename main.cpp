//
// Created by BaiZehong on 2019/5/8.
//

#include <iostream>
#include "SortTestHelper.h"
#include "QuickSort.h"
#include "MergeSort.h"
using namespace std;

int main() {
    int n = 100;
    int *arr = SortTestHelper::generateRandomArray(n, 0, 1000);
    QuickSort::quickSort3Ways(arr, n);

    SortTestHelper::printArray(arr, n);

    delete[] arr;

    return 0;
}
