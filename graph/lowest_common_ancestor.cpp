// Lowest Common Ancestor

// given a tree, find the lowest common ancestor of 2 nodes u, v
// solves LCA by finding RMQ

// sources:
// cp-algorithms.com (https://cp-algorithms.com/graph/lca.html)

struct LCA {
    vector<ll> depth, euler, t_in, t_out, segtree;
    vector<bool> vis;
    ll n;
    
    LCA(vector<vector<ll>> &adj, ll root = 0) {
        n = (ll) adj.size();
        depth.resize(n);
        t_in.resize(n);
        t_out.resize(n);
        euler.reserve(2 * n);
        vis.assign(n, false);
        
        dfs(adj, root);
        
        ll m = (ll) euler.size();
        segtree.resize(4 * m);
        build(1, 0, m - 1);
    }
    
    void dfs(vector<vector<ll>> &adj, ll u, ll dep = 0) {
        vis[u] = true;
        depth[u] = dep + 1;
        t_in[u] = (ll) euler.size();
        euler.push_back(u);
        
        for (auto &v : adj[u]) {
            if (!vis[v]) {
                dfs(adj, v, dep + 1);
                euler.push_back(u);
            }
        }
        
        t_out[u] = (ll) euler.size() - 1;
    }
    
    void build(ll u, ll l, ll r) {
        if (l == r) {
            segtree[u] = euler[l];
            return;
        }
        
        ll m = (l + r) / 2;
        build(2 * u, l, m);
        build(2 * u + 1, m + 1, r);
        
        ll v = segtree[2 * u], w = segtree[2 * u + 1];
        segtree[u] = (depth[v] < depth[w]) ? v : w;
    }
    
    ll query(ll u, ll l, ll r, ll ql, ll qr) {
        if (ql == l && qr == r) {
            return segtree[u];
        }
        
        ll m = (l + r) / 2;
        
        if (l <= ql && qr <= m) {
            return query(2 * u, l, m, ql, qr);
        } else if (m + 1 <= ql && qr <= r) {
            return query(2 * u + 1, m + 1, r, ql, qr);
        } else {
            ll v = query(2 * u, l, m, ql, m);
            ll w = query(2 * u + 1, m + 1, r, m + 1, qr);
            return (depth[v] < depth[w]) ? v : w;
        }
    }
    
    ll lca(ll u, ll v) {
        ll l = t_in[u], r = t_in[v];
        
        if (l > r) {
            swap(l, r);
        }
        
        return query(1, 0, (ll) euler.size() - 1, l, r);
    }
    
    bool in_subtree(ll u, ll v) {
        return (t_in[u] <= t_in[v] && t_in[v] <= t_out[u]);
    }
    
    ll dpth(ll u) {
        return depth[u];
    }
};