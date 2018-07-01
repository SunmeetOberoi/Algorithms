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

//Quick Sort >>> QuickSort(array, initial_index, final_index) >> Ascending
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

//Counting Sort >>> CountingSort(array,resultArray,size) >> Ascending (STABLE)
#define MAX 100000 //vector can also be used
void CountingSort(int arr[],int ans[],int n){  //arr2 must have a size of n+1
	int count[MAX]={0};
	for(int i=0;i<n;i++)
		count[arr[i]]++;

	for(int i=1;i<MAX;i++)
		count[i]=count[i]+count[i-1];

	for(int i=n-1;i>=0;i--){
		ans[count[arr[i]]]=arr[i];
		count[arr[i]]--;
	}
}
//END

//Radix Sort >>> RadixSort(array, size) >> Ascending
int getMax(int arr[],int n){
	int max=0;
	for(int i=0;i<n;i++)
		if(arr[i]>max)
			max=arr[i];
	return max;
}
void countSortrad(int arr[],int n,int t){
	int ans[n],count[10]={0};

	for(int i=0;i<n;i++)
		count[(arr[i]/t)%10]++;

	for(int i=1;i<10;i++)
		count[i]+=count[i-1];

	for(int i=n-1;i>=0;i--){
		ans[count[(arr[i]/t)%10]-1]=arr[i];
		count[(arr[i]/t)%10]--;
	}

	for(int i=0;i<n;i++)
		arr[i]=ans[i];
}
void RadixSort(int arr[],int n){
	int max=getMax(arr,n);
	for(int t=1;max/t>0;t*=10){
		countSortrad(arr,n,t);
	}
}
//END

//Bucket Sort >>> BucketSort(array(values less than 1),size)
void inserSort(vector <float> &bucket,int n)
{
	for(int i=1,j;i<n;i++){
		j=i;
		while(bucket[j]<bucket[j-1] && j>0){
			swap(bucket[j],bucket[j-1]);
			j--;
		}
	}
}
void bucketSort(float arr[],int n){
	vector <float> aux[n];
	for(int i=0;i<n;i++)
		aux[(int)(n*arr[i])].push_back(arr[i]);
	for(int i=0;i<n;i++){
		inserSort(aux[i],aux[i].size()); // sort() function can also be used but time complexity may vary
	}
	for(int i=0,index=0;i<n;i++)
	{
		for(unsigned int j=0;j<aux[i].size();j++)
			arr[index++]=aux[i][j];
	}
}
//END

//Order Statistics >>>RandomizedSelect(arr,initial index,final index,order) >> Random

int RandomizedSelect(int arr[],int l, int r, int i){
	int q = randPivot(arr,l,r);
	int k = q-l+1;
	if(i==k)
		return arr[q];
	if(i<k)
		return RandomizedSelect(arr,l,q-1,i);
	return RandomizedSelect(arr,q+1,r,i-k);
}
//END

#endif /* ALGO_H_ */
