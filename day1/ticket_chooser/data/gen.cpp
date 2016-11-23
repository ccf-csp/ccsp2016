#include <bits/stdc++.h>
using namespace std;

void random(int n, int k, int lim = 0) {
	if (!lim) lim = k;
	printf("%d %d\n", n, k);
	for (int i = 1; i <= n; ++i) printf("%d%c", rand() % lim + 1, i == n ? '\n' : ' ');
}

void all_one(int n, int k) {
	printf("%d %d\n", n, k);
	for (int i = 1; i <= n; ++i) printf("%d%c", 1, i == n ? '\n' : ' ');
}

void from_middle(int n, int k) {
	printf("%d %d\n", n, k);
	assert(n > k);
	for (int i = 1; i <= k; ++i) printf("%d ", k - ((i >> 1) << 1));
	for (int i = k + 1; i <= n; ++i) printf("%d%c", rand() % 5 + 1, i == n ? '\n' : ' ');
}

void huge(int n, int k) {
	printf("%d %d\n", n, k);
	assert(k > 30);
	for (int i = 1; i <= n / 2; ++i) printf("%d ", rand() % 5 + (k / 3) * 2);
	for (int i = n / 2 + 1; i <= n; ++i) printf("%d%c", rand() % 5 + 1, i == n ? '\n' : ' ');
}

int odd(int n) {
	return ((n >> 1) << 1) | 1;
}

int main() {
	srand(time(0) + clock());

	int n = 300000, k = 300001;
	huge(n - rand() % 100, odd(k - rand() % 1000));
//	random(n, k);
	all_one(n, (int(sqrt(n)) >> 1) << 1 | 1);
//	all_one(n, ((int(sqrt(n)) - 1) >> 1) << 1 | 1);
//	random(n, (rand() % (k >> 1)) * 2 + 1);
//	random(n, (rand() % (k >> 1)) * 2 + 1);
	from_middle(n, odd(k >> 1));
//	from_middle(n, min(k, k));
	huge(n >> 1, k);
	huge(n - rand() % 100, odd(k - rand() % 1000));
//	huge(n, k);
	random(n, odd(k >> 1));

	return 0;
}
