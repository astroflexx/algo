// Segment Tree

// a data structure for range queries and point updates

// a tree where every node corresponds to a range/segment
// and we store information about the segment in the node

// building takes O(n) time
// querying takes O(log(n)) time
// updating takes O(log(n)) time

// there is a simple sum operation defined as an example
// to range query sums

// replace it with your definition of Info and op

// sources:
// atcoder library (https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp)
// the-tourist/algo (https://github.com/the-tourist/algo/tree/master/segtree)

// define the info to be stored in a node
// must have a default constructor for Info

struct Info {
    ll val;
    Info() : val(0) {}
    Info(ll v) : val(v) {}
};

// define the operation to be done on 2 nodes

Info op(Info &a, Info &b) {
    // return the Info node
    // obtained by operating on the 2 child Info nodes

    return Info(a.val + b.val);
}

class SegmentTree {
  private:
    ll n;
    vector<Info> tree;

    void build(ll node, ll l, ll r, vector<ll> &a) {
        if (l == r) {
            tree[node] = Info(a[l]);
            return;
        }

        ll m = (l + r) / 2;
        build(2 * node, l, m, a);
        build(2 * node + 1, m + 1, r, a);
        tree[node] = op(tree[2 * node], tree[2 * node + 1]);
    }

    void update(ll node, ll l, ll r, ll idx, ll val) {
        if (l == r) {
            tree[node] = Info(val);
            return;
        }

        ll m = (l + r) / 2;

        if (idx <= m) {
            update(2 * node, l, m, idx, val);
        } else {
            update(2 * node + 1, m + 1, r, idx, val);
        }

        tree[node] = op(tree[2 * node], tree[2 * node + 1]);
    }

    Info query(ll node, ll l, ll r, ll ql, ll qr) {
        assert(l <= ql && qr <= r);

        if (ql == l && qr == r) {
            return tree[node];
        }

        ll m = (l + r) / 2;

        if (l <= ql && qr <= m) {
            return query(2 * node, l, m, ql, qr);
        } else if (m + 1 <= ql && qr <= r) {
            return query(2 * node + 1, m + 1, r, ql, qr);
        } else {
            Info res_left = query(2 * node, l, m, ql, m);
            Info res_right = query(2 * node + 1, m + 1, r, m + 1, qr);
            return op(res_left, res_right);
        }
    }

  public:
    SegmentTree(ll N) {
        this->n = N;
        tree.resize(4 * n);
    }

    SegmentTree(ll N, Info e) {
        this->n = N;
        tree.resize(4 * n, e);
    }

    SegmentTree(vector<ll> &a) {
        this->n = (ll)a.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, a);
    }

    Info query(ll l, ll r) { return query(1, 0, n - 1, l, r); }

    void update(ll idx, ll val) { update(1, 0, n - 1, idx, val); }
};