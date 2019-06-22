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
            int begin(){
                index = -1;
                return next();
            }

            // 返回要迭代的下一个元素
            int next(){
                for (index++ ; index < G.V(); index ++) {
                    // 每次查看index下一个元素 在矩阵中是否对应true
                    if(G.g[v][index]){
                        return index;
                    }
                }
                return -1;
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
