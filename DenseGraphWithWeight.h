//
// Created by BaiZehong on 2019/6/21.
//

#ifndef ALGORITHM_DENSEGRAPH_H
#define ALGORITHM_DENSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"

using namespace std;

// 稠密图 - 邻接矩阵+权值
template <typename Weight>
namespace DenseGraph{
    class DenseGraph{
    private:
        int n;// 图中的点数
        int m; // 图中的边数
        bool directed;// true有向图，false无向图
        vector< vector< Edge<Weight> *> g; // 存储图，存储指针是为了能存储NULL值，矩阵中NULL表示无边

    public:
        DenseGraph(int n, bool directed){
            this->n = n;
            this -> m = 0;// 初始没有边
            this -> directed = directed;
            for (int i = 0; i < n; ++i) {
                g.push_back( vector<Edge<Weight> *>(n, NULL) );
            }
        }
        ~DenseGraph(){
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (g[i][j] != NULL){
                        delete g[i][j];
                    }
                }
            }
        }

        int V(){ return n;}// 返回有多少个顶点
        int E() { return  m;}// 返回有多少个边

        void addEdge(int v, int w, Weight weight){
            assert(v >= 0 && v < n);
            assert(w >= 0 && w < n);
            // 如果原来有边，删除掉旧边;  这里采取的策略是替换，也可以采取比较权值大小来替换
            if (hasEdge(v, w)) {
                delete g[v][w];
                if (!directed){// 如果是无向图，还要删除反方向的旧边
                    delete g[w][v];
                }
                m --;
            }

            g[v][w] = new Edge<Weight>(v, w, weight);
            if (!directed){// 如果是无向图
                g[w][v] = new Edge<Weight>(w, v, weight);
            }
            m ++;
        }

        bool hasEdge(int v, int w){
            assert(v >= 0 && v <n);
            assert(w >= 0 && w < n);
            return g[v][w] != NULL;
        }

        // 打印邻接矩阵
        void show(){
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (g[i][g] != NULL) {
                        cout << g[i][j]->wt() << "\t";
                    } else{
                        cout << "NULL\t";
                    }
                }
                cout << endl;
            }
        }

        // 稠密图的迭代器
        class adjIterator{
        private:
            DenseGraph &G;// 要迭代哪张图
            int v;// 要迭代图中的哪个点
            int index;// 当前迭代到哪步
        public:
            adjIterator(DenseGraph &graph, int v): G(graph){
                this->v = v;
                this->index = -1;
            }

            // 返回要迭代的第一个元素
            Edge<Weight>* begin(){
                index = -1;
                return next();
            }

            // 返回要迭代的下一个元素
            Edge<Weight>* next(){
                for (index++ ; index < G.V(); index ++) {
                    // 每次查看index下一个元素 在矩阵中是否对应true
                    if(G.g[v][index]){
                        return G.g[v][index];
                    }
                }
                return NULL;
            }

            // 检查迭代是否结束
            bool end(){
                return index >= G.V();
            }

            /*
            // 使用示例
            void example(){
                DenseGraph g1(100, false);
                DenseGraph::adjIterator adj(g1, 0);
                for (int i = adj.begin(); !adj.end(); i = adj.next()) {
                    // 迭代
                }
            }
            */
        };
    };
}

#endif //ALGORITHM_DENSEGRAPH_H
