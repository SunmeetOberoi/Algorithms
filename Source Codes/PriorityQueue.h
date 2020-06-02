#include<iostream>
#include<vector>
#include<map>
#include<cmath>


#define inf 1e9

using namespace std;

template<typename node, typename compare>
class PriorityQueue{

    // this will contain all the elements.
    vector<node> mainHeap;

    // mapping from index to position in heap so that 
    //accessing a node can be done efficiently.
    vector<int> posMapping;


    // mapping from position in heap to index in
    //posMapping.
    vector<int> indexMapping;

    // function used to define whether the priority queue is max or min, defaults to minHeap.
    compare comp;

    int parent(int i){
        return ceil(i/2.0)-1;
    }
    int left(int i){
        return 2*i+1;
    }
    int right(int i){
        return 2*i+2;
    }

    // private function declarations.
    void heapify(int i);
    void build_heap();
    void extract_top();

    public:
        // constructor declarations.
        PriorityQueue(){}
        PriorityQueue(vector<node> vals);

        // public function declarations
        void update_node(int i, node key);
        node top_node();
        int top_index();
        node extract_top_node();
        int extract_top_index();
        bool empty();
        bool member(int x);

        /*** DEBUGGING ***/
        void print(){
            /***
             * Prints all the elements of posMapping
            */
            for(int i : posMapping)
                cout<<i<<endl;
            cout<<"----------"<<endl;
        }
        /*** DEBUGGING ***/
};


template<typename node, typename compare>
PriorityQueue<node, compare>::PriorityQueue(vector<node> vals){
    /***
     * Priority Queue constructor, adds all the values in vals to the heap.
     * 
     * @param vals vector of template type node which contains the nodes to be added to the heap.
    */
    for(auto i : vals){
        mainHeap.push_back(i);
        posMapping.push_back(posMapping.size());
        indexMapping.push_back(indexMapping.size());
    }
    build_heap();
}


template<typename node, typename compare>
void PriorityQueue<node, compare>::heapify(int i){
    /***
     * Maintains the heap property for the subtree rooted at i.
     * 
     * @param i root of the subtree.
    */
    int l=left(i), r=right(i), higher;
    if(l<mainHeap.size() && comp(mainHeap[l], mainHeap[i]))
        higher = l;
    else higher = i;
    if(r<mainHeap.size() && comp(mainHeap[r], mainHeap[higher]))
        higher=r;
    if(higher != i){
        swap(mainHeap[i], mainHeap[higher]);
        
        swap(posMapping[indexMapping[i]], posMapping[indexMapping[higher]]);
        swap(indexMapping[i], indexMapping[higher]);
        
        heapify(higher);
    }
}


template<typename node, typename compare>
void PriorityQueue<node, compare>::build_heap(){
    /***
     * Builds a heap from an vector of nodes.
    */
    for(int i=mainHeap.size()/2-1;i>=0;i--){
        heapify(i);
    }
}


template<typename node, typename compare>
void PriorityQueue<node, compare>::update_node(int i, node key){
    /***
     * Updates the value of a node in the mainHeap, the value 
     * should be lesser/greater than the node's value for min/max heap respectively.
     * 
     * @param i index of the node to be updated.
     * @param key the value of the node to be updated.
    */
    int mappedKey = posMapping[i];
    if(comp(mainHeap[mappedKey], key)){
        cout<<"The requested update operation is not supported! Exiting..."<<endl;
        exit(-1);
    }
    mainHeap[mappedKey] = key;
    while(mappedKey>0 && comp(mainHeap[mappedKey], mainHeap[parent(mappedKey)])){
        swap(mainHeap[mappedKey], mainHeap[parent(mappedKey)]);
        
        swap(posMapping[indexMapping[mappedKey]], posMapping[indexMapping[parent(mappedKey)]]);
        swap(indexMapping[mappedKey], indexMapping[parent(mappedKey)]);

        mappedKey=parent(mappedKey);
    }
}


template<typename node, typename compare>
node PriorityQueue<node, compare>::top_node(){
    /***
     * Provides the min/max node in case of min/max
     * heap respectively.
     * 
     * @return top of the heap.
    */
    return mainHeap[0];
}


template<typename node, typename compare>
int PriorityQueue<node, compare>::top_index(){
    /***
     * Provides the index of the min/max node in case 
     * of min/max heap respectively.
     * 
     * @return index of the top of heap.
    */
    return indexMapping[0];
}


template<typename node, typename compare>
void PriorityQueue<node, compare>::extract_top(){
    /***
     * Deletes the top of the heap.
    */
    mainHeap[0]=mainHeap[mainHeap.size()-1];
    posMapping[indexMapping[0]]=-1;
    indexMapping[0]=indexMapping[indexMapping.size()-1];
    posMapping[indexMapping[0]]=0;
    mainHeap.pop_back();
    indexMapping.pop_back();
    heapify(0);
}


template<typename node, typename compare>
node PriorityQueue<node, compare>::extract_top_node(){
    /***
     * Removes the top of the heap and returns its value.
     * 
     * @return top of the heap.
    */
    if (mainHeap.size() < 1){
        cout<<"Priority Queue Underflow"<<endl;
        exit(-1);
    }
    node top = mainHeap[0];
    extract_top();
    return top;
}


template<typename node, typename compare>
int PriorityQueue<node, compare>::extract_top_index(){
    /***
     * Removes the top of the heap and return its index.
     * 
     * @return index of the top of the heap.
    */
    if (mainHeap.size() < 1){
        cout<<"Priority Queue Underflow"<<endl;
        exit(-1);
    }
    int top = indexMapping[0];
    extract_top();
    return top;
}


template<typename node, typename compare>
bool PriorityQueue<node, compare>::empty(){
    /***
     * Tells whether the Queue is empty or not.
     * 
     * @returns a boolean value specifying whether the queue is empty.
    */
    return mainHeap.size()==0?true:false;
}

template<typename node, typename compare>
bool PriorityQueue<node, compare>::member(int x){
    /***
     * Check a number for its membership in the queue.
     * 
     * @param x index of the node which is to be checked for membership.
     * 
     * @returns a boolean value specifying wheter x is a member of the priority queue.
    */
    return indexMapping[posMapping[x]] == x;
}