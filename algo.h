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

//Merge Sort >>> MergeSort(array,initial_index,final_index) >> Ascending

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
	if(left==right) //Base Case (single element)
		return;
	MergeSort(arr,left,(left+right)/2);
	MergeSort(arr,(left+right)/2+1,right);
	merge(arr,left,(left+right)/2,right);
}
//END

//Heap Sort >>> HeapSort(array,size) >> Ascending

void heapify(int arr[],int i,int heap_size)
{
	int l=2*i+1,r=2*i+2,largest=i;
	if(l<heap_size && arr[l]>arr[largest])
		largest=l;
	if(r<heap_size && arr[r]>arr[largest])
		largest=r;
	if(largest!=i)
	{
		swap(arr[largest],arr[i]);
		heapify(arr,largest,heap_size);
	}
}
void HeapSort(int arr[],int heap_size)
{
	// Create the heap
	for(int i=heap_size/2-1;i>=0;i--)
		heapify(arr,i,heap_size);

	// Sort
	for(int i=heap_size-1;i>=1;i--)
	{
		swap(arr[0],arr[i]);

		heapify(arr,0,i);
	}
}
//END

//Quick Sort >>> QuickSort(array, initial_index, final_index)
int partition(int arr[],int a,int b)
{
	int x=arr[b];
	int i=a-1;
	for(int j=a;j<b;j++)
		if(arr[j]<x)
		{
			i++;
			swap(arr[j],arr[i]);
		}
	swap(arr[i+1],arr[b]);
	return i+1;
}
int randPivot(int arr[],int a,int b){
	swap(arr[b],arr[a+rand()%(b-a+1)]);
	return partition(arr,a,b);
}
void QuickSort(int arr[],int a,int b)
{
	if(a<b)
	{
		int pivot=randPivot(arr,a,b);
		QuickSort(arr,a,pivot-1);
		QuickSort(arr,pivot+1,b);
	}
}
//END


#endif /* ALGO_H_ */
