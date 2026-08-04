/**
 * @brief Square Matrix Exponentiation
 * @details Multiplies and exponentiates square matrices modulo a global `mod`.
 * Assumes `ll` (long long) and a global `mod` are already defined.
 * 
 * Time Complexities:
 * - Matrix Multiplication: $O(N^3)$
 * - Matrix Exponentiation: $O(N^3 \log P)$
 * 
 * Space Complexity: $O(N^2)$ per matrix
 * 
 * @usage
 * Mat base = {{1, 1}, {1, 0}}; // Example: Fibonacci transition matrix
 * Mat res = pow(base, 10);     // Raises matrix to the power of 10 in O(N^3 log P)
 */


const int mod = 1'000'000'007;
using Mat = vector<vector<ll>>;
Mat I(int n) {
    Mat ret(n, vector<ll>(n, 0.0));
    for (int i = 0; i < n; i++) {
        ret[i][i] = 1;
    }
    return ret;
}
Mat operator*(Mat &a, Mat &b) {
    int n = a.size();
    Mat c(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                (c[i][j] += a[i][k] * b[k][j]) %= mod;
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
