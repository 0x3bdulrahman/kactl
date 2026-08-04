/**
 * @brief Min-Plus Matrix Exponentiation (Shortest Path of Length P)
 * @details Finds the minimum cost path of exactly length P between all pairs of nodes.
 * Replaces standard addition with `min()` and standard multiplication with `+`.
 * Infinity is represented by 2e18 to prevent overflow when adding two infinities.
 * 
 * Time Complexities:
 * - Matrix Multiplication: $O(N^3)$
 * - Matrix Exponentiation: $O(N^3 \log P)$
 * 
 * Space Complexity: $O(N^2)$ per matrix
 * 
 * @usage
 * Mat adj(N, vector<ll>(N, 2e18));
 * // Fill adj[u][v] = weight
 * Mat res = pow(adj, K); // res[i][j] = shortest path from i to j of exactly K edges
 */

using Mat = vector<vector<ll> >;
Mat I(int n) {
    Mat ret(n, vector<ll>(n, 2e18));
    for (int i = 0; i < n; i++) {
        ret[i][i] = 0;
    }
    return ret;
}

Mat operator*(Mat &a, Mat &b) {
    int n = a.size();
    Mat c(n, vector<ll>(n, 2e18));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] = min(a[i][k] + b[k][j], c[i][j]);
            }
        }
    }
    return c;
}

Mat pow(Mat &a, ll p) {
    Mat ret = I(a.size());
    while (p) {
        if (p & 1) {
            ret = ret * a;
        }
        a = a * a;
        p >>= 1ll;
    }
    return ret;
}
