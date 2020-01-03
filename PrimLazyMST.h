//
// Created by BaiZehong on 2020/1/3.
//

#ifndef ALGORITHM_PRIMLAZYMST_H
#define ALGORITHM_PRIMLAZYMST_H

#include <iostream>
#include "MinHeap.h"
#include "Edge.h"

/**
 * 切分法最小生成树
 * Minimum Spanning Tree
 * @tparam Graph
 * @tparam Weight
 */
template <typename Graph, typename Weight>
class PrimLazyMST{

private:
    Graph &G;
    MinHeap<Edge<Weight>> pq;// priority queue 优先队列
    bool *marked;// 图中的点是否被标记（属于哪个区域）
    vector<Edge<Weight>> mst;//存储最小生成树
    Weight mstWeight; // 最小生成树的权

    // 访问v
    void visit(int v){
        assert( !marked[v] ); // v节点不能被访问过
        marked[v] = true;

        typename Graph::adjIterator adj(G, v);
        // 对该节点的所有边访问
        for (Edge<Weight>* edge = adj.begin(); !adj.end(); edge = adj.next()){
            if ( !marked[edge->other(v)]){
                // 如果这个边的另一个节点没有被mark
                pq.insert(*edge);
            }
        }
    }

public:
    PrimLazyMST(Graph graph) : G(graph), pq(MinHeap<Edge<Weight>>(graph.E())){
        marked = new bool[G.V()];
        for (int i = 0; i < G.V(); ++i) {
            marked[i] = false;
        }
        mst.clear();

        // Lazy Prim
        visit(0);
        while ( !pq.isEmpty() ){
            Edge<Weight> edge = pq.gatMin();
            // 取出来的这个边可能不是横切边（Lazy）
            if ( marked[edge.v()] == marked[edge.w()])
                continue;
            // 否则，这个最小边一定是最小生成树的边
            mst.push_back(edge);

            // 此时这个边一定有一个端点是访问过的，另一个端点是没访问过的，找到没访问的那个点
            if ( !marked[edge.v()] ) {
                visit(edge.v());
            } else{
                visit(edge.w());
            }// 后续会将该节点划入访问过区域，并将所有的边insert到pq
        }

        // 计算最小权值
        mstWeight = mst[0].wt();
        for (int j = 0; j < mst.size(); ++j) {
            mstWeight += mst[i].wt();
        }
    }

    // 返回最小生成树
    vector<Edge<Weight>> mstEdges(){
        return mst;
    }

    // 返回得到的最小生成树权重
    Weight result(){
        return mstWeight;
    }

    ~PrimLazyMST(){
        delete [] marked;
    }
};
#endif //ALGORITHM_PRIMLAZYMST_H
