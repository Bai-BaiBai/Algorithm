//
// Created by BaiZehong on 2020/1/1.
//

#ifndef ALGORITHM_EDGE_H
#define ALGORITHM_EDGE_H

#include <iostream>
#include <cassert>

template <typename Weight>
class Edge {
private:
    int a, b;// 两个顶点，对于有向图来说顺序为 a->b
    Weight weight;//顶点之间的权重

public:
    Edge(int a, int b, Weight weight) : a(a), b(b), weight(weight) {}

    Edge() {}

    ~Edge() {}

    int v() { return a; }

    int w() { return b; }

    Weight wt() { return weight; }

    // 找到这个边的另外一个顶点
    int other(int x) {
        assert(x == a || x == b);
        return x == a ? b : a;
    }

    // 重载输出
    friend ostream &operator<<(ostream &ostream, const Edge &e) {
        ostream << e.a << "-" << e.b << ": " << e.weight;
        return ostream;
    }

    //重载比较
    bool operator<(Edge<Weight> &e) {
        return this->weight < e.wt();
    }

    bool operator<=(Edge<Weight> &e) {
        return this->weight <= e.wt();
    }

    bool operator>(Edge<Weight> &e) {
        return this->weight > e.wt();
    }

    bool operator>=(Edge<Weight> &e) {
        return this->weight >= e.wt();
    }

    bool operator==(Edge<Weight> &e) {
        return this->weight == e.wt();
    }
};
#endif //ALGORITHM_EDGE_H
