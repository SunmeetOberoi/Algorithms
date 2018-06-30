#include<iostream>
#include<vector>
using namespace std;
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
int main(){
	float arr[]={0.1234,0.3434,0.565,0.656,0.665,0.897};
	int n = sizeof(arr)/sizeof(arr[0]);
	bucketSort(arr,n);
	for(int i=0;i<n;i++)
		cout<<arr[i]<<endl;
	return 0;
}
