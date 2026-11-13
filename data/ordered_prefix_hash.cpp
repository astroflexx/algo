// Ordered Prefix Hash

// Prefix Hash because here its just a prefix sum
// and allows us to find the hash of any segment

// Now this is ordered, so its an exact comparison
// We look at the order of elements in a segment

// First, generate a fixed random seed at program start
// Use it in your random number generator to generate a random base in [2, m - 2]

// Let m = 2^61 - 1
// This is a nice big prime number, thats safe to use and also prevents collisions

// We consistently map every a[i] to a random number in [0, m - 1]

// The formula for finding hash of a prefix is:
// pre_hash[i] = a[0] * base^(i - 1) + a[1] * base^(i - 2) + ... + a[i] * base^0 (mod m)

// So the hash for a segment [l, r] is:
// pre_hash[r] - pre_hash[l - 1] * base^len where len = r - l + 1

// We use unsigned long long here, which makes negative elements positive
// and is needed in the splitmix64 function to handle that stuff
// I have no idea how this fixed random seed and this generation works, total black box

using ull = unsigned long long;

class OrderedPrefixHash {
  private:
    static constexpr ull m = (1ULL << 61) - 1;
    inline static const ull seed = chrono::steady_clock::now().time_since_epoch().count();
    inline static const ull base = mt19937_64(seed)() % (m - 3) + 2;

    // max size of the array / string to prefix hash
    static const ll max_n = $1;

    inline static vector<ull> base_pow;
    vector<ull> pre_hash;

    static ull splitmix64(ull x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    static ull id(ll x) {
        return splitmix64(ull(x) + seed) % m;
    }

    // (a * b) % m for a, b < m, using 2^61 = 1 (mod m)
    static ull mul(ull a, ull b) {
        __uint128_t c = __uint128_t(a) * b;
        ull res = ull(c & m) + ull(c >> 61);
        if (res >= m) {
            res -= m;
        }
        return res;
    }

    static void init() {
        base_pow.resize(max_n + 1, 1);
        for (ll i = 1; i <= max_n; i++) {
            base_pow[i] = mul(base_pow[i - 1], base);
        }
    }

  public:
    OrderedPrefixHash(const vector<ll> &a) {
        if (base_pow.empty()) {
            init();
        }
        ll n = ll(a.size());
        pre_hash.resize(n, 0);
        pre_hash[0] = id(a[0]);
        for (ll i = 1; i < n; i++) {
            pre_hash[i] = mul(pre_hash[i - 1], base) + id(a[i]);
            if (pre_hash[i] >= m) {
                pre_hash[i] -= m;
            }
        }
    }

    OrderedPrefixHash(const string &s) {
        if (base_pow.empty()) {
            init();
        }
        ll n = ll(s.size());
        pre_hash.resize(n, 0);
        pre_hash[0] = id(s[0]);
        for (ll i = 1; i < n; i++) {
            pre_hash[i] = mul(pre_hash[i - 1], base) + id(s[i]);
            if (pre_hash[i] >= m) {
                pre_hash[i] -= m;
            }
        }
    }

    ll segment_hash(ll l, ll r) {
        if (l > r) {
            return 0;
        }
        ll len = r - l + 1;
        ull hash = pre_hash[r] + m - mul(((l - 1 >= 0) ? pre_hash[l - 1] : 0), base_pow[len]);
        if (hash >= m) {
            hash -= m;
        }
        return ll(hash);
    }
};
