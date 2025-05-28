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

static void run_with_stack_size(void (*func)(void), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack + stsize - 16;
    send = (char *)((uintptr_t)send / 16 * 16);
    asm volatile("mov %%rsp, (%0)\n"
                 "mov %0, %%rsp\n"
                 :
                 : "r"(send));
    func();
    asm volatile("mov (%0), %%rsp\n" : : "r"(send));
    free(stack);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll t = 1;
    cin >> t;

    for (ll i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        run_with_stack_size(solve, 1024 * 1024 * 1024);
    }

    return 0;
}