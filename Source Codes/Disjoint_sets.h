/***
 * Disjoint Sets implementation on arrays using union by rank and path compression heuristics.
*/
#include<bits/stdc++.h>

using namespace std;


struct DisjointSet{
    int parent;
    int rank;
};

void make_set(int x, vector<DisjointSet>& ds){
    /***
     * Creates a new set whoose only member is x.
     * Since the sets are disjoint x must not already 
     * be in some other set. 
     * This function should be called in order from 0...|V| [n-1] 
     * and/or the original vertex index should have a mapping to x, 
     * since this will be the key that the vertex will be addressed
     * with in the disjoint set forest.
     * 
     * @param x index of the individual component, and own representative/parent.
     * @param ds DisjointSet Forest
    */
    DisjointSet dj = DisjointSet();
    dj.parent = x;
    dj.rank = 0;
    ds.push_back(dj);
}


int find_set(int x, vector<DisjointSet>& ds){
    /***
     * Return the index of the representative of the set containing x.
     * Uses Path Compression.
     * 
     * @param x index whoose set representative is to be found.
     * @param ds Disjoint set forest.
     * 
     * @return set representative of x.
    */
    if(x!=ds[x].parent)
        ds[x].parent = find_set(ds[x].parent, ds);
    return ds[x].parent;
}


void link(int x, int y, vector<DisjointSet>& ds){
    /***
     * Subroutine called by union_set(), unites x and y.
     * 
     * @param x set representative of first set.
     * @param y set representative of second set.
     * @param ds Disjoint set forest.
    */
    if(ds[x].rank > ds[y].rank)
        ds[y].parent = x;
    else{
        ds[x].parent = y;
        if (ds[x].rank == ds[y].rank)
            ds[y].rank++;
    }

}


void union_set(int x, int y, vector<DisjointSet>& ds){
    /***
     * Unites the dynamic sets that contain x and y, say Sx ans Sy
     * into a new set that is the union of these two sets.
     * 
     * @param x first index whoose set needs to be united.
     * @param y second index whoose set needs to be united.
     * @param ds Disjoint set forest.
    */
    link(find_set(x, ds), find_set(y, ds), ds);
}