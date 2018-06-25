/*
 * algorithms.h
 *
 *  Created on: 25-Jun-2018
 *      Author: Sunmeet
 */

#ifndef ALGO_H_
#define ALGO_H_

#include<iostream>
#include<vector>
#include<climits>
using namespace std;

//Merge Sort

void merge(int arr[],int left, int mid,int right)
{
	vector <int> le,ri;
	for(int i=left;i<=mid;i++)
		le.push_back(arr[i]);
	for(int i=mid+1;i<=right;i++)
		ri.push_back(arr[i]);
	le.push_back(INT_MAX);
	ri.push_back(INT_MAX);
	int l=0, r=0;
	for(int i=left;i<=right;i++)
		if(le[l]<ri[r])
			arr[i]=le[l++];
		else
			arr[i]=ri[r++];
	le.clear();ri.clear();
}

void MergeSort(int arr[],int left, int right){
	if(left==right)
		return;
	MergeSort(arr,left,(left+right)/2);
	MergeSort(arr,(left+right)/2+1,right);
	merge(arr,left,(left+right)/2,right);
}
//END




#endif /* ALGO_H_ */
