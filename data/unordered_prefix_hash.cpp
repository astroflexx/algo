// Unordered Prefix Hash

// Prefix Hash because here its just a prefix sum
// and allows us to find the hash of any segment

// Now this is unordered, so its a multiset / bag comparison
// We don't look at the order of elements in a segment
// Just the count of each element should match in both segments

// First, generate a fixed random seed at program start
// Use it in your random number generator

// Assign a random number to each number consistently, call it id
// in the range [0, m - 1]

// Let m = 2^61 - 1
// This is a nice big prime number, thats safe to use and also prevents collisions

// Now the sum of these ids modulo m is different for different multisets
// with a high probability, so this is our hash value

// We use unsigned long long here, which makes negative elements positive
// and is needed in the splitmix64 function to handle that stuff
// I have no idea how this fixed random seed and this generation works, total black box

using ull = unsigned long long;

class UnorderedPrefixHash {
  private:
    static constexpr ull m = (1ULL << 61) - 1;
    inline static const ull seed = chrono::steady_clock::now().time_since_epoch().count();

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

  public:
    UnorderedPrefixHash(const vector<ll> &a) {
        ll n = ll(a.size());
        pre_hash.resize(n, 0);
        pre_hash[0] = id(a[0]);
        for (ll i = 1; i < n; i++) {
            pre_hash[i] = pre_hash[i - 1] + id(a[i]);
            if (pre_hash[i] >= m) {
                pre_hash[i] -= m;
            }
        }
    }

    ll segment_hash(ll l, ll r) {
        if (l > r) {
            return 0;
        }
        ull hash = pre_hash[r] + m - ((l - 1 >= 0) ? pre_hash[l - 1] : 0);
        if (hash >= m) {
            hash -= m;
        }
        return ll(hash);
    }
};
