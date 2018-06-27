#include<iostream>
using namespace std;
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
void quicksort(int arr[],int a,int b)
{
	if(a<b)
	{
		int pivot=randPivot(arr,a,b);
		quicksort(arr,a,pivot-1);
		quicksort(arr,pivot+1,b);
	}
}
int main(){
	int arr[]={12, 12, 13, 5, 6, 7};
	int n=sizeof(arr)/sizeof(arr[0]);
	quicksort(arr,0,n-1);
	for(int i=0;i<n;i++)
		cout<<arr[i]<<endl;
	return 0;
}

