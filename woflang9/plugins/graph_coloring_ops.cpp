// plugins/graph_coloring_ops.cpp
#include <iostream>
#include <vector>

namespace woflang {

std::vector<int> greedyGraphColoring(const std::vector<std::vector<int>>& graph) {
    int n=graph.size(); std::vector<int> res(n,-1); std::vector<bool> avail(n,false);
    res[0]=0;
    for(int u=1;u<n;++u){
        for(int v:graph[u]) if(res[v]!=-1) avail[res[v]]=true;
        int c; for(c=0;c<n;++c) if(!avail[c]) break;
        res[u]=c;
        for(int v:graph[u]) if(res[v]!=-1) avail[res[v]]=false;
    }
    return res;
}

} // namespace woflang
