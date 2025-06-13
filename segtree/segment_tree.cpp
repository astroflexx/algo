// Segment Tree

// a data structure for range queries and point updates

// a tree where every node corresponds to a range/segment
// and we store information about the segment in the node

// building takes O(n) time
// updating takes O(log(n)) time
// querying takes O(log(n)) time

// define op() the binary operation and e() the identity element of the tree

// sources:
// atcoder library (https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp)
// the-tourist/algo (https://github.com/the-tourist/algo/tree/master/segtree)

template <typename T, T op(T, T), T e()>
class SegmentTree {
  private:
    ll n;
    vector<T> tree;

    void build(vector<ll> &a, ll u, ll l, ll r) {
        if (l == r) {
            tree[u] = T(a[l]);
        } else {
            ll m = (l + r) / 2;
            build(a, 2 * u, l, m);
            build(a, 2 * u + 1, m + 1, r);
            tree[u] = op(tree[2 * u], tree[2 * u + 1]);
        }
    }

    void update(ll u, ll idx, ll l, ll r, ll val) {
        if (l == r) {
            tree[u] = T(val);
        } else {
            ll m = (l + r) / 2;
            if (idx <= m) {
                update(2 * u, idx, l, m, val);
            } else {
                update(2 * u + 1, idx, m + 1, r, val);
            }
            tree[u] = op(tree[2 * u], tree[2 * u + 1]);
        }
    }

    T query(ll u, ll ql, ll qr, ll l, ll r) {
        if (ql > qr) {
            return e();
        }
        if (ql == l && qr == r) {
            return tree[u];
        }
        ll m = (l + r) / 2;
        return op(query(2 * u, ql, min(qr, m), l, m), query(2 * u + 1, max(ql, m + 1), qr, m + 1, r));
    }

  public:
    SegmentTree(ll sz) {
        this->n = sz;
        tree.resize(4 * n, e());
    }

    SegmentTree(ll sz, T filler) {
        this->n = sz;
        tree.resize(4 * n, filler);
    }

    SegmentTree(vector<ll> &a) {
        this->n = (ll)a.size();
        tree.resize(4 * n, e());
        build(a, 1, 0, n - 1);
    }

    void update(ll idx, ll val) { update(1, idx, 0, n - 1, val); }
    T query(ll l, ll r) { return query(1, l, r, 0, n - 1); }
};

// type T, change ll to whatever type you're using

ll op(ll a, ll b) {
    $1
}

ll e() {
    $2
}