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

namespace ReadGraph{

    // 使用稀疏图还是稠密图均可
    template <typename Graph>
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
                ss >> a >> b;
                graph.addEdge(a,b);
            }
        }
    };
}
#endif //ALGORITHM_READGRAPH_H
