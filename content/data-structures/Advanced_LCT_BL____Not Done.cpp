#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;

struct node {
    // 1. Pointers & Structure (Most frequently accessed -> Top for Cache Locality)
    int p = 0, c[2] = {0, 0}, pp = 0;
    int sz = 1, ssz = 1, vsz = 0;

    // 2. Data & Aggregates
    long long val = 0, sum = 0, lazy = 0, subsum = 0, vsum = 0;

    // 3. Bitfields (Packs tightly)
    bool flip: 1;

    node() { flip = 0; }

    node(long long x) {
        val = sum = subsum = x;
        sz = ssz = 1;
        vsz = 0;
        lazy = vsum = 0;
        flip = 0;
    }
};

struct LCT {
    vector<node> t;

    LCT() {}
    LCT(int n) : t(n + 1) {}

    int dir(int x, int y) { return t[x].c[1] == y; }

    void apply(int x, long long v) {
        if (!x) return;
        t[x].val += v;
        t[x].sum += v * t[x].sz;
        t[x].subsum += v * t[x].sz;
        t[x].lazy += v;
    }

    void pull(int x) {
        if (!x) return;
        int l = t[x].c[0], r = t[x].c[1];
        t[x].sum = t[l].sum + t[r].sum + t[x].val;
        t[x].sz = t[l].sz + t[r].sz + 1;
        t[x].ssz = t[l].ssz + t[r].ssz + t[x].vsz + 1;
        t[x].subsum = t[l].subsum + t[r].subsum + t[x].vsum + t[x].val;
    }

    void push(int x) {
        if (!x) return;
        int l = t[x].c[0], r = t[x].c[1];
        if (t[x].flip) {
            swap(t[x].c[0], t[x].c[1]);
            if (l) t[l].flip ^= 1;
            if (r) t[r].flip ^= 1;
            t[x].flip = 0;
        }
        if (t[x].lazy) {
            if (l) apply(l, t[x].lazy);
            if (r) apply(r, t[x].lazy);
            t[x].lazy = 0;
        }
    }

    void rotate(int x, int d) {
        int y = t[x].p, z = t[y].p, w = t[x].c[d];
        int dz = z ? dir(z, y) : -1;

        swap(t[x].pp, t[y].pp);

        t[y].c[!d] = w;
        if (w) t[w].p = y;
        t[x].c[d] = y;
        t[y].p = x;
        t[x].p = z;
        if (z) t[z].c[dz] = x;

        pull(y);
        pull(x);
    }

    void push_all(int x) {
        if (t[x].p) push_all(t[x].p);
        push(x);
    }

    void splay(int x) {
        push_all(x);
        for (; t[x].p;) {
            int y = t[x].p, z = t[y].p;
            int dx = dir(y, x), dy = dir(z, y);
            if (!z) rotate(x, !dx);
            else if (dx == dy) rotate(y, !dx), rotate(x, !dx);
            else rotate(x, dy), rotate(x, dx);
        }
    }

    void make_root(int u) {
        access(u);
        t[u].flip ^= 1;
        push(u);
    }

    int access(int _u) {
        int v = 0, u = _u;
        for (; u; u = t[v = u].pp) {
            splay(u);
            t[u].vsz -= t[v].ssz;
            t[u].vsum -= t[v].subsum;
            int r = t[u].c[1];
            t[u].vsz += t[r].ssz;
            t[u].vsum += t[r].subsum;

            t[r].p = 0;
            t[r].pp = u; // Manual swap to avoid set() overhead
            t[u].c[1] = v;
            if (v) t[v].p = u;

            t[v].pp = 0;
            pull(u);

            v = u;
        }
        splay(_u);
        return v;
    }

    void link(int u, int v) {
        make_root(v);
        access(u);
        t[v].pp = u;
        t[u].vsz += t[v].ssz;
        t[u].vsum += t[v].subsum;
        pull(u);
    }

    void cut(int u) {
        access(u);
        if (t[u].c[0] == 0) return;
        t[t[u].c[0]].p = 0;
        t[u].c[0] = 0;
        pull(u);
    }

    void cut(int u, int v) {
        if (get_parent(u) == v) cut(u);
        else cut(v);
    }

    int get_parent(int u) {
        access(u);
        push(u);
        int cur = t[u].c[0];
        if (!cur) return 0;
        push(cur);
        while (t[cur].c[1]) {
            cur = t[cur].c[1];
            push(cur);
        }
        splay(cur);
        return cur;
    }

    int find_root(int u) {
        access(u);
        push(u);
        while (t[u].c[0]) {
            u = t[u].c[0];
            push(u);
        }
        splay(u);
        return u;
    }

    bool connected(int u, int v) {
        if (u == v) return true;
        return find_root(u) == find_root(v);
    }

    int depth(int u) {
        access(u);
        return t[u].sz;
    }

    int lca(int u, int v) {
        if (u == v) return u;
        if (depth(u) > depth(v)) swap(u, v);
        access(v);
        return access(u);
    }

    int subtree_size(int u, int root) {
        make_root(root);
        access(u);
        return t[u].vsz + 1;
    }

    long long subtree_query(int u, int root) {
        make_root(root);
        access(u);
        return t[u].vsum + t[u].val;
    }

    // ----------------- Path Queries & Updates -----------------

    long long query(int u, int v) {
        make_root(u);
        access(v);
        return t[v].sum;
    }

    void upd(int u, long long x) {
        access(u);
        t[u].val += x;
        pull(u);
    }

    void upd(int u, int v, long long x) {
        make_root(u);
        access(v);
        apply(v, x);
    }
};
