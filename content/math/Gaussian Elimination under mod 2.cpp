/**
 * @brief Gaussian Elimination over GF(2) (Modulo 2)
 * @details Solves a system of N linear equations with M variables in modulo 2 arithmetic.
 * Highly optimized using std::bitset. Addition/Subtraction is XOR, Multiplication is AND.
 * The input matrix 'a' must be an augmented matrix. Variables are in columns 0 to m-1, 
 * and the constants are in column m.
 * 
 * WARNING: The matrix 'a' is passed by reference and will be modified (destroyed).
 * 
 * Time Complexity: $O(\frac{N \cdot M^2}{64})$ (Extremely fast due to bitwise operations)
 * Space Complexity: $O(\frac{N \cdot M}{64})$ auxiliary space
 * 
 * @param a Augmented bitset matrix of size n x (m + 1). Modified in-place.
 * @param n Number of equations (rows).
 * @param m Number of variables (columns, excluding the augmented column).
 * @param ans Bitset to store the solutions.
 * @return 1 if a unique solution exists.
 * @return 0 if no solution exists (inconsistent system).
 * @return INF if infinite solutions exist.
 */


const int INF = 2;  // Used to represent infinite solutions
const int N = 1005;  // Max variables + 1 (Adjust based on problem constraints)
int gauss(vector<bitset<N>> &a, int n, int m, bitset<N> &ans) {
    vector<int> where(m, -1);
    int row = 0;
    for (int col = 0; col < m && row < n; ++col) {
        for (int i = row; i < n; ++i) {
            if (a[i][col]) {
                swap(a[i], a[row]);
                break;
            }
        }
        if (!a[row][col])
            continue;
        where[col] = row;
        for (int i = 0; i < n; ++i) {
            if (i != row && a[i][col]) {
                a[i] ^= a[row];
            }
        }
        ++row;
    }
    // row is the rank of matrix if  you want the rank retrun row (you don't need to continue)
    ans.reset();
    for (int i = 0; i < m; ++i) {
        if (where[i] != -1) {
            ans[i] = a[where[i]][m];
        }
    }

    for (int i = row; i < n; ++i) {
        if (a[i][m]) {
            return 0;
        }
    }
    for (int i = 0; i < m; ++i) {
        if (where[i] == -1) {
            return INF;
        }
    }
    return 1;
}
