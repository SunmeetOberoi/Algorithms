#include<bits/stdc++.h>
#include "Disjoint_sets.h"

using namespace std;

struct Graph{
    int vertices;
    vector<vector<int>> adj;
    vector<pair<pair<int, int>, int>> edges;
    bool directed;

    Graph(int size, bool isDirected);

    void add_edge(int u, int v, int w){
        edges.emplace_back(make_pair(u, v), w);
        adj[u].push_back(v);
        if(!directed) 
            adj[v].push_back(u);
    }
};


Graph::Graph(int size, bool isDirected=true){
    /***
     * Creates a graph of the given size(0-(size-1)).
     * 
     * @param size number of node of the graph.
     * @param isDirected boolean values true if graph is directed.
    */
    vertices = size;
    directed = isDirected;
    for(int i=0;i<size;i++){
        vector<int> v;
        adj.push_back(v);
    }
}


bool comp(const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b){
    /***
     * Utility function used by sort to return edges in non-decreasing order.
     * 
     * @param a edge to be compared.
     * @param b edge to be compared.
    */
    return a.second < b.second;
}


vector<pair<pair<int, int>, int>> mst_kruskal(Graph g){
    /***
     * Returns the minimum spanning tree of the graph, 
     * by selecting the edge in a non-decreasing order 
     * which connects A to an isolated node.
     * 
     * @param g Graph whoose minimum spanning tree is provided.
     * 
     * @return a vector containing the edges which form the MST.
    */
    vector<pair<pair<int, int>, int>> A;
    vector<DisjointSet> disjointSets;
    for(int i=0;i<g.vertices;i++)
        make_set(i, disjointSets);
    sort(g.edges.begin(), g.edges.end(), comp);
    for(pair<pair<int, int>, int> edge : g.edges){
        if(find_set(edge.first.first, disjointSets) != find_set(edge.first.second, disjointSets)){
            A.push_back(edge);
            union_set(edge.first.first, edge.first.second, disjointSets);
        }
    }
    return A;
}



int main(){
    Graph g = Graph(9, false);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 8);
    g.add_edge(1, 2, 11);
    g.add_edge(1, 4, 8);
    g.add_edge(2, 3, 7);
    g.add_edge(2, 5, 1);
    g.add_edge(3, 4, 2);
    g.add_edge(3, 5, 6);
    g.add_edge(4, 6, 7);
    g.add_edge(4, 7, 4);
    g.add_edge(5, 7, 2);
    g.add_edge(6, 7, 14);
    g.add_edge(6, 8, 9);
    g.add_edge(7, 8, 10);
    vector<pair<pair<int, int>, int>> mst = mst_kruskal(g);
    for(pair<pair<int, int>, int> p : mst)
        cout<<p.first.first<<"-"<<p.first.second<<"=>"<<p.second<<endl;
    return 0;
}