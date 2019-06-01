#include<iostream>
#include<climits>
#include<algorithm>
using namespace std;

// Top-Down Approach(Memoization)
int cut_rod_memoization(int p[], int n, int r[]) {
	if (r[n] > 0) {
		return r[n];
	}
	int q;
	if (n == 0)
		q = 0;
	else
		q = INT_MIN;
	for (int i = 1; i <= n;i++) {
		q = max(q, p[i] + cut_rod_memoization(p, n - i, r));
	}
	r[n] = q;
	return q;
}

int cut_rod_top_down(int p[], int n) {
	int* r = new int[n + 1];
	for (int i = 0;i <= n;i++)
		r[i] = INT_MIN;
	int res = cut_rod_memoization(p, n, r);
	delete[] r;
	return res;
}

// Top-Down Approach(Memoization, Extended)
int cut_rod_memoization_extended(int p[], int n, int r[], int s[]) {
	if (r[n] > 0) {
		return r[n];
	}
	int q;
	if (n == 0)
		q = 0;
	else
		q = INT_MIN;
	for (int i = 1; i <= n;i++) {
		int res = p[i] + cut_rod_memoization_extended(p, n - i, r, s);
		if (q < res) {
			q = res;
			s[n] = i;
		}
	}
	r[n] = q;
	return q;
}

void print_cut_rod_td_sol(int p[], int n) {
	int* r = new int[n + 1];
	for (int i = 0;i <= n;i++)
		r[i] = INT_MIN;
	int* s = new int[n + 1];
	int rev = cut_rod_memoization_extended(p, n, r, s);
	delete[] r;
	cout << "Revenue: " << rev << endl;
	while (n > 0) {
		cout << s[n] << " ";
		n = n - s[n];
	}
	cout << endl;
	delete[] s;
}

// Bottom-Up Approach (normal)
int cut_rod_bottom_up(int p[], int n) {
	int* r = new int[n + 1];
	r[0] = 0;
	int q;
	for (int i = 1;i <= n;i++) {
		q = INT_MIN;
		for (int j = 1;j <= i;j++) {
			q = max(q, p[j] + r[i - j]);
		}
		r[i] = q;
	}
	q = r[n];
	delete[] r;
	return q;
}

// Bottom-Up Approach (extended)
int cut_rod_b_u_extended(int p[], int n, int s[]) {
	int* r = new int[n + 1];
	r[0] = 0;
	int q;
	for (int i = 1;i <= n;i++) {
		q = INT_MIN;
		for (int j = 1;j <= i;j++) {
			if (q < p[j] + r[i - j]) {
				s[i] = j;
				q = p[j] + r[i - j];
			}
		}
		r[i] = q;
	}
	q = r[n];
	delete[] r;
	return q;
}

void print_rod_cut_solution(int p[], int n) {
	int* s = new int[n+1];
	int rev = cut_rod_b_u_extended(p, n, s);
	cout << "Revenue: " << rev << endl;
	while (n > 0) {
		cout << s[n] << " ";
		n = n - s[n];
	}
	cout << endl;
	delete[] s;
}

int main() {
	int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	int n;
	cin>>n;
	cout << "Top Down: " << cut_rod_top_down(p, n) << endl;
	cout << "Bottom Up: " << cut_rod_bottom_up(p, n)<<endl; 
	cout << "Bottom Up Extended: ";
	print_rod_cut_solution(p, n);
	cout << "Top Down Extended: ";
	print_cut_rod_td_sol(p, n);
	// if the input is meant to be greater than the size of the price table 
	// then initialize rest of the table with zeros.
	return 0;
}