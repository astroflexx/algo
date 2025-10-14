// Lazy Segment Tree

// a data structure for range updates and range queries

// lazy propagation
// for every update, just marks the update to be done (pending)
// in the corresponding segment nodes

// only when another query/update comes to a lower child segment
// we will push the update to the child segments from the parent
// and only update whenever necessary

// building takes O(n) time
// updating takes O(log(n)) time
// querying takes O(log(n)) time

// define op() the binary operation and e() the identity element of the tree

// sources:
// atcoder library (https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp)
// the-tourist/algo (https://github.com/the-tourist/algo/tree/master/segtree)

struct Node {
    ll val;

    Node(ll val_) : val(val_) {}
};

class LazySegmentTree {
  private:
    ll n;
    vector<Node> tree;
    vector<ll> lazy;

    Node op(Node a, Node b) { 
        $1
    }

    Node e() {  
        $2
    }

    void build(vector<ll> &a, ll u, ll l, ll r) {
        if (l == r) {
            tree[u] = a[l];
        } else {
            ll m = (l + r) / 2;
            build(a, 2 * u, l, m);
            build(a, 2 * u + 1, m + 1, r);
            tree[u] = op(tree[2 * u], tree[2 * u + 1]);
        }
    }

    void push(ll u) {
        tree[2 * u].val += lazy[u];
        lazy[2 * u] += lazy[u];
        tree[2 * u + 1].val += lazy[u];
        lazy[2 * u + 1] += lazy[u];
        lazy[u] = 0;
    }

    void update(ll u, ll ql, ll qr, ll l, ll r, ll addend) {
        if (ql > qr) {
            return;
        }
        if (ql == l && qr == r) {
            tree[u].val += addend;
            lazy[u] += addend;
        } else {
            push(u);
            ll m = (l + r) / 2;
            update(2 * u, ql, min(qr, m), l, m, addend);
            update(2 * u + 1, max(ql, m + 1), qr, m + 1, r, addend);
            tree[u] = op(tree[2 * u], tree[2 * u + 1]);
        }
    }

    Node query(ll u, ll ql, ll qr, ll l, ll r) {
        if (ql > qr) {
            return e();
        }
        if (ql == l && qr == r) {
            return tree[u];
        }
        push(u);
        ll m = (l + r) / 2;
        return op(query(2 * u, ql, min(qr, m), l, m), query(2 * u + 1, max(ql, m + 1), qr, m + 1, r));
    }

  public:
    LazySegmentTree(ll n_) : n(n_) {
        tree.resize(4 * n, e());
        lazy.resize(4 * n, 0);
    }

    LazySegmentTree(ll n_, Node x) : n(n_) {
        tree.resize(4 * n, x);
        lazy.resize(4 * n, 0);
    }

    LazySegmentTree(vector<ll> &a) : LazySegmentTree(ll(a.size())) { build(a, 1, 0, n - 1); }

    void update(ll l, ll r, ll addend) { update(1, l, r, 0, n - 1, addend); }
    Node query(ll l, ll r) { return query(1, l, r, 0, n - 1); }
    Node get(ll idx) { return query(idx, idx); }
    void set(ll idx, ll val) { update(idx, idx, val - get(idx).val); }
};