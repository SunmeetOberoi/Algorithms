#include<iostream>
#include<vector>
#include<string>
using namespace std;

char** LCS_length(string x, string y) {
	int m = x.length();
	int n = y.length();

	char** b = new char* [m + 1];
	for (int i = 0;i <= m;i++) {
		b[i] = new char[n + 1];
	}

	int** c = new int* [m + 1];
	for (int i = 0;i <= m;i++) {
		c[i] = new int[n + 1];
		c[i][0] = 0;
		for (int j = 0;j <= n;j++)
			c[0][j] = 0;
	}

	for (int i = 1;i <= m;i++) {
		for (int j = 1;j <= n; j++) {
			if (x[i-1] == y[j-1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = '\\';
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = '|';
			}
			else {
				c[i][j] = c[i][j - 1];
				b[i][j] = '_';
			}
		}
	}
	return b;
}

void print_lcs(char** b, string x, int i, int j) {
	if (i == 0 || j == 0) 
		return;
	if (b[i][j] == '\\') {
		print_lcs(b, x, i - 1, j - 1);
		cout << x[i-1] << " ";
	}
	else if (b[i][j] == '|')
		print_lcs(b, x, i - 1, j);
	else
		print_lcs(b, x, i, j - 1);
}

void main() {
	string x, y;
	cout << "Enter the first sequence: ";
	cin >> x;
	cout << "Enter the second sequence: ";
	cin >> y;
	cout << "Result: ";
	print_lcs(LCS_length(x, y), x, x.length(), y.length());

}