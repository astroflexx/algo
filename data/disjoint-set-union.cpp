// Disjoint Set Union

// we have a bunch of components that are represented as trees
// components are identified by their representative, who is the root of the tree
// we can find the component a node belongs to or combine two components together in O(1) time

class DSU
{
    // components are stored as trees
    // trees should have least levels / depth as possible
    // best case 2 levels, worst case log(n) levels

private:
    vector<ll> parent;
    vector<ll> depth;
    vector<ll> sz;
    ll comps;

public:
    DSU(ll n)
    {
        // n nodes
        // nodes are 1-based indexed

        parent.resize(n);
        depth.resize(n);
        sz.resize(n);
        comps = n - 1;

        iota(parent.begin(), parent.end(), 0LL);
        fill(depth.begin(), depth.end(), 0LL);
        fill(sz.begin(), sz.end(), 1LL);
    };

    // the representative / leader of a tree is the root of the tree
    // find the representative of the tree which the node belongs to
    // takes O(log(n)) time or almost O(1) time

    ll find_representative(ll node)
    {
        if (node == parent[node])
        {
            return node;
        }

        return parent[node] = find_representative(parent[node]);
    }

    // union by depth
    // join the root of smaller depth tree to the root of larger depth tree
    // works in O(1) time

    void union_trees(ll node1, ll node2)
    {
        ll rep1 = find_representative(node1);
        ll rep2 = find_representative(node2);

        if (rep1 != rep2)
        {
            if (depth[rep1] < depth[rep2])
            {
                swap(rep1, rep2);
            }

            parent[rep2] = rep1;
            sz[rep1] += sz[rep2];
            comps--;

            if (depth[rep1] == depth[rep2])
            {
                depth[rep1]++;
            }
        }
    }

    // whether node1 and node2 are in the same component or not

    bool same_component(ll node1, ll node2)
    {
        return find_representative(node1) == find_representative(node2);
    }

    // get the size of the component

    ll get_size(ll node)
    {
        ll rep = find_representative(node);
        return sz[rep];
    }

    // get the number of components 

    ll get_no_of_comps()
    {
        return comps;
    }
};