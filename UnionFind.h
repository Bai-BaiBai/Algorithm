// 并查集
// Created by BaiZehong on 2019/6/19.
//

#ifndef ALGORITHM_UNIONFIND_H
#define ALGORITHM_UNIONFIND_H

#include <assert.h>

// 路径压缩，find操作时，压缩寻找路径
namespace QuickUnion_Path{
    class UnionFind{
    private:
        int* id; // 存储元素的数组
        int* rank;// rank[i]表示以i为根的集的高度
        int count;// 元素数

    public:
        UnionFind(int n){
            count = n;
            id = new int[n];
            for (int i = 0; i < n; ++i) {
                id[i] = i;
                rank[i] = 1;
            }
        }

        ~UnionFind(){
            delete [] id;
            delete [] rank;
        }

        // 查找 p 号元素属于哪个集
        int find(int p){
            assert(p >= 0 && p < count);
            while (p != id[p]){
                id[p] = id[id[p]]; // 压缩：让p的父亲，指向父亲的父亲，不存在无效索引的问题。
                p = id[p]; // 这种压缩并不是让p最终直接指向并查集的根
            }
            return p;
        }

        // 完全压缩
        int find_CompleteCompression(int p){
            if (id[p] != p){
                id[p] = find_CompleteCompression( id[p] );
            }
            return id[p];
        }

        bool isConnected(int p, int q){
            return find(p) == find(q);
        }

        void unionElements(int p, int q){
            int pID = find(p);
            int qID = find(q);
            if (pID == qID) return;
            if (rank[pID] < rank[qID]) {
                id[pID] = qID; // 让 p 合并到 q 上去
            } else if (rank[qID] < rank[pID]){
                id[qID] = pID; // 这两种情况都不需要维护rank，因为高度高的节点rank值不改变
            } else { // rank[qID] == rank[pID]
                id[pID] = qID;
                rank[qID] ++; // 相等时，高度才发生变化
            }
        }
    };
}

// 基于rank的优化，rank[i]代表i节点的高度
namespace QuickUnion_Rank{
    class UnionFind{
    private:
        int* id; // 存储元素的数组
        int* rank;// rank[i]表示以i为根的集的高度
        int count;// 元素数

    public:
        UnionFind(int n){
            count = n;
            id = new int[n];
            for (int i = 0; i < n; ++i) {
                id[i] = i;
                rank[i] = 1;
            }
        }

        ~UnionFind(){
            delete [] id;
            delete [] rank;
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
            if (rank[pID] < rank[qID]) {
                id[pID] = qID; // 让 p 合并到 q 上去
            } else if (rank[qID] < rank[pID]){
                id[qID] = pID; // 这两种情况都不需要维护rank，因为高度高的节点rank值不改变
            } else { // rank[qID] == rank[pID]
                id[pID] = qID;
                rank[qID] ++; // 相等时，高度才发生变化
            }
        }
    };
}

// 基于集合size的优化，union操作时，将size小的集合向size大的集合合并
namespace QuickUnion_Size{
    class UnionFind{
    private:
        int* id; // 存储元素的数组
        int* size;// size[i]表示以i为根的并查集有多少个元素
        int count;// 元素数

    public:
        UnionFind(int n){
            count = n;
            id = new int[n];
            for (int i = 0; i < n; ++i) {
                id[i] = i;
                size[i] = 1;
            }
        }

        ~UnionFind(){
            delete [] id;
            delete [] size;
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
            if (size[pID] < size[qID]) {
                id[pID] = qID; // 让 p 合并到 q 上去
                size[qID] += size[qID]; // 维护 q 的size值
            } else {
                id[qID] = pID;
                size[pID] += size[qID];
            }
        }
    };
}

// 未优化过的并查集
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
