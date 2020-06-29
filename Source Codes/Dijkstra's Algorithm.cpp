#include<iostream>
#include<vector>
#include<map>
#include "PriorityQueue.h"

using namespace std;

#define inf 1e9
#define NIL -1

struct Graph{
    int vertices;
    vector<vector<int>> adj;
    map<pair<int, int>, int> edges;
    bool directed;

    Graph(int size, bool isDirected);

    void add_edge(int u, int v, int w){
        edges[make_pair(u, v)] = w;
        adj[u].push_back(v);
        if(!directed){
            adj[v].push_back(u);
            edges[make_pair(v, u)] = w;
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

struct DJNode{
    int d;
    int parent;
};

void initialize_single_source(Graph &g, int source, vector<DJNode> &info){
    /***
     * Initialize the shortest-path estimates and predecessors by the 
     * following O(V)-time procedure. After initialization, we have 
     * v.π = NIL for all v ∈ V, s.d=0, and v.d = ∞ for v ∈ V - {s}.
     * 
     * @param g Graph.
     * @param source the source of the single source problem.
     * @param info predecessor-subgraph.
    */
    for(int i=0;i<g.vertices;i++){
        info[i].d=inf;
        info[i].parent=NIL;
    }
    info[source].d=0;
}

struct comp{
    bool operator()(const DJNode &a, const DJNode &b){
        return a.d<b.d;
    }
};

void relax(Graph &g, int u, int v, vector<DJNode> &info, PriorityQueue<DJNode, comp> &Q){
    /***
     * Performs a relaxation step on edge(u, v) in O(1) time.
     * 
     * @param g Graph.
     * @param u first node.
     * @param v second node.
     * @param info predecessor-subgraph.
    */
    if(info[v].d > info[u].d + g.edges[make_pair(u, v)]){
        info[v].d = info[u].d + g.edges[make_pair(u, v)];
        info[v].parent = u;
        Q.update_node(v, info[v]);
    }
}

void print_path(Graph &g, int s, int v, vector<DJNode> &info){
    /***
     * Prints the vertices on a shortest path from source to destination
     * assuming that predecessor-subgraph has already been computed.
     * 
     * @param g graph on which shortest path is to be found.
     * @param s source node.
     * @param v destination node.
     * @param info predecessor-subgraph.
    */
    if(v==s)
        cout<<s<<endl;
    else if(info[v].parent==NIL)
        cout<<"No path from "<<s<<" to "<<v<<" exists"<<endl;
    else{
        print_path(g, s, info[v].parent, info);
        cout<<v<<endl;
    }
}

void dijkstra(Graph &g, int source, vector<DJNode> &info){
    /***
     * Dijkstra’s algorithm solves the single-source shortest-paths 
     * problem on a weighted, directed graph G=(V,E) for the case in 
     * which all edge weights are nonnegative. 
     * 
     * Time Complexity based on implementation of priority queue: 
     * Binary Heap: O((V + E)lg(V)), which is O((E)lg(V))
     * Fibonacci Heap: O((V)lg(V) + E)
     * 
     * @param g Graph.
     * @param source the source of the single source problem.
     * @param info predecessor-subgraph.
    */
    initialize_single_source(g, source, info);
    PriorityQueue<DJNode, comp> Q(info);
    int u;
    while(!Q.empty()){
        u = Q.extract_top_index();
        for(int v: g.adj[u])
            relax(g, u, v, info, Q);
    }

}

int main(){
    int size=5;
    Graph g = Graph(size);
    vector<DJNode> info(size);

    g.add_edge(0, 1, 10);
    g.add_edge(0, 2, 5);
    g.add_edge(1, 3, 1);
    g.add_edge(1, 2, 2);
    g.add_edge(2, 1, 3);
    g.add_edge(2, 4, 2);
    g.add_edge(2, 3, 9);
    g.add_edge(3, 4, 4);
    g.add_edge(4, 3, 6);
    g.add_edge(4, 0, 7);

    int source=0;
    dijkstra(g, source, info);

    print_path(g, source, 3, info);
    return 0;
}