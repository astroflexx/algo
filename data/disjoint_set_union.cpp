// Disjoint Set Union

// You have n elements, initially each of them belong in their own set
// Lets have a representative / leader for each set, so that element is the ID of the set
// You can:
// Union two sets
// Find the set that an element belongs to (returns the leader of the set)
// Thus, DSU is also called Union-Find

// Represent the sets are trees (components)
// With the root of the tree being the leader of the set

// Now, to union two sets, we just join the leader of the smaller size tree to the leader of the larger size tree
// And thus the larger tree's leader is the leader of the new tree
// This is called Union by size (we can also join the smaller depth tree to the larger one, which is called Union by depth)
// Both ways of joining are optimal / similar to each other
// This takes O(log(n)) time to do, since we have to first find the leaders of the two trees

// To find the set an element belongs to, we just keep moving to the leader of the current node
// An optimization here is to now set the found leader as the leader to all nodes on the path that we visited
// So its like compressing the path and directly adding these nodes to the leader, so the next find() takes less time
// This is called Path Compression, and also takes O(log(n)) time

// But actually, these 2 optimizations together make these two operations amortized O(1) time

// Sources:
// cp-algorithms.com (https://cp-algorithms.com/data_structures/disjoint_set_union.html)

class DSU {
  private:
    ll n_comps;
    vector<ll> parent;
    vector<ll> sz;
    bool zero;

  public:
    DSU(ll n, bool zero = false) {
        // n nodes
        // nodes are 1-based indexed by default
        // if zero is true, make it 0-based indexed

        this->zero = zero;

        parent.resize(n);
        sz.resize(n, 1);

        n_comps = ((!zero) ? n - 1 : n);

        iota(parent.begin(), parent.end(), 0LL);
    };

    ll find(ll u) {
        if (u == parent[u]) {
            return u;
        }
        return (parent[u] = find(parent[u]));
    }

    void unite(ll u, ll v) {
        ll leader_u = find(u);
        ll leader_v = find(v);
        if (leader_u != leader_v) {
            if (sz[leader_u] < sz[leader_v]) {
                swap(leader_u, leader_v);
            }
            parent[leader_v] = leader_u;
            sz[leader_u] += sz[leader_v];
            n_comps--;
        }
    }

    bool same_component(ll u, ll v) {
        return (find(u) == find(v));
    }

    ll size(ll u) {
        ll leader = find(u);
        return sz[leader];
    }

    ll no_of_comps() {
        return n_comps;
    }

    vector<vector<ll>> comps() {
        ll n = ll(parent.size());
        vector<ll> index(n, -1);
        vector<vector<ll>> res;
        for (ll i = 1 - zero; i < n; i++) {
            ll leader = find(i);
            if (index[leader] == -1) {
                index[leader] = ll(res.size());
                res.push_back({});
            }
            res[index[leader]].push_back(i);
        }
        return res;
    }
};
