//
// Created by BaiZehong on 2019/12/25.
//

#ifndef ALGORITHM_FINDPATH_H
#define ALGORITHM_FINDPATH_H

#include <iostream>
#include <cassert>
#include <vector>
#include <stack>

/**
 * 使用dfs算法寻找某个点到任意点的路径
 *
 * 时间复杂度：稀疏图(邻接表):O(V+E)
 *              稠密图(邻接矩阵):O(V^2)
 */
 namespace Path{
     template <template Graph>
     class Path{

     private:
         Graph &G;
         int s;// 图中的某个点
         bool *visited;// 访问数组
         int *from;// 记录所有节点从哪个节点来

         void dfs(int v){

             visited[v] = true;
             typename Graph::adjIterator adj(G, v);
             for (int i = adj.begin(); !adj.end() ; i = adj.next()) {
                 if (!visited[i]){
                     from[i] = v;// *** 对未访问过节点i dfs前，先记录i 的前一步
                     dfs(i);
                 }
             }
         }

     public:
         Path(Graph &graph, int s):G(graph){
             // 初始化
             assert(s >= 0 && s < G.V());
             visited = new bool[G.V()];
             from = new bool[G.V()];
             for (int i = 0; i < G.V(); ++i) {
                 visited[i] = false;
                 from[i] = -1;
             }
             this->s = s;

             // 寻路算法
             dfs(s);
         }

         // 判断给定点w 到s 是否有路
         bool hasPath(int w){
             assert(w >= 0 && w < G.V());
             return visited[w];// 只要访问过就是有路
         }

         // 存储路径到vec
         void path(int w, vector<int> &vec){
             stack<int> s;
             int p = w;
             while (p != -1){
                 s.push(p);
                 p = from[p];
             }
             vec.clear();
             while (!s.empty()){
                 vec.push_back(s.top());
                 s.pop();
             }
         }

         // 打印点w 到s的路径
         void showPath(int w){
             vector<int> vector;
             path(w, vector);
             for (int i = 0; i < vector.size(); ++i) {
                 cout << vector[i];
                 if (i == vector.size()-1){
                     cout << endl;
                 } else{
                     cout << " -> ";
                 }
             }
         }

         ~Path(){
             delete [] visited;
             delete [] from;
         }
     };
 }

#endif //ALGORITHM_FINDPATH_H
