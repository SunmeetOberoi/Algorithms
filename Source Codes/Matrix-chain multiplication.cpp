#include<iostream>
#include<vector>

using namespace std;

int** matrix_chain_order(vector<int> p) {

	// size
	int n = p.size() - 1;

	// declaring and intialising result matrices
	int** s = new int* [n];
	int** m = new int* [n + 1];
	for (int i = 0;i < n;i++) {
		s[i] = new int[n + 1];
		m[i] = new int[n + 1];
		m[i][i] = 0;
	}
	m[n] = new int[n + 1];
	m[n][n] = 0;

	// calculating order
	int q;
	for (int l = 2;l <= n;l++) {
		for (int i = 1;i <= n - l + 1;i++) {
			int j = i + l - 1;
			m[i][j] = INT_MAX;
			for (int k = i;k < j;k++) {
				q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	return s;
}

void print_optimal_parens(int** s, int i, int j) {
	if (i == j)
		cout << "A" << i;
	else {

		cout << "(";
		print_optimal_parens(s, i, s[i][j]);
		print_optimal_parens(s, s[i][j] + 1, j);
		cout << ")";
	}
}


int main() {
	vector<int> p;
	int n;
	cout << "Enter number of matrices to multiply: ";
	cin >> n;
	int temp;
	for (int i = 0;i <= n;i++) {
		cin >> temp;
		p.push_back(temp);
	}
	print_optimal_parens(matrix_chain_order(p), 1, n);
	return 0;
}
