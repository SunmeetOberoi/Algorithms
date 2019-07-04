#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool second(const pair<int, int>& a, const pair<int, int>& b)
{
	return (a.second < b.second);
}

void recursive_activity_solution(vector<pair<int, int>> a, int k) {
	int m = k + 1;
	while (m < a.size() && a[m].first < a[k].second) {
		m++;
	}
	cout << a[k].first << ":" << a[k].second << endl;
	if (m < a.size()) {
		recursive_activity_solution(a, m);
	}
	else
		return;
}

int main() {
	vector<pair<int, int>> a;
	a.push_back(make_pair(1, 4));
	a.push_back(make_pair(3, 5));
	a.push_back(make_pair(0, 6));
	a.push_back(make_pair(5, 7));
	a.push_back(make_pair(3, 9));
	a.push_back(make_pair(5, 9));
	a.push_back(make_pair(6, 10));
	a.push_back(make_pair(8, 11));
	a.push_back(make_pair(8, 12));
	a.push_back(make_pair(2, 14));
	a.push_back(make_pair(12, 16));
	sort(a.begin(), a.end(), second);
	recursive_activity_solution(a, 0);
	return 0;
}