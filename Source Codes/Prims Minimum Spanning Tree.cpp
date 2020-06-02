#include<iostream>
#include<vector>
#include<map>
#include "PriorityQueue.h"

#define INF 1e9
#define NIL -1

using namespace std;

struct Graph{
    int vertices;
    vector<vector<int>> adj;
    map<pair<int, int>, int> edges;
    bool directed;

    Graph(int size, bool isDirected);

    void add_edge(int u, int v, int w){
        edges[make_pair(u, v)]=w;
        adj[u].push_back(v);
        if(!directed){
            adj[v].push_back(u);
            edges[make_pair(v, u)]=w;
        }
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

struct PrimNode{
    int key;
    int vertex;
    int parent;
};

struct compKey{
    bool operator()(const PrimNode &a, const PrimNode &b){
        return a.key<b.key;
    }
};

vector<PrimNode> mst_prim(Graph g, int r){
    /***
     * Returns the minimum spanning tree of the graph, 
     * by selecting the edge which connects A to an isloated 
     * node whoose weight is the least amongst all others.
     * 
     * @param g Graph whoose minimum spanning tree is provided.
     * @param r root for the Prim's algorithm.
     * 
     * @return a vector of type PrimNode which contains information of the vertices 
     *         and their parents in the minimum spanning tree.
    */
    vector<PrimNode> mst(g.vertices);
    for(int i=0;i<g.vertices;i++){
        mst[i].key=inf;
        mst[i].vertex=i;
        mst[i].parent=NIL;
    }
    mst[r].key=0;
    PriorityQueue<PrimNode, compKey> Q(mst);
    int u;
    while(!Q.empty()){
        u = Q.extract_top_index();
        for(int v : g.adj[u]){
            if(Q.member(v) && g.edges[make_pair(u, v)] < mst[v].key){
                mst[v].parent = u;
                mst[v].key = g.edges[make_pair(u, v)];
                Q.update_node(v, mst[v]);
            }
        }
    }
    return mst;
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
    vector<PrimNode> mst = mst_prim(g, 0);
    for(PrimNode p : mst)
        if(p.parent!=NIL)
            cout<<p.vertex<<"|<->|"<<p.parent<<"=>"<<p.key<<endl;
    return 0;
}