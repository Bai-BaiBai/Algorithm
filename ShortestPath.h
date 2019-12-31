//
// Created by BaiZehong on 2019/12/31.
//

#ifndef ALGORITHM_SHORTESTPATH_H
#define ALGORITHM_SHORTESTPATH_H

#include <cassert>
#include <queue>
#include <vector>
#include <stack>

/**
 * 广度优先遍历-无向图最短路径
 */
namespace ShortestPath{
    template <typename Graph>
    class ShortestPath{

    private:
        Graph &G;
        int s; //源节点
        bool  *visited;
        int *from;
        int *order;//记录从s 到每个节点的最短距离

    public:
        ShortestPath(Graph &graph, int s):G(graph){
            assert( s >= 0 && s < graph.V());
            visited = new bool[graph.V()];
            from = new bool[graph.V()];
            order = new bool[graph.V()];
            for (int i = 0; i < graph.V(); ++i) {
                visited[i] = false;
                from[i] = -1;
                order[i] = -1;
            }
            this->s = s;

            // 最短路径算法
            queue<int> q;
            q.push(s);
            visited[s] = true;
            order[s] = 0;
            while (!q.isEmpty()){
                int v = q.front();
                q.pop();
                typename Graph::adjIterator adj(G, v);
                for (int j = adj.begin(); j != adj.end() ; j = adj.next()) {
                    if (!visited[i]) {
                        q.push(i);
                        visited[i] = true;
                        from[i] = v;
                        order[i] = order[v] + 1;
                    }
                }
            }
            q.push()
        }

        bool hasPath(int w){
            assert(w >= 0 && w < G.V());
            return visited[w];
        }

        void path(int w, vector<int> &vec){
            assert(w >= 0 && w < G.V());
            stack<int> stack;

            int p = w;
            while (p != -1){
                stack.push(p);
                p = from[p];
            }
            vec.clear();
            while (!p.empty()){
                vec.push_back( stack.top() );
                s.pop();
            }
        }

        int length(int w){
            assert( w >= 0 && w < G.V());
            return order[w];
        }

        ~ShortestPath(){
            delete [] visited;
            delete [] from;
            delete [] order;
        }
    };
}



#endif //ALGORITHM_SHORTESTPATH_H
