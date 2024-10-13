// Stirling Numbers of the second kind

// Given integers n and k, find the no of ways to group n items into k groups
// such that every group should have atleast one item

// denote this as S(n, k)
// the nth item can go to any one of the k existing groups (with a total of n - 1 items)
// or to a new kth group (already exist k - 1 groups with n - 1 items)

// therefore S(n, k) = k * S(n - 1, k) + S(n - 1, k - 1)

// we can calculate this irrespective of k, until S(n, n)
// if k > n, S(n, k) = 0

// S(0, 0) = 1, S(n > 0, k = 0) = 0 and S(n = 0, k > 0) = 0
// S(n, k) value can be really big so we take mod

// takes O(n^2) time to compute

vector<vector<ll>> stirling_numbers_2(ll n, const ll mod)
{
    vector<vector<ll>> s(n + 1, vector<ll>(n + 1, 0));

    for (ll i = 0; i <= n; i++)
    {
        for (ll j = 0; j <= n; j++)
        {
            if (i == 0 && j == 0)
            {
                s[0][0] = 1;
            }

            else if (i >= j && j != 0)
            {
                s[i][j] = (j * s[i - 1][j]) % mod + s[i - 1][j - 1];
                s[i][j] %= mod;
            }
        }
    }

    return s;
}