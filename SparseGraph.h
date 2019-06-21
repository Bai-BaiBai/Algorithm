//
// Created by BaiZehong on 2019/6/21.
//

#ifndef ALGORITHM_SPARSEGRAPH_H
#define ALGORITHM_SPARSEGRAPH_H

#include <cassert>
#include <vector>

using namespace std;

// 稀疏图 - 邻接表
namespace SparseGraph{
    class SparseGraph{
    private:
        int n;// 图中点数
        int m;// 图中边数
        bool directed;// true有向图/ false无向图
        vector <vector<int>> g; // 存相连点的位置

    public:
        SparseGraph(int n, bool directed){
            this -> n = n;
            this -> m = 0;
            this -> directed = directed;
            for (int i = 0; i < n; ++i) {
                g.push_back( vector<int>());
            }
        }
        ~SparseGraph(){}

        int V(){ return n;}// 返回有多少个顶点
        int E() { return  m;}// 返回有多少个边

        void addEdge(int v, int w){
            assert(v >= 0 && v < n);
            assert(w >= 0 && w < n);
            g[v].push_back(w);
            if (!directed && v != w){// 如果是无向图
                g[w].push_back(v);
            }
            m++;
            // 暂时不处理平行边的问题,即两个点之间可能存在多个边
        }

        bool hasEdge(int v, int w){
            assert(v >= 0 && v < n);
            assert(w >= 0 && w < n);
            for (int i = 0; i < g[v].size(); ++i) {
                if (g[v][i] == w) return true;
            }
            return false;
        }
    };
}

#endif //ALGORITHM_SPARSEGRAPH_H
