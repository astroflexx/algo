// Fenwick Tree (Binary Indexed Tree)

// A data structure for range sum queries and point updates
// Lighter than a Segment Tree, only uses O(n) memory

// Define 2 functions: g(i) and h(i)

// g(i) = turn off all trailing 1 bits of i
// g(i) is the left endpoint (l) for i
// i = 10100111, g(i) = 10100000, [g(i), i] is a range

// h(i) = set the LSB of i
// h(i) is the next right endpoint (r) that contains i in its range
// basically the opposite of g(i), we keep on setting the LSB of i

// i = 10100111, h(i) = 10101111, its l would be g(h(i)) = 10100000
// so you see [g(h(i)), h(i)] = [10100000, 10101111] contains i = 10100111
// next one would be h(h(i)) = 10111111 and so on, that contains i

// so atmost log(n) such jumps (powers of 2 trick)

// 0-indexed, so if you're using a 1-indexed array, make sure a[0] = identity element
// identity element = 0 for sum, inf / -inf for min / max

// Sources:
// cp-algorithms.com (https://cp-algorithms.com/data_structures/fenwick.html)

class FenwickTree {
  private:
    vector<ll> a;
    vector<ll> bit;
    ll n;

  public:
    FenwickTree(ll n_) : n(n_) {
        bit.resize(n, 0);
        a.resize(n, 0);
    }

    FenwickTree(const vector<ll> &a_) {
        a = a_;
        ll n_ = ll(a.size());
        this->n = n_;
        bit.resize(n, 0);
        for (ll i = 0; i < n; i++) {
            bit[i] += a[i];
            ll r = (i | (i + 1));
            if (r < n) {
                bit[r] += bit[i];
            }
        }
    }

    ll sum(ll r) {
        ll res = 0;
        while (r >= 0) {
            res += bit[r];
            r = (r & (r + 1)) - 1;
        }
        return res;
    }

    ll sum(ll l, ll r) {
        ll res = sum(r) - sum(l - 1);
        return res;
    }

    void add(ll idx, ll addend) {
        a[idx] += addend;
        while (idx < n) {
            bit[idx] += addend;
            idx = (idx | (idx + 1));
        }
    }

    ll get(ll idx) {
        return a[idx];
    }

    void set(ll idx, ll val) {
        ll addend = val - get(idx);
        add(idx, addend);
    }
};
