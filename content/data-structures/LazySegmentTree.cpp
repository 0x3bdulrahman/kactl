/**
 * @brief 0-indexed Segment Tree with Lazy Propagation
 * @details Supports range updates and range queries over half-open intervals [l, r).
 * To adapt for different problems, modify `def`, `deflazy`, `Node::update`, and `SegTree::merge`.
 * 
 * Time Complexities:
 * - Build: $O(N)$
 * - Range Update: $O(\log N)$
 * - Range Query: $O(\log N)$
 * 
 * Space Complexity: $O(N)$
 * 
 * @usage
 * SegTree st(10);           // Creates tree for an array of size 10 (padded to next power of 2)
 * st.update(2, 6, 5);       // Updates elements in range [2, 6) with value 5
 * int ans = st.query(2, 6); // Returns the merged result for range [2, 6)
 */

// Define your neutral values based on the problem (e.g., 0 for sum, -1 for bitwise AND, -INF for max)
const int def = 0;
const int deflazy = 0;

struct Node {
    int val, lazy;
    bool is_lazy;
    Node(int val = def) : val(val), lazy(deflazy), is_lazy(false) {}

    void set() {
        lazy = deflazy;
        is_lazy = false;
    }

    void update(int _val) {
        // Change to &=, ^=, = etc., based on the problem.
        val += _val;
        lazy += _val;
        is_lazy = true;
    }
};

struct SegTree {
// OPTIMIZATION: Removed '1LL' for array indexing. Bitwise ops on 32-bit 'int'
// are slightly faster and prevent implicit 64-bit casting overhead.
#define L (ni << 1 | 1)
#define R (L + 1)
#define mid ((lx + rx) >> 1)
#define Default 0, 0, tree_size
#define Left L, lx, mid
#define Right R, mid, rx
public:
    // FIX: Changed 'int &n' to 'int n'. Passing by reference prevents 'SegTree st(10)'
    SegTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size <<= 1;
        // OPTIMIZATION: assign() is safer than resize() to ensure all nodes use default constructor
        SegData.assign(tree_size << 1, Node());
    }


    int tree_size;
    vector<Node> SegData;

    void propagate(int ni, int lx, int rx) {
        if (!SegData[ni].is_lazy || lx + 1 == rx) return;
        SegData[L].update(SegData[ni].lazy);
        SegData[R].update(SegData[ni].lazy);
        SegData[ni].set();
    }

    Node merge(const Node &l, const Node &r) {
        // Adjust the operator (+, &, ^, max) according to your problem.
        return Node(l.val + r.val);
    }

    void update(int l, int r, int val) {
        update(l, r, val, Default);
    }
    void update(int l, int r, int val, int ni, int lx, int rx) {
        propagate(ni, lx, rx);
        if (l <= lx && rx <= r) return void(SegData[ni].update(val));
        if (rx <= l || r <= lx) return;
        update(l, r, val, Left);
        update(l, r, val, Right);
        SegData[ni] = merge(SegData[L], SegData[R]);
    }

    int query(int l, int r) {
        return query(l, r, Default).val;
    }
    Node query(int l, int r, int ni, int lx, int rx) {
        propagate(ni, lx, rx);
        if (rx <= l || r <= lx) return Node();
        if (l <= lx && rx <= r) return SegData[ni];
        return merge(query(l, r, Left), query(l, r, Right));
    }

#undef L
#undef R
#undef mid
#undef Default
#undef Left
#undef Right
};
