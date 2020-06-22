#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

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


struct DFSNode{
    int processed;
    int parent;
    int discovered;
    int finished;
};


struct DAGNode{
    int d;
    int parent;
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

void initialize_single_source(Graph &g, int source, vector<DAGNode> &info){
    /***
     * Initialize the shortest-path estimates and predecessors by the 
     * following O(V)-time procedure. After initialization, we have 
     * v.π = NIL for all v ∈ V, s.d=0, and v.d = ∞ for v ∈ V - {s}.
     * 
     * @param g Graph.
     * @param source the source of the single source problem.
     * @param info BFNode type vector which store all the processing 
     *             information of the graph.
    */
    for(int i=0;i<g.vertices;i++){
        info[i].d=inf;
        info[i].parent=NIL;
    }
    info[source].d=0;
}

void relax(Graph &g, int u, int v, vector<DAGNode> &info){
    /***
     * Performs a relaxation step on edge(u, v) in O(1) time.
     * 
     * @param g Graph.
     * @param u first node.
     * @param v second node.
     * @param info BFNode type vector which store all the processing 
     *             information of the graph.
    */
    if(info[v].d > info[u].d + g.edges[make_pair(u, v)]){
        info[v].d = info[u].d + g.edges[make_pair(u, v)];
        info[v].parent = u;
    }
}

void DFS_visit(Graph &g, int u, vector<DFSNode> &info, int &time);


vector<DFSNode> DFS(Graph &g){
    /***
     * Performs Depth-first search on the graph, 
     * responsible for selecting every individual component 
     * of the graph for procesing.
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
   for(int i=0;i<g.vertices;i++){
       if(!info[i].processed){
           DFS_visit(g, i, info, time);
       }
   }
   return info;
}


void DFS_visit(Graph &g, int u, vector<DFSNode> &info, int &time){
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
            DFS_visit(g, v, info, time);
        }
    }
    info[u].processed=true;
    time++;
    info[u].finished=time;
}

vector<int> topological_sort(Graph &g){
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

void DAGShortestPath(Graph &g, int source, vector<DAGNode> &info){
    /***
     * Computing the shortest path from a single source in Θ(V+E) time in a DAG
     * by topoligically sorting the vertices.
     * 
     * @param g Graph.
     * @param source the source of the single source problem.
     * @param info DAGNode type vector which store all the processing 
     *             information of the graph.
    */
    vector<int> sortedNodes = topological_sort(g);
    initialize_single_source(g, source, info);
    for(int u: sortedNodes)
        for(int v: g.adj[u])
            relax(g, u, v, info);
}

int main(){
    int size=6;
    Graph g = Graph(size);
    vector<DAGNode> info(size);
    g.add_edge(0, 3, 2);
    g.add_edge(0, 2, 6);
    g.add_edge(1, 0, 5);
    g.add_edge(1, 3, 3);
    g.add_edge(2, 4, -1);
    g.add_edge(2, 5, 1);
    g.add_edge(3, 2, 7);
    g.add_edge(3, 4, 4);
    g.add_edge(3, 5, 2);
    g.add_edge(4, 5, -2);

    DAGShortestPath(g, 0, info);

    for(int i=0;i<info.size();i++)
        cout<<i<<"::"<<info[i].d<<endl;

    int target=5;
    vector<int> path;
    while (target!=NIL){
        path.push_back(target);
        target=info[target].parent;
    }
    
    for(int i=path.size()-1;i>0;i--)
        cout<<path[i]<<"->";
    cout<<path.front()<<endl;
    return 0;
}