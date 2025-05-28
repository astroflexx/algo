// Disjoint Set Union

// we have a bunch of components that are represented as trees
// components are identified by their representative, who is the root of the tree
// we can find the component a node belongs to or combine two components together in O(1) time

// read source for path compression + union by size and union by depth optimizations

// sources:
// cp-algorithms.com (https://cp-algorithms.com/data_structures/disjoint_set_union.html)

class DSU {
    // components are stored as trees
    // trees should have least levels / depth as possible
    // best case 2 levels, worst case log(n) levels

  private:
    vector<ll> parent;
    vector<ll> sz;
    ll n_comps;

  public:
    DSU(ll n) {
        // n nodes
        // nodes are 1-based indexed by default

        parent.resize(n);
        sz.resize(n);

        // change this to n if you are using 0-based indexed nodes

        n_comps = n - 1;$1

        iota(parent.begin(), parent.end(), 0LL);
        fill(sz.begin(), sz.end(), 1LL);
    };

    // the representative / leader of a tree is the root of the tree
    // find the representative of the tree which the node belongs to
    // takes O(log(n)) time or almost O(1) time

    ll find_rep(ll node) {
        if (node == parent[node]) {
            return node;
        }

        return parent[node] = find_rep(parent[node]);
    }

    // union by depth
    // join the root of smaller depth tree to the root of larger depth tree
    // works in O(1) time

    void union_trees(ll node1, ll node2) {
        ll rep1 = find_rep(node1);
        ll rep2 = find_rep(node2);

        if (rep1 != rep2) {
            if (sz[rep1] < sz[rep2]) {
                swap(rep1, rep2);
            }

            parent[rep2] = rep1;
            sz[rep1] += sz[rep2];
            n_comps--;
        }
    }

    // whether node1 and node2 are in the same component or not

    bool same_component(ll node1, ll node2) { return find_rep(node1) == find_rep(node2); }

    // get the size of the component

    ll size(ll node) {
        ll rep = find_rep(node);
        return sz[rep];
    }

    // get the number of components

    ll no_of_comps() { return n_comps; }

    // get all the components

    vector<vector<ll>> comps() {
        ll n = (ll)parent.size();
        vector<ll> index(n);
        ll idx = 0;

        for (ll i = 1; i < n; i++) {
            if (find_rep(i) == i) {
                index[i] = idx++;
            }
        }

        vector<vector<ll>> result(idx);

        for (ll i = 1; i < n; i++) {
            ll rep = find_rep(i);
            result[index[rep]].push_back(i);
        }

        return result;
    }
};