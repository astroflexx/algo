#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename U>
using ordered_multiset = tree<pair<T, U>, null_type, less<pair<T, U>>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;

void solve() {
    $0
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll t = 1;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}