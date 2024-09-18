#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <numeric>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <utility>
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <functional>
#include <popcntintrin.h>
#include <ext/pb_ds/assoc_container.hpp>

// LLONG_MAX is 9,223,372,036,854,775,807 (19 digits)
// ULLONG_MAX is 18,446,744,073,709,551,615 (20 digits)

using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using ordered_multiset = tree<std::pair<T, T>, null_type, std::less<std::pair<T, T>>, rb_tree_tag, tree_order_statistics_node_update>;

// use a map to keep track of duplicates in ordered multiset, like 2-1, 2-2, 2-3, and so on

using ll = long long;
using ld = long double;
using namespace std;

