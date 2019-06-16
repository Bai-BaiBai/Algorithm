//
// Created by BaiZehong on 2019/6/16.
//

#ifndef ALGORITHM_BINARYSEARCH_H
#define ALGORITHM_BINARYSEARCH_H

/**
 * 二分查找法
 * 只能在有序数组中查找,在arr中查找target元素，返回索引下标index
 */
namespace BinarySearch{

    template <typename T>
    int binarySearch(T arr[], int n, T target){

        // 在arr[l...r]中寻找target
        int l = 0, r = n-1;
        while ( l <= r){
            int mid = l+ (r-l)/2;//防止越界
            if (arr[mid] == target) return mid;
            if (arr[mid] < target){
                l = mid+1;
            } else{
                r = mid-1;
            }
        }
        return -1;
    }

    // 递归
    int binarySearch2(T arr[], int l, int r, T target){
        if (l > r)
            return -1;
        int mid = l + (r-l)/2;
        if (arr[mid] == target) return mid;

        if (arr[mid] > target){
            return binarySearch2(arr, l, mid-1, target);
        } else {
            return binarySearch2(arr, mid+1, r, target);
        }
    }

    // 返回target值的最小下标，如果不存在就返回比target小的元素的最大下标(最接近它的前一个)
    int floor(T arr[], int n, T target){
        int l = -1, r = n-1;// 如果数组中的最小值都比target大，返回-1

        while (l < r){
            int mid = l + (r-l+1)/2;//向上取整，防止死循环。 在floor中需要让l=mid而不是l=mid+1，因为mid可能就是要返回的值
            if (arr[mid] >= target){
                r = mid-1;// 先找比target前一个元素的下标，跳出循环后再判断是否有target
            } else {
                l = mid;// 因为mid可能就是target前一个元素的下标
            }
        }
        if (l+1 < n && arr[l+1] == target) return l+1;
        return l;
    }

    int ceil(T arr[], int n, T target){

        int l = 0, r = n;

        while (l < r){
            int mid = l + (r-l)/2; //找target的上限没有死循环问题

            if (arr[mid] <= target){
                l = mid + 1;
            } else{
                r = mid;//此时可能arr[mid]即为target的上界
            }
        }
        if (r-1 >= 0 && arr[r-1] == target) return r-1;
        return r;
    }
}

#endif //ALGORITHM_BINARYSEARCH_H
