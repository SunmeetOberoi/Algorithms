#define INF 1e9
#define NIL -1


using namespace std;


struct Graph{
    int vertices;
    vector<vector<int>> adj;
    bool directed;

    Graph(int size, bool isDirected);

    void add_edge(int u, int v){
        adj[u].push_back(v);
        if(!directed)
            adj[v].push_back(u);
    }
};


struct DFSNode{
    int processed;
    int parent;
    int discovered;
    int finished;
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
