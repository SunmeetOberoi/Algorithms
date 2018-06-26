#include<iostream>
using namespace std;
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
int main(){
	int arr[]={12, 11, 13, 5, 6, 7};
	int n=sizeof(arr)/sizeof(arr[0]);
	HeapSort(arr,n);
	for(int i=0;i<n;i++)
		cout<<arr[i]<<endl;
	return 0;
}
