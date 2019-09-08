//
// Created by BaiZehong on 2019/9/8.
//

#ifndef ALGORITHM_COMPONENT_H
#define ALGORITHM_COMPONENT_H

/**
 * 深度优先遍历求联通分量个数
 */
 namespace Component{
     template <typename Graph>
     class Component{
     private:
         Graph &G; // 需要遍历的图
         bool *visited;// 访问标志数组
         int ccount;// 联通分量个数

         // 递归完成深度遍历
         void dfs(int v){
             visited[v] = true;
             typename Graph::adjIterator adj(G, v);
             for (int i = adj.begin(); i != adj.end() ; i = adj.next()) {
                 if(!visited[i]){
                     dfs(i);
                 }
             }
         }

     public:
         Component(Graph &graph): G(graph){
             visited = new bool[G.V()];
             ccount = 0;
             for (int i = 0; i < G.V(); ++i) {
                 visited[i] = false;
             }

             for (int i = 0; i < G.V(); ++i) {
                 // 如果没遍历过，就对它进行深度优先遍历
                 if (!visited[i]){
                     dfs(i);
                     ccount ++;
                 }
             }
         }

         // 返回联通分量个数
         int count(){
             return ccount;
         }

         ~Component(){
             delete[] visited;
         }
     };
 }

#endif //ALGORITHM_COMPONENT_H
