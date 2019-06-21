//
// Created by BaiZehong on 2019/6/21.
//

#ifndef ALGORITHM_DENSEGRAPH_H
#define ALGORITHM_DENSEGRAPH_H

#include <vector>
#include <cassert>

using namespace std;

// 稠密图 - 邻接矩阵
namespace DenseGraph{
    class DenseGraph{
    private:
        int n;// 图中的点数
        int m; // 图中的边数
        bool directed;// true有向图，false无向图
        vector< vector<bool> > g; // 存储图 true代表有边

    public:
        DenseGraph(int n, bool directed){
            this->n = n;
            this -> m = 0;// 初始没有边
            this -> directed = directed;
            for (int i = 0; i < n; ++i) {
                g.push_back( vector<bool>(n, false) );
            }
        }
        ~DenseGraph(){}

        int V(){ return n;}// 返回有多少个顶点
        int E() { return  m;}// 返回有多少个边

        void addEdge(int v, int w){
            assert(v >= 0 && v < n);
            assert(w >= 0 && w < n);
            if (hasEdge(v, w)) return;
            g[v][w] = true;
            if (!directed){// 如果是无向图
                g[w][v] = true;
            }
            m++;
        }

        bool hasEdge(int v, int w){
            assert(v >= 0 && v <n);
            assert(w >= 0 && w < n);
            return g[v][w];
        }
    };
}

#endif //ALGORITHM_DENSEGRAPH_H
