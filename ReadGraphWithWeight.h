// 图的相关算法
// Created by BaiZehong on 2019/6/22.
//

#ifndef ALGORITHM_READGRAPH_H
#define ALGORITHM_READGRAPH_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

/**
 * 图的相关算法
 * 1--从txt文件中读取图
 * 2--求连通分量，图的深度优先遍历
 *
 */
namespace ReadGraph{

    // 从txt文件中将图读取到Graph类中
    // 使用稀疏图还是稠密图均可
    template <typename Graph, typename Weight>
    class ReadGraph{
    public:
        // 从文件中读取图   图保存在Graph.txt中
        ReadGraph(Graph &graph, const string &fileName){
            ifstream file(fileName);
            string line;// 将文件中的内容读到line中
            int V,E;// 保存顶点数、边数
            assert(file.is_open());
            assert(getline(file, line));
            stringstream ss(line);
            ss >> V >> E;//文件第一行存储点数、边数
            assert( V == graph.V());

            for (int i = 0; i < E; ++i) { // 读取边
                assert( getline(file, line) );
                stringstream ss(line);
                int a, b;
                Weight weight;
                ss >> a >> b >> weight;
                assert( a >= 0 && a < V)
                assert( b >= 0 && b < V)
                graph.addEdge(a,b,weight);
            }
        }
    };

    // 求连通分量，图的深度优先遍历
    template <typename Graph>
    class Component{
    private:
        Graph &G;//需要求解的图
        bool *visited;// 标记每个节点是否走过
        int count;// 连通分量个数
        int *id;// 查看每个节点属于哪个连通分量

        void dfs(int v){
            visited[v] = true;
            id[v] = count;// 相同联通分量节点的id值均相同
            typename Graph::adjIterator adj(G, v);
            for (int i = adj.begin(); !adj.end(); i = adj.next()) {
                if (!visited[i]){// 如果没有遍历过，对该节点进行深度遍历
                    dfs(i);
                }
            }
        }

    public:
        Component(Graph &graph):G(graph){
            this->visited = new bool[graph.V()];
            this->id = new int[graph.V()];
            this->count = 0;
            for (int i = 0; i < G.V(); ++i) {
                visited[i] = false;
                id[i] = -1;
            }

            for (int j = 0; j < G.V(); ++j) {
                if (!visited[j]) {
                    dfs(i);// 如果当前节点没有访问过，就对它进行深度优先遍历
                    count++;
                }
            }
        }
        ~Component(){
            delete [] visited;
            delete [] id;
        }

        int count(){
            return count;
        }

        // 查看两个节点是否相通(不一定直接相连)
        bool isConnected(int v, int w){
            assert( v >= 0 && v < G.V());
            assert( w >= 0 && w < G.V());
            return id[v] == id[w];
        }
    };
}
#endif //ALGORITHM_READGRAPH_H
