// Segment Tree

// Used for range queries and updates on an array

// A tree where each node corresponds to a range
// and we store max/min/sum/product of the range in the node

// building takes O(n) time
// querying takes O(log(n)) time

class SegmentTree
{
private:
    ll n;
    vector<ll> tree_min, tree_max, tree_sum, tree_prod;

    void build_min(vector<ll> &arr, ll u, ll l, ll r)
    {
        if (l == r)
        {
            tree_min[u] = arr[l];
        }

        else
        {
            ll mid = (l + r) / 2;
            build_min(arr, 2 * u, l, mid);
            build_min(arr, 2 * u + 1, mid + 1, r);
            tree_min[u] = min(tree_min[2 * u], tree_min[2 * u + 1]);
        }
    }

    void build_max(vector<ll> &arr, ll u, ll l, ll r)
    {
        if (l == r)
        {
            tree_max[u] = arr[l];
        }

        else
        {
            ll mid = (l + r) / 2;

            build_max(arr, 2 * u, l, mid);
            build_max(arr, 2 * u + 1, mid + 1, r);

            tree_max[u] = max(tree_max[2 * u], tree_max[2 * u + 1]);
        }
    }

    void build_sum(vector<ll> &arr, ll u, ll l, ll r)
    {
        if (l == r)
        {
            tree_sum[u] = arr[l];
        }

        else
        {
            ll mid = (l + r) / 2;

            build_sum(arr, 2 * u, l, mid);
            build_sum(arr, 2 * u + 1, mid + 1, r);

            tree_sum[u] = tree_sum[2 * u] + tree_sum[2 * u + 1];
        }
    }

    void build_prod(vector<ll> &arr, ll u, ll l, ll r)
    {
        if (l == r)
        {
            tree_prod[u] = arr[l];
        }
        else
        {
            ll mid = (l + r) / 2;

            build_prod(arr, 2 * u, l, mid);
            build_prod(arr, 2 * u + 1, mid + 1, r);

            tree_prod[u] = tree_prod[2 * u] * tree_prod[2 * u + 1];
        }
    }

public:
    void build_min(vector<ll> &arr)
    {
        n = arr.size();
        tree_min.resize(4 * n);

        if (n != 0)
        {
            build_min(arr, 1, 0, n - 1);
        }
    }

    void build_max(vector<ll> &arr)
    {
        n = arr.size();
        tree_max.resize(4 * n);

        if (n != 0)
        {
            build_max(arr, 1, 0, n - 1);
        }
    }

    void build_sum(vector<ll> &arr)
    {
        n = arr.size();
        tree_sum.resize(4 * n);

        if (n != 0)
        {
            build_sum(arr, 1, 0, n - 1);
        }
    }

    void build_prod(vector<ll> &arr)
    {
        n = arr.size();
        tree_prod.resize(4 * n);

        if (n != 0)
        {
            build_prod(arr, 1, 0, n - 1);
        }
    }

    ll query_min(ll ql, ll qr, ll l = 0, ll r = -1, ll u = 1)
    {
        if (r == -1)
        {
            r = n - 1;
        }

        if (l == ql && r == qr)
        {
            return tree_min[u];
        }

        ll mid = (l + r) / 2;

        if (ql >= l && qr <= mid)
        {
            return query_min(ql, qr, l, mid, 2 * u);
        }

        else if (ql >= mid + 1 && qr <= r)
        {
            return query_min(ql, qr, mid + 1, r, 2 * u + 1);
        }

        else
        {
            return min(query_min(ql, mid, l, mid, 2 * u), query_min(mid + 1, qr, mid + 1, r, 2 * u + 1));
        }
    }

    ll query_max(ll ql, ll qr, ll l = 0, ll r = -1, ll u = 1)
    {
        if (r == -1)
        {
            r = n - 1;
        }

        if (l == ql && r == qr)
        {
            return tree_max[u];
        }

        ll mid = (l + r) / 2;

        if (ql >= l && qr <= mid)
        {
            return query_max(ql, qr, l, mid, 2 * u);
        }

        else if (ql >= mid + 1 && qr <= r)
        {
            return query_max(ql, qr, mid + 1, r, 2 * u + 1);
        }

        else
        {
            return max(query_max(ql, mid, l, mid, 2 * u), query_max(mid + 1, qr, mid + 1, r, 2 * u + 1));
        }
    }

    ll query_sum(ll ql, ll qr, ll l = 0, ll r = -1, ll u = 1)
    {
        if (r == -1)
        {
            r = n - 1;
        }

        if (l == ql && r == qr)
        {
            return tree_sum[u];
        }

        ll mid = (l + r) / 2;

        if (ql >= l && qr <= mid)
        {
            return query_sum(ql, qr, l, mid, 2 * u);
        }

        else if (ql >= mid + 1 && qr <= r)
        {
            return query_sum(ql, qr, mid + 1, r, 2 * u + 1);
        }

        else
        {
            return query_sum(ql, mid, l, mid, 2 * u) + query_sum(mid + 1, qr, mid + 1, r, 2 * u + 1);
        }
    }

    ll query_prod(ll ql, ll qr, ll l = 0, ll r = -1, ll u = 1)
    {
        if (r == -1)
        {
            r = n - 1;
        }

        if (l == ql && r == qr)
        {
            return tree_prod[u];
        }

        ll mid = (l + r) / 2;

        if (ql >= l && qr <= mid)
        {
            return query_prod(ql, qr, l, mid, 2 * u);
        }

        else if (ql >= mid + 1 && qr <= r)
        {
            return query_prod(ql, qr, mid + 1, r, 2 * u + 1);
        }

        else
        {
            return query_prod(ql, mid, l, mid, 2 * u) * query_prod(mid + 1, qr, mid + 1, r, 2 * u + 1);
        }
    }

    void update(ll pos, ll new_value, ll l = 0, ll r = -1, ll u = 1)
    {
        if (r == -1)
        {
            r = n - 1;
        }

        if (l == r)
        {
            tree_min[u] = tree_max[u] = tree_sum[u] = tree_prod[u] = new_value;
        }

        else
        {
            ll mid = (l + r) / 2;

            if (pos <= mid)
            {
                update(pos, new_value, l, mid, 2 * u);
            }

            else
            {
                update(pos, new_value, mid + 1, r, 2 * u + 1);
            }

            tree_min[u] = min(tree_min[2 * u], tree_min[2 * u + 1]);
            tree_max[u] = max(tree_max[2 * u], tree_max[2 * u + 1]);
            tree_sum[u] = tree_sum[2 * u] + tree_sum[2 * u + 1];
            tree_prod[u] = tree_prod[2 * u] * tree_prod[2 * u + 1];
        }
    }
};