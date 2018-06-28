#include<iostream>
using namespace std;
#define MAX 100000
void countingSort(int arr[],int ans[],int n){  //arr2 must have a size of n+1
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
int main(){
	int arr[]={3,1,24,5,8};
	const int n=5;
	int ans[6];
	countingSort(arr,ans,n);
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<endl;
	return 0;
}
