#include<bits/stdc++.h>
#include "dfs.h"

using namespace std;

void DFS_visit_scc(Graph g, int u, vector<DFSNode> &info, int &time);


vector<DFSNode> DFS_scc(Graph g, vector<DFSNode> DFSForest){
    /***
     * Performs Depth-first search on the graph, 
     * responsible for selecting every individual component 
     * of the graph for procesing in order of decreasing 
     * finish time.
     * 
     * @param g the graph whoose DFS is to be computed.
     * 
     * @return vector of type DFSNode containing the DFS Forest.
    */
    vector<DFSNode> info(g.vertices);
    for(int i=0;i<g.vertices;i++){
       info[i].processed=false;
       info[i].parent=NIL;
    }
    int time=0;

    vector<pair<int, int>> indices;
    vector<int> sorted;

    for(int i=0;i<DFSForest.size();i++)
        indices.emplace_back(DFSForest[i].finished, i);
    sort(indices.begin(), indices.end(), greater<>());

    for(auto i : indices)
        sorted.push_back(i.second);


    for(int i : sorted){
        if(!info[i].processed){
            cout<<i<<" ";
            DFS_visit_scc(g, i, info, time);
            cout<<"\t";
        }
    }
    cout<<endl;
    return info;
}


void DFS_visit_scc(Graph g, int u, vector<DFSNode> &info, int &time){
    /***
     * Marks the discovery of a node and further
     * explores the adjacency list of that node.
     * 
     * @param g the graph.
     * @param u the node which is discovered.
     * @param info DFS forest.
     * @param time counter for setting discovery and finished time.
    */
    time++;
    info[u].discovered=time;
    info[u].processed=true;
    for(int v : g.adj[u]){
        if(!info[v].processed){
            info[v].parent=u;
            cout<<v<<" ";
            DFS_visit_scc(g, v, info, time);
        }
    }
    info[u].processed=true;
    time++;
    info[u].finished=time;
}

void strongly_connected_components(Graph g){
    /***
     * Provides the strongly connected components
     * of a graph. A strongly connected component 
     * of a directed graph G = (V, E) is a maximal 
     * set of vertices C ⊆ V such that for every pair 
     * of vertices u and v in C, we have both u~~>v
     *  and v~~>u; i.e., vertices u and v are reachable
     *  from each other.
     * 
     * @param g graph whose strongly connected components are to be discovered.
    */
   
    // compute finishing time for each verterx u.
    vector<DFSNode> DFSForest = DFS(g);

    // compute g transpose.
    Graph g_T = Graph(g.vertices);
    for(int i=0;i<g.vertices;i++)
        for(int j : g.adj[i])
            g_T.add_edge(j, i);
    
    DFS_scc(g_T, DFSForest);
}

int main(){
    Graph g = Graph(9);
    g.add_edge(1, 0);
    g.add_edge(0, 2);
    g.add_edge(2, 1);
    g.add_edge(1, 3);
    g.add_edge(2, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 5);
    g.add_edge(5, 3);
    g.add_edge(4, 5);
    g.add_edge(4, 6);
    g.add_edge(6, 4);
    g.add_edge(5, 7);
    g.add_edge(6, 7);
    g.add_edge(7, 7);
    g.add_edge(2, 8);
    g.add_edge(8, 0);
    strongly_connected_components(g);
    return 0;
}