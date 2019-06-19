// 并查集
// Created by BaiZehong on 2019/6/19.
//

#ifndef ALGORITHM_UNIONFIND_H
#define ALGORITHM_UNIONFIND_H

#include <assert.h>

namespace QuickUnion{
    class UnionFind{
    private:
        int* id; // 存储元素的数组
        int count;// 元素数

    public:
        UnionFind(int n){
            count = n;
            id = new int[n];
            for (int i = 0; i < n; ++i) {
                id[i] = i;
            }
        }

        ~UnionFind(){
            delete [] id;
        }

        // 查找 p 号元素属于哪个集
        int find(int p){
            assert(p >= 0 && p < count);
            while (p != id[p]){
                p = id[p];
            }
            return p;
        }

        bool isConnected(int p, int q){
            return find(p) == find(q);
        }

        void unionElements(int p, int q){
            int pID = find(p);
            int qID = find(q);
            if (pID == qID) return;
            id[pID] = qID;
        }
    };
}

#endif //ALGORITHM_UNIONFIND_H
