#include<iostream>
#include"Algo.h"
using namespace std;
int RandomizedSelect(int arr[],int l, int r, int i){
	int q = randPivot(arr,l,r);
	int k = q-l+1;
	if(i==k)
		return arr[q];
	if(i<k)
		return RandomizedSelect(arr,l,q-1,i);
	return RandomizedSelect(arr,q+1,r,i-k);
}

int main()
{
	int arr[] = {1,5,2,4};
	cout<<RandomizedSelect(arr,0,3,3);
	return 0;
}
