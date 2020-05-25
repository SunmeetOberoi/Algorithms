#include<bits/stdc++.h>
#include "dfs.h"

using namespace std;


vector<int> topological_sort(Graph g){
    /***
     * Performs a topological sort of a directed acyclic graph
     * or a "dag". A topological sort of a dag G = (V, E) is a 
     * linear ordering of all its vertices such that if G contains
     * an edge (u, v), then u appears before v in ordering.
     * (Graph should not contain cycles) It can be seen as 
     * sorting the vertices on a horizontal line so that all 
     * directed edges go from left to right.
     * 
     * @param g graph on which topological sort is to be performed.
    */
    vector<DFSNode> DFSForest = DFS(g);
    vector<pair<int, int>> indices;
    vector<int> sorted;

    for(int i=0;i<DFSForest.size();i++)
        indices.emplace_back(DFSForest[i].finished, i);
    sort(indices.begin(), indices.end(), greater<>());

    for(auto i : indices)
        sorted.push_back(i.second);

    return sorted;
}


int main(){
    Graph g=Graph(9);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 5);
    g.add_edge(3, 2);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    g.add_edge(0, 7);
    g.add_edge(1, 7);
    g.add_edge(6, 7);
    vector<int> sorted = topological_sort(g);
    cout<<"Topologically Sorted Sequence:"<<endl;
    for(int i : sorted)
        cout<<i<<endl;
    return 0;
}