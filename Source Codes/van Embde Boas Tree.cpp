#include<bits/stdc++.h>

#define NIL 1e9
#define U 8
using namespace std;


int upperSqrt(int u);


struct vEBNode{
    int u;
    int max;
    int min;
    vEBNode* summary;
    vector<vEBNode*> cluster;

    vEBNode(int u){
        this->u=u;
        max=NIL;
        min=NIL;
        summary=NULL;
        // base case won't contain cluster vector
        if(u>2){
            for(int i=0;i<upperSqrt(u);i++)
                cluster.push_back(NULL);
        }
    }
};


int lowerSqrt(int u){
    /***
     * Gives the lower square root.
     * 
     * @param u size of the node.
     * 
     * @return 2^⌊lg(u)/2⌋.
    ***/
    return pow(2, floor(log2(u)/2));
}


int upperSqrt(int u){
    /***
     * Gives the upper square root.
     * 
     * @param u size of the node.
     * 
     * @return 2^⌈lg(u)/2⌉.
    ***/
    return pow(2, ceil(log2(u)/2));
}


int high(int x, int u){
    /***
     * Provides the number of x's cluster.
     * 
     * @param x number whose cluster is to be found.
     * @param u size of value.
     * 
     * @return most significant ⌈lg(u)/2⌉ bits of x.
    ***/
    return floor(x/lowerSqrt(u));
}


int low(int x, int u){
    /***
     * Provides x's position within its cluster.
     * 
     * @param x number whose position is to be found.
     * @param u size of value.
     * 
     * @return least significant ⌊lg(u)/2⌋ bits of x.
    ***/
    return x%lowerSqrt(u);
}


int index(int x, int y, int u){
    /***
     * Builds an element number from x and y,
     * treating x as the most significant ⌈lg(u)/2⌉ bits 
     * of the element number and y as the least 
     * significant ⌊lg(u)/2⌋ bits.
     * 
     * @param x most significant ⌈lg(u)/2⌉ bits.
     * @param y least significant ⌊lg(u)/2⌋ bits.
     * @param u size of value.
     * 
     * @return the element number from x and y.
    ***/
    return x*lowerSqrt(u) + y;
}


vEBNode* create_tree(int size){
    /***
     * Create an empty van Embde Boas tree
     * of the given size, everything is initialized
     * to NULL/NIL.
     * 
     * @param size size of the current node to be created.
     * 
     * @return a pointer to the created node/root.
    ***/
    if(size && (!(size&(size-1)))){
        vEBNode* root = new vEBNode(size);
        if(size>2){
            root->summary = create_tree(upperSqrt(size));
            for(int i=0;i<root->cluster.size();i++)
                root->cluster[i] = create_tree(lowerSqrt(size));
        }
        return root;
    }
    return NULL;
} 


int vEB_tree_maximum(vEBNode V){
    /***
     * Gives the maximum number present in the node.
     * 
     * @param V a vEBNode whose max is to be found.
     * 
     * @return max of the vEBNode.
    ***/
    return V.max;
}


int vEB_tree_minimum(vEBNode V){
    /***
     * Gives the minimum number present in the node.
     * 
     * @param V a vEBNode whose min is to be found.
     * 
     * @return min of the vEBNode.
    ***/
    return V.min;
}


void vEB_empty_tree_insert(vEBNode &V, int x){
    /***
     * Adds an element to an empty VEBNode.
     * 
     * @param V node in which the value is to be inserted.
     * @param x the value to be inserted.
    ***/
    V.min=x;
    V.max=x;
}


void vEb_tree_insert(vEBNode &V, int x, int u){
    /***
     * Inserts an element to the node.
     * 
     * @param V node in which the value is to be inserted.
     * @param x number to be inserted.
     * @param u size of the node.
    ***/
    if(V.min==NIL){
        vEB_empty_tree_insert(V, x);
    }
    else{
        if (x<V.min)
            swap(x, V.min);
        if  (V.u>2){
            if(vEB_tree_minimum(*V.cluster[high(x, u)]) == NIL){
                vEb_tree_insert(*V.summary, high(x, u), upperSqrt(u));
                vEB_empty_tree_insert(*V.cluster[high(x, u)], low(x, u));
            }
            else
                vEb_tree_insert(*V.cluster[high(x, u)], low(x, u), upperSqrt(u));
        }
        if(x>V.max)
            V.max = x;
    }
}


bool vEB_tree_member(vEBNode V, int x, int u){
    /***
     * Tells if a number exists in the vEBNode.
     * 
     * @param V Node in which the value is to be checked for membership.
     * @param x the value that is to be checked.
     * @param u size of the node.
     * 
     * @return whether x is a member of V.
    ***/
    if(x==V.min || x==V.max)
        return true;
    else if(V.u==2)
        return false;
    else return vEB_tree_member(*V.cluster[high(x, u)], low(x, u), upperSqrt(u));
}


int vEb_tree_successor(vEBNode V, int x, int u){
    /***
     * Provides the successor a given number,
     * the given number may or may not exist 
     * in the node itself.
     * 
     * @param V vEBNode to be checked for the successor.
     * @param x number whose successor is to be found.
     * @param u size of the vEBNode.
     * 
     * @return the successor of x if present else NIL.
    ***/
    if(V.u==2){
        if(x==0 && V.max==1)
            return 1;
        else return NIL;
    }
    else if(V.min!=NIL && x<V.min)
        return V.min;
    else{
        int max_low = vEB_tree_maximum(*V.cluster[high(x, u)]);
        if(max_low!=NIL && low(x, u) < max_low){
            int offset = vEb_tree_successor(*V.cluster[high(x, u)], low(x, u), upperSqrt(u));
            return index(high(x, u), offset, u);
        }
        else{
            int succ_cluster = vEb_tree_successor(*V.summary, high(x, u), upperSqrt(u));
            if(succ_cluster==NIL)
                return NIL;
            else {
                int offset = vEB_tree_minimum(*V.cluster[succ_cluster]);
                return index(succ_cluster, offset, u);
            }
        }
    }
}


int vEb_tree_predecessor(vEBNode V, int x, int u){
    /***
     * Provides the predecessor a given number,
     * the given number may or may not exist 
     * in the node itself.
     * 
     * @param V vEBNode to be checked for the predecessor.
     * @param x number whose predecessor is to be found.
     * @param u size of the vEBNode.
     * 
     * @return the predecessor of x if present else NIL.
    ***/
    if(V.u==2){
        if(x==1 && V.min==0)
            return 0;
        else return NIL;
    }
    else if(V.max!=NIL && x>V.max)
        return V.max;
    else{
        int min_low = vEB_tree_minimum(*V.cluster[high(x, u)]);
        if(min_low!=NIL && low(x, u) > min_low){
            int offset = vEb_tree_predecessor(*V.cluster[high(x, u)], low(x, u), upperSqrt(u));
            return index(high(x, u), offset, u);
        }
        else{
            int pred_cluster = vEb_tree_predecessor(*V.summary, high(x, u), upperSqrt(u));
            if(pred_cluster==NIL){
                if(V.min!=NIL && x>V.min)
                    return V.min;
                else return NIL;
            }
            else {
                int offset = vEB_tree_maximum(*V.cluster[pred_cluster]);
                return index(pred_cluster, offset, u);
            }
        }
    }
}


void vEB_tree_delete(vEBNode &V, int x, int u){
    /***
     * Deletes an element from the node.
     * 
     * @param V node from which the value is to be deleted.
     * @param x number to be deleted.
     * @param u size of the node.
    ***/
    if(V.min == V.max){
        V.min=NIL;
        V.max=NIL;
    }
    else if(V.u==2){
        if(x==0)
            V.min=1;
        else
            V.min=0;
        V.max = V.min;
    }
    else{
        if(x==V.min){
            int first_cluster = vEB_tree_minimum(*V.summary);
            x=index(first_cluster, vEB_tree_minimum(*V.cluster[first_cluster]), u);
            V.min=x;
        }
        vEB_tree_delete(*V.cluster[high(x, u)], low(x, u), upperSqrt(u));
        if(vEB_tree_minimum(*V.cluster[high(x, u)])==NIL){
            vEB_tree_delete(*V.summary, high(x, u), upperSqrt(u));
            if(x==V.max){
                int summary_max = vEB_tree_maximum(*V.summary);
                if(summary_max==NIL)
                    V.max=V.min;
                else V.max = index(summary_max, vEB_tree_maximum(*V.cluster[summary_max]), u);
            }
        }
        else if(x==V.max)
            V.max=index(high(x, u), vEB_tree_maximum(*V.cluster[high(x, u)]), u);
    }
}


void print_vEB(vEBNode V){
    /***
     * Prints the vEB Tree.
     * 
     * @param V node/root to be printed.
    ***/
    cout<<"U:"<<V.u<<endl;
    cout<<"Min: "<<(V.min==NIL?"NIL":to_string(V.min))<<endl;
    cout<<"Max: "<<(V.max==NIL?"NIL":to_string(V.max))<<endl;
    if(V.u>2){
                           cout << "\033[1;35m";
        cout<<"Summary:\n";
        print_vEB(*V.summary);
                            cout<<"\033[1;96m";
        for(int i=0;i<V.cluster.size();i++)
            print_vEB(*V.cluster[i]);
    }
}


int main(){
    vEBNode root = *create_tree(U);
    int arr[]={2, 3, 4, 5, 7};
    for(int i : arr) vEb_tree_insert(root, i, U);
                        cout<<"\033[1;96m";
    print_vEB(root);
                        cout<<"\033[0m";
    cout<<(vEB_tree_member(root, 5, U)?"True":"False")<<endl;
    cout<<"Min: "<<vEB_tree_minimum(root)<<endl;
    cout<<"Max: "<<vEB_tree_maximum(root)<<endl;
    int succ = vEb_tree_successor(root, 6, U);
    cout<<"Successor: "<<(succ==NIL?"NIL":to_string(succ))<<endl;
    int pred = vEb_tree_predecessor(root, 800, U);
    cout<<"Predecessor: "<<(pred==NIL?"NIL":to_string(pred))<<endl;


    vEB_tree_delete(root, 7, U);


    succ = vEb_tree_successor(root, 6, U);
    cout<<"Successor: "<<(succ==NIL?"NIL":to_string(succ))<<endl;
    pred = vEb_tree_predecessor(root, 800, U);
    cout<<"Predecessor: "<<(pred==NIL?"NIL":to_string(pred))<<endl;

    return 0;
}