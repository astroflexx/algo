// Unordered Prefix Hash

// Prefix Hash because here its just a prefix sum
// and allows us to find the hash of any segment

// Now this is unordered, so its a multiset / bag comparison
// We don't look at the order of elements in a segment
// Just the count of each element should match in both segments

// Assign a random number to each number consistently, call it id
// Now the sum of these ids modulo 2^64 is different for different multisets
// with a high probability, so this is our hash value

// We use unsigned long long here, which automatically wraps around 2^64
// I have no idea how this fixed random seed and this generation works, total black box

using ull = unsigned long long;

class UnorderedPrefixHash {
  private:
    inline static const ull FIXED_RANDOM1 = chrono::steady_clock::now().time_since_epoch().count();
    inline static const ull FIXED_RANDOM2 = mt19937_64(FIXED_RANDOM1)();
    vector<ull> pre1, pre2;

    static ull splitmix64(ull x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    static ull id1(ll x) {
        return splitmix64(ull(x) + FIXED_RANDOM1);
    }

    static ull id2(ll x) {
        return splitmix64(ull(x) + FIXED_RANDOM2);
    }

  public:
    UnorderedPrefixHash(const vector<ll> &a) {
        ll n = ll(a.size());
        pre1.resize(n);
        pre2.resize(n);
        pre1[0] = id1(a[0]);
        pre2[0] = id2(a[0]);
        for (ll i = 1; i < n; i++) {
            pre1[i] = pre1[i - 1] + id1(a[i]);
            pre2[i] = pre2[i - 1] + id2(a[i]);
        }
    }

    pair<ull, ull> segment_hash(ll l, ll r) {
        if (l > r) {
            return {0, 0};
        }
        ull hash1 = pre1[r] - ((l - 1 >= 0) ? pre1[l - 1] : 0);
        ull hash2 = pre2[r] - ((l - 1 >= 0) ? pre2[l - 1] : 0);
        return {hash1, hash2};
    }
};
