/**
 * @brief Gaussian Elimination over a Finite Field (Modulo Arithmetic)
 * @details Solves a system of N linear equations with M variables modulo a prime.
 * The input matrix 'a' must be an augmented matrix of size N x (M + 1).
 * All elements in the initial matrix should be in the range [0, mod - 1].
 * WARNING: The matrix 'a' is passed by reference and will be modified (destroyed).
 * 
 * Time Complexity: $O(N \cdot M^2)$
 * Space Complexity: $O(M)$ auxiliary space
 * 
 * @param a Augmented matrix of size N x (M + 1). Modified in-place.
 * @param ans Vector to store the solutions.
 * @return 1 if a unique solution exists.
 * @return 0 if no solution exists (inconsistent system).
 * @return INF if infinite solutions exist.
 */


const ll mod = 1e9 + 7;
const int INF = 2; // Used to represent infinite solutions
ll fastpower(ll a, ll b, ll p) {
    ll res = 1;
    if (b == 0) {
        return 1;
    }
    res = fastpower(a, b / 2, p);
    res *= res;
    res %= p;
    if (b & 1) {
        res *= a;
    }
    res %= p;
    return res;
}
ll modInverse(ll n) {
    return fastpower(n, mod - 2, mod);
}
int gauss_mod(vector<vector<ll>> &a, vector<ll> &ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i) {
            if (a[i][col] != 0) {
                sel = i;
                break;
            }
        }
        if (a[sel][col] == 0)
            continue;
        for (int i = col; i <= m; ++i)
            swap(a[sel][i], a[row][i]);
        where[col] = row;
        ll inv_pivot = modInverse(a[row][col]);
        for (int i = 0; i < n; ++i) {
            if (i != row && a[i][col] != 0) {
                // c = a[i][col] / a[row][col] under mod
                ll c = (a[i][col] * inv_pivot) % mod;
                for (int j = col; j <= m; ++j) {
                    a[i][j] = (a[i][j] - a[row][j] * c) % mod;
                    if (a[i][j] < 0) a[i][j] += mod; // Handle C++ negative modulo
                }
            }
        }
        ++row;
    }
    // row is the rank of matrix if  you want the rank retrun row (you don't need to continue)
    ans.assign(m, 0);
    for (int i = 0; i < m; ++i) {
        if (where[i] != -1) {
            ans[i] = (a[where[i]][m] * modInverse(a[where[i]][i])) % mod;
        }
    }
  // Check for inconsistent systems (0 = non-zero)
    for (int i = 0; i < n; ++i) {
        bool all_zero = true;
        for (int j = 0; j < m; ++j) {
            if (a[i][j] != 0) {
                all_zero = false;
                break;
            }
        }
        if (all_zero && a[i][m] != 0)
            return 0;
    }
    for (int i = 0; i < m; ++i) {
        if (where[i] == -1)
            return INF;
    }
    return 1;
}


