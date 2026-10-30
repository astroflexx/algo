// Fenwick Tree 2D

// Supports range sum queries (box / grid sum) and point updates

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

// to find sum in [0, x], [0, y]
// iterate thru x's ranges backwards
// for each range of x, iterate thru y's ranges backwards
// add up the sums of the boxes

// 0-indexed, so if you're using a 1-indexed grid
// make sure boundary elements = identity element
// identity element = 0 for sum, inf / -inf for min / max

// Sources:
// cp-algorithms.com (https://cp-algorithms.com/data_structures/fenwick.html)

class FenwickTree2D {
  private:
    vector<vector<ll>> a;
    vector<vector<ll>> bit;
    ll n, m;

  public:
    FenwickTree2D(ll n_, ll m_) : n(n_), m(m_) {
        bit.resize(n, vector<ll>(m, 0));
        a.resize(n, vector<ll>(m, 0));
    }

    FenwickTree2D(const vector<vector<ll>> &a_) {
        ll n_ = ll(a_.size()), m_ = ll(a_[0].size());
        this->n = n_;
        this->m = m_;
        a = a_;
        bit.resize(n, vector<ll>(m, 0));
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                bit[i][j] += a[i][j];
                ll r = (j | (j + 1));
                if (r < m) {
                    bit[i][r] += bit[i][j];
                }
            }
        }
        for (ll i = 0; i < n; i++) {
            ll r = (i | (i + 1));
            if (r < n) {
                for (ll j = 0; j < m; j++) {
                    bit[r][j] += bit[i][j];
                }
            }
        }
    }

    void add(ll x, ll y, ll addend) {
        a[x][y] += addend;
        for (ll i = x; i < n; i = (i | (i + 1))) {
            for (ll j = y; j < m; j = (j | (j + 1))) {
                bit[i][j] += addend;
            }
        }
    }

    ll sum(ll x, ll y) {
        if (x < 0 || y < 0) {
            return 0;
        }
        ll res = 0;
        for (ll i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for (ll j = y; j >= 0; j = (j & (j + 1)) - 1) {
                res += bit[i][j];
            }
        }
        return res;
    }

    ll sum(ll x1, ll x2, ll y1, ll y2) {
        ll res = sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
        return res;
    }

    ll get(ll x, ll y) {
        return a[x][y];
    }

    void set(ll x, ll y, ll val) {
        ll addend = val - get(x, y);
        add(x, y, addend);
    }
};
