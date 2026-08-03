/**
 * @brief 0-indexed Point-Update Segment Tree
 * @details Supports point updates (set) and range queries over half-open intervals [l, r).
 * To adapt for different problems, modify the `Node` struct and the `merge` function.
 * 
 * Time Complexities:
 * - Build: $O(N)$
 * - Point Update: $O(\log N)$
 * - Range Query: $O(\log N)$
 * 
 * Space Complexity: $O(N)$
 */

struct Node {
    int val;
    int num;
    Node() : num(0), val(0) {}
    Node(int val) : val(val), num(1) {}
    
    void change(int val) {
        this->val = val;
        num = 1;
    } // Removed unnecessary trailing semicolon
};

struct SegTree {
// Optimized macros: Removed 1LL to prevent unnecessary 64-bit casting overhead on index math
#define L (ni << 1 | 1)
#define R (L + 1)
#define mid ((lx + rx) >> 1)
#define Left L, lx, mid
#define Right R, mid, rx
#define Default 0, 0, tree_size

    int tree_size;
    vector<Node> SegData;
    
    SegTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size <<= 1;
        SegData.assign(tree_size << 1, Node());
    }
    
    SegTree(vector<int> &v) : SegTree(v.size()) {
        Build(v, Default);
    }
    
    void Build(vector<int> &v, int ni, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < v.size()) SegData[ni] = Node(v[lx]);
            return;
        }
        Build(v, Left);
        Build(v, Right);
        SegData[ni] = merge(SegData[L], SegData[R]);
    }
    
    void Build(vector<int> &v) {
        Build(v, Default);
    }
    
    Node merge(const Node &l, const Node &r) {
        Node ans;
        // FIX: Added sample merge logic so the tree doesn't just return 0.
        // Adjust these operators (+, max, min, etc.) based on the problem.
        ans.val = l.val + r.val;
        ans.num = l.num + r.num; 
        return ans;
    }

    void set(int idx, int val) {
        set(idx, val, Default);
    }

    void set(int idx, int val, int ni, int lx, int rx) {
        if (rx - lx == 1) return SegData[ni].change(val);
        if (idx < mid) set(idx, val, Left);
        else set(idx, val, Right);
        SegData[ni] = merge(SegData[L], SegData[R]);
    }
    
    int get(int l, int r) {
        auto GG = get(l, r, Default);
        return GG.val;
    }

    Node get(int l, int r, int ni, int lx, int rx) {
        if (rx <= l || r <= lx) return Node();
        if (l <= lx && rx <= r) return SegData[ni];

        Node lf = get(l, r, Left), ri = get(l, r, Right);

        return merge(lf, ri);
    }

#undef L
#undef R
#undef mid
#undef Left
#undef Right
#undef Default
};
