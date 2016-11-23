#include <bits/stdc++.h>
#define clr(a) memset(a, 0, sizeof(a))
#define mkp make_pair
#define fir first
#define sec second
#define ll long long
using namespace std;

const int MaxN = 300010, MaxT = 1 << 20;
const ll vinf = 1ll << 60, inf = 1 << 30;
int sl[MaxN], sr[MaxN];
int n, k, m[MaxN], center;

int iabs(int x) { return x < 0 ? -x : x; }

class Segment_tree {
public:
	int maxr;
	int node[MaxN];
	pair <int, int> c[MaxT];

	void build(int l, int r, int now) {
		c[now] = mkp(inf, 0);
		if (l == r) {
			node[l] = now;
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, now << 1);
		build(mid + 1, r, now << 1 | 1);
	}
	
	void init(int r) {
		maxr = r;
		build(1, r, 1);
	}

	int x;
	pair <int, int> query(int l, int r, int now) {
		if (x < l) return mkp(inf, 0);
		if (r <= x) return c[now];
		int mid = (l + r) >> 1;
		return min(query(l, mid, now << 1), query(mid + 1, r, now << 1 | 1));
	}

	int query(int r) {
		x = r;
		pair <int, int> tmp = query(1, maxr, 1);
		//printf("query %d %d %d\n", r, tmp.fir, tmp.sec);
		return tmp.sec;
	}

	void modify(int x, int f, int s) {
		c[node[x]] = mkp(f, s);
		for (int i = node[x] >> 1; i; i >>= 1)
			c[i] = min(c[i << 1], c[i << 1 | 1]);
	}

}	T;

int mnr[MaxN];
set <pair<int, int> > q[MaxN];
int ept;

int query(int m) {
	int lim = center - m;
	int r = T.query(lim);
	return r;
}

void update(int now) {
	int pos = 0;
	if (q[now].size() == 0) mnr[now] = inf;
	else {
		mnr[now] = (*q[now].begin()).fir;
		pos = (*q[now].begin()).sec;
	}
//	printf("update %d %d %d\n", now, mnr[now] + now, pos);
	T.modify(now, now + mnr[now], pos);
}

ll calc_0(int r, int s, int l) {
	return 1ll * iabs(center - r) * l + 1ll * (s + s + l - 1) * l / 2;
}
ll calc_1(int r, int l) {
	return calc_0(r, 0, (l + 1) >> 1) + calc_0(r, 1, l >> 1);
}

pair <int, int> mpair(int r) {
	return mkp(iabs(center - r), r);
}

void Main() {
	clr(sl);
	clr(sr);
	for (int i = 1; i <= k; ++i) mnr[i] = inf;
	center = (k + 1) >> 1;
	for (int i = 1; i <= k; ++i) q[i].clear();
	T.init(center);
	ept = 0;

	for (int i = 1; i <= n; ++i) {
		int m, row, cl, cr;
		scanf("%d", &m);
		int r0 = query(m), r1;
		if (ept & 1) r1 = center - ((ept + 1) >> 1);
		else r1 = center + ((ept + 1) >> 1);

		ll val0 = calc_0(r0, min(sl[r0], sr[r0]), m), val1 = calc_1(r1, m);
		if (r1 <= 0 || r1 > k) val1 = vinf;
		if (r0 <= 0 || r0 > k) val0 = vinf;
		if ((val1 == vinf && val0 == vinf) || m > k) {
			printf("-1\n");
			continue;
		}

		if (val0 < val1 || (val0 == val1 && r0 < r1)) {
			int tmp = min(sl[r0], sr[r0]);
			row = r0;
			if (sl[r0] <= sr[r0]) {
				cl = center - sl[r0] - m + 1, cr = center - sl[r0];
				sl[r0] += m;
			} else {
				cl = center + sr[r0], cr = center + sr[r0] + m - 1;
				sr[r0] += m;
			}

			q[tmp].erase(mpair(r0));
			update(tmp);

			tmp = min(sl[r0], sr[r0]);
			q[tmp].insert(mpair(r0));
			update(tmp);
		} else {
			int tl = (m + 2) >> 1, tr = (m + 1) >> 1;
			row = r1;
			cl = center - tl + 1, cr = center + tr - 1;
			
			++ept;
			sl[r1] = tl, sr[r1] = tr;
			int tmp = tr;
			q[tmp].insert(mpair(r1));
			update(tmp);
		}
		printf("%d %d %d\n", row, cl, cr);
	}
}

int main() {
	while (scanf("%d%d", &n, &k) == 2) {
		Main();
	}
	return 0;
}
