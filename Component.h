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
         int *id;// 标识每个节点属于的联通分量，可以得出两个节点是否是属于一个联通分量

         // 递归完成深度遍历
         void dfs(int v){
             visited[v] = true;
             id[v] = ccount;
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
             id = new int[G.V()];
             ccount = 0;
             for (int i = 0; i < G.V(); ++i) {
                 visited[i] = false;
                 id[i] = -1;
             }

             for (int i = 0; i < G.V(); ++i) {
                 // 如果没遍历过，就对它进行深度优先遍历
                 if (!visited[i]){
                     dfs(i);
                     ccount ++;
                 }
             }
         }

         // 返回两个节点是否相通
         bool isConnected(int p, int q){
             if (id[p] == -1 || id[q] == -1) {
                 return false;
             } else {
                 return id[p] == id[q];
             }
         }

         // 返回联通分量个数
         int count(){
             return ccount;
         }

         ~Component(){
             delete[] visited;
             delete [] id;
         }
     };
 }

#endif //ALGORITHM_COMPONENT_H
