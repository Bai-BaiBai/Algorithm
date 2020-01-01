//
// Created by BaiZehong on 2019/6/21.
//

#ifndef ALGORITHM_SPARSEGRAPH_H
#define ALGORITHM_SPARSEGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>
#include "Edge.h"

using namespace std;

// 稀疏图 - 邻接表
template <typename Weight>
namespace SparseGraph{
    class SparseGraph{
    private:
        int n;// 图中点数
        int m;// 图中边数
        bool directed;// true有向图/ false无向图
        vector <vector< Edge<Weight> *> g; // 存相连点的位置

    public:
        SparseGraph(int n, bool directed){
            this -> n = n;
            this -> m = 0;
            this -> directed = directed;
            for (int i = 0; i < n; ++i) {
                g.push_back( vector< Edge<Weight> *>());
            }
        }
        ~SparseGraph(){
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < g[i].size(); ++j) {
                    delete g[i][j];
                }
            }
        }

        int V(){ return n;}// 返回有多少个顶点
        int E() { return  m;}// 返回有多少个边

        void addEdge(int v, int w, Weight weight){
            assert(v >= 0 && v < n);
            assert(w >= 0 && w < n);

            g[v].push_back(new  Edge(v, w, weight));
            if (!directed && v != w){// 如果是无向图
                g[w].push_back(new  Edge(w, v, weight));
            }
            m++;
            // 暂时不处理平行边的问题,即两个点之间可能存在多个边
        }

        bool hasEdge(int v, int w){
            assert(v >= 0 && v < n);
            assert(w >= 0 && w < n);
            for (int i = 0; i < g[v].size(); ++i) {
                if (g[v][i] -> other(v) == w)
                    return true; // 如果与v点相连边的另一个点是w
            }
            return false;
        }

        // 打印邻接表
        void show(){
            for (int i = 0; i < n; ++i) {
                cout << "vertex" << i << ":\t";
                for (int j = 0; j < g[i].size(); ++j) {
                    cout << "( to:" <<g[i][j]-> w() << ", wt:"<< g[i][j] -> wt() <<" )\t";
                }
                cout << endl;
            }
        }

        // 稀疏图的迭代器
        class adjIterator{
        private:
            SparseGraph &G;// 要迭代哪张图
            int v;// 要迭代图中的哪个点
            int index;// 当前迭代到哪步
        public:
            adjIterator(SparseGraph &graph, int v): G(graph){
                this->v = v;
                this->index = 0;
            }

            // 返回要迭代的第一个元素
            Edge<Weight>* begin(){
                index = 0;
                if (G.g[v].size()){// 如果节点v 的邻接表不为空
                    return G.g[v][0];
                }
                return NULL;
            }

            // 返回要迭代的下一个元素
            Edge<Weight>* next(){
                index ++;
                if (index < G.g[v].size()){
                    return G.g[v][index];
                }
                return NULL;
            }

            // 检查迭代是否结束
            bool end(){
                return index >= G.g[v].size()
            }

            /*
            // 使用示例
            void example(){
                SparseGraph g1(100, false);
                SparseGraph::adjIterator adj(g1, 0);
                for (int i = adj.begin(); !adj.end(); i = adj.next()) {
                    // 迭代
                }
            }
            */
        };
    };
}

#endif //ALGORITHM_SPARSEGRAPH_H
