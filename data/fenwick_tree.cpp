// Fenwick Tree (binary indexed tree)

// a data structure for range sum queries and point updates
// lighter than a Segment Tree, only uses O(n) memory

// stores data in an array T[0 ... N - 1]
// where T[i] stores the sum for the range [g(i), i]

// follows 1-based indexing for the tree [1, N]
// if a 0-based indexed array is passed as input

// the indexing will shift by 1 of the indexing of the passed input array

// eg: if you pass a 1-based indexed array
// the tree will be 2-based indexed, with T[0] = T[1] = 0
// thats fine, no problem, you can query and update normally

// g(i) = i - (i & (-i))
// h(i) = i + (i & (-i))

// sources:
// cp-algorithms.com (https://cp-algorithms.com/data_structures/fenwick.html)

struct FenwickTree
{
    vector<ll> bit;
    ll n;

    FenwickTree(ll N)
    {
        this->n = N + 1;
        bit.assign(N + 1, 0LL);
    }

    FenwickTree(vector<ll> &a) : FenwickTree((ll) a.size())
    {
        for (ll i = 0; i < (ll) a.size(); i++)
        {
            add(i, a[i]);
        }
    }

    // to answer sum queries
    // start from the range [g(i), i], add its sum to result
    // then jump to [g(g(i) - 1), g(i) - 1], add its sum and so on...
    // as long as idx > 0 (because our full array is [1, n])

    ll sum(ll idx)
    {
        ll ret = 0;

        for (++idx; idx > 0; idx -= idx & -idx)
        {
            ret += bit[idx];
        }

        return ret;
    }

    ll sum(ll l, ll r)
    {
        return sum(r) - sum(l - 1);
    }

    // add delta to the first range containing i
    // which is [g(i), i]
    // the next range's right border containing i is given by h(i) 
    // keep adding as long as i < n (because n = N + 1 so its like i <= N)

    void add(ll idx, ll delta)
    {
        for (++idx; idx < n; idx += idx & -idx)
        {
            bit[idx] += delta;
        }
    }
};