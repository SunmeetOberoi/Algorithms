#include<iostream>
#include<vector>
#include<climits>
using namespace std;


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

void divide(int arr[],int left, int right){
	if(left==right)
		return;
	divide(arr,left,(left+right)/2);
	divide(arr,(left+right)/2+1,right);
	merge(arr,left,(left+right)/2,right);
}

int main()
{
	int arr[]={25,1,37,43,2,54};
	int n=sizeof(arr)/sizeof(int);
	divide(arr,0,n-1);
	for(int i=0;i<n;i++)
		cout<<arr[i]<<endl;
	return 0;
}
