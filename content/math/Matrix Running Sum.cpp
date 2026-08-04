/**
 * @brief Geometric Series of a Matrix (Running Sum)
 * @details Computes S_k = A^1 + A^2 + ... + A^k modulo a global `mod` using Divide and Conquer.
 * Requires `operator*`, `I()` (Identity matrix), and `operator+` to be defined.
 * 
 * Time Complexity: $O(N^3 \log K)$
 * Space Complexity: $O(N^2 \log K)$ due to recursion stack
 * 
 * @param A The base matrix.
 * @param k The power to sum up to.
 * @return pair<Mat, Mat> where `.first` is S_k and `.second` is A^k.
 * 
 * @usage
 * pair<Mat, Mat> res = running_sum(adj, K);
 * Mat sum_matrix = res.first; // This contains A^1 + A^2 + ... + A^K
 */

const ll mod = 1e9 + 7;
using Mat = vector<vector<ll>>;
Mat I(int n) {
    Mat ret(n, vector<ll>(n, 0.0));
    for (int i = 0; i < n; i++) {
        ret[i][i] = 1;
    }
    return ret;
}
Mat operator*(const Mat &a, const Mat &b) {
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

// by ref?!!!
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
Mat operator+(const Mat &a, Mat &b) {
    int n = a.size();
    Mat c(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = (a[i][j] + b[i][j]) % mod;
        }
    }
    return c;
}
// running sum
pair<Mat, Mat> running_sum(Mat A, ll k) {
    /// k==0????!!!!!
    // if (k == 0) {
    //     return {Mat(A.size(), vector<ll>(A.size(), 0)), I(A.size())};
    // }
    if (k == 1) return {A, A};
    pair<Mat, Mat> half = running_sum(A, k / 2);
    Mat Sk = half.first;
    Mat Ak = half.second;
    Mat A2k = Ak * Ak;
    Mat ss = Ak * Sk;
    Mat S2k = Sk + ss;
    if (k % 2 == 0) {
        return {S2k, A2k};
    } else {
        Mat A2k_plus_1 = A2k * A;
        Mat S2k_plus_1 = S2k + A2k_plus_1;
        return {S2k_plus_1, A2k_plus_1};
    }

}
