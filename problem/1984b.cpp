#pragma GCC optimize("O3,inline")

#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#ifndef ONLINE_JUDGE
#include "Debug.h"
#endif

using namespace std;
using namespace __gnu_pbds;

#define all(a) (a).begin(), (a).end()
#define fastio() (ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr), cerr.tie(nullptr), cout << fixed, cout << setprecision(10));

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<long, long>;
using vi = vector<int>;
using vll = vector<long long>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long, long>>;

inline constexpr double PI = 3.14159265358979323846;
inline constexpr pair<int, int> D4[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
inline constexpr pair<int, int> D8[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, -1}};

template <typename T> string str(T a) {
    return to_string(a);
}

template <typename T> void read(T &value) {
    cin >> value;
}

template <typename T> void read(vector<T> &arr) {
    for (auto &v : arr) {
        cin >> v;
    }
}

template <typename S, typename T> void read(pair<S, T> &p) {
    cin >> p.f >> p.s;
}

template <typename... Args> void input(Args &...args) {
    (read(args), ...);
}

template <typename T> T gcd(T a, T b) {
    return (b == 0) ? a : gcd(b, a % b);
}

template <class S, class T = null_type, class chash = hash<S>> using hset = gp_hash_table<S, T, chash>;
template <class S, class T = null_type, class cmp = less<S>> using oset = tree<S, T, cmp, rb_tree_tag, tree_order_statistics_node_update>;

// Simple 1D range query segment tree inc range [a,b]
struct SegmentTree {
    vector<int> t;
    int n;

    SegmentTree(const vector<int> &a, int n) : t(n << 2), n(n) {
        this->build(a, 1, 0, n - 1);
    }

    void build(const vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) >> 1;
            build(a, v << 1, tl, tm);
            build(a, v << 1 | 1, tm + 1, tr);
            t[v] = t[v << 1] + t[v << 1 | 1];
        }
    }

    int query(int l, int r) {
        return Query(1, 0, n - 1, l, r);
    }

    int Query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) >> 1;
        return Query(v << 1, tl, tm, l, min(r, tm)) + Query(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r);
    }

    void update(int pos, int val) {
        Update(1, 0, n - 1, pos, val);
    }

    void Update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            t[v] = val;
        } else {
            int tm = (tl + tr) >> 1;
            if (pos <= tm)
                Update(v << 1, tl, tm, pos, val);
            else
                Update(v << 1 | 1, tm + 1, tr, pos, val);
            t[v] = t[v << 1] + t[v << 1 | 1];
        }
    }
};

// NOTE: consider using hashmaps or c-array
struct UnionFind {
    vector<int> parent, rank;

    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // NOTE: consider NOT using path compression
    int find(int u) {
        while (u != parent[u]) {
            parent[u] = parent[parent[u]];
            u = parent[u];
        }
        return u;
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return;
        if (rank[u] < rank[v])
            swap(u, v);
        parent[v] = u;
        if (rank[u] == rank[v])
            ++rank[u];
    }
};

struct Q {
    int pos;
    int carry;
    Q(int pos, int carry) : pos(pos), carry(carry) {
    }
};

void solve() {
    ll x;
    cin >> x;
    string s = to_string(x);
    int n = s.length();
    deque<Q> dq;
    dq.emplace_front(n - 1, 0);
    bool valid = false;
    bool seen[n][10];
    memset(seen, false, sizeof(seen));
    while (!dq.empty() && !valid) {
        int sz = dq.size();
        for (int i = 0; i < sz; ++i) {
            auto &u = dq.front();
            int u_pos = u.pos, u_carry = u.carry;
            dq.pop_front();
            if (u_pos < 0)
                break;
            int target = s[u_pos] - '0';
            // debug(s, u_pos, u_carry);
            if (u_pos == 0 && u_carry == target) {
                valid = true;
                break;
            }
            for (int a = 5; a <= 9; ++a) {
                for (int b = 5; b <= 9; ++b) {
                    int sm = a + b + u_carry;
                    int d = sm % 10;
                    if (d == target) {
                        int c = sm / 10;
                        if (!seen[u_pos - 1][c]) {
                            dq.emplace_front(u_pos - 1, c);
                            seen[u_pos - 1][c] = true;
                        }
                    }
                }
            }
        }
    }
    cout << (valid ? "YES" : "NO") << '\n';
}

int main() {
    // FASTIO
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cerr.tie(nullptr);
    cout << fixed, cout << setprecision(10);

    /* int t = 1; */
    int t;
    cin >> t;

#ifdef DEBUG
    while (t--) {
        time__("Time") {
            solve();
        }
    }
#else
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
    while (t--) {
        solve();
    }
#endif
} //
