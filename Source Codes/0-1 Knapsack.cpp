#include<iostream>
#include<vector>
using namespace std;

//top-down
int KnapSack0_1TD(int k, int i, vector<int> dp[], vector<int>v, vector<int> w){
    if(dp[k][i]==-1) {
        if (w[i] > k)
            if (i == 0)
                dp[k][i] = 0;
            else
                dp[k][i] = KnapSack0_1TD(k, i - 1, dp, v, w);
        else if (i == 0)
            dp[k][i] = v[i];
        else
            dp[k][i] = max(KnapSack0_1TD(k - w[i], i - 1, dp, v, w) + v[i], KnapSack0_1TD(k, i - 1, dp, v, w));
    }
    return dp[k][i];
}

//bottom-up
int KnapSack0_1BU(vector<int> v, vector<int> w, int W, int n){
    int dp[n+1][W+1];
    for(int i=0;i<=n;i++)
        for(int j=0;j<=W;j++){
            if(j==0||i==0)
                dp[i][j]=0;
            else if (w[i-1] <= j)
                dp[i][j]=max(dp[i-1][j], dp[i-1][j-w[i-1]]+v[i-1]);
            else
                dp[i][j]=dp[i-1][j];
        }
    return dp[n][W];
}
int main(){
    int W, n, temp;
    vector<int> v, w;
    cin>>W>>n;
    for(int i=0;i<n;i++){
        cin>>temp;
        v.push_back(temp);
        cin>>temp;
        w.push_back(temp);
    }
    cout<<KnapSack0_1BU(v, w, W, n)<<endl;
    vector<int> dp[W+1];
    for(int i=0;i<=W;i++)
        for(int j=0;j<=n;j++)
            dp[i].push_back(-1);
    cout<<KnapSack0_1TD(W, n-1, dp, v, w);

    return 0;
}