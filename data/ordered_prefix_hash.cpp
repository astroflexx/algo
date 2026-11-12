// Ordered Prefix Hash

// Checks for ordered segment match
// First, let m1 = 10^9 + 7 and m2 = 998244353
// These are the 2 modulo for two hashes

// Generate 2 random bases base1 and base2
// base1 in [2, m1 - 2]
// base2 in [2, m2 - 2]

// Prefix hash of [1, i] = a[1] * base^i + a[2] * base^(i - 1) + ... + a[i] ^ base^0 (mod m)

// So hash of [l, r] = pre_hash[r] - pre_hash[l - 1] * base^len

// --------------------------------------------------------------------------------------

// Modint

// it is the struct that treats the modular arithmetic
// introduces a new type `mint` that can be used with all modular operations
// like add, subtract, multiply, divide (inverse), pow, with mod.

// there are 2 types of modint:
// static (when we know the mod value) and dynamic (when we need to read the mod value)

// MAKE SURE TO SET using mint = ...
// MAKE SURE TO CALL precompute_factorials(ll n) IF YOU WANT IT

// sources:
// atcoder library (https://github.com/atcoder/ac-library/blob/master/atcoder/modint.hpp)
// the-tourist/algo (https://github.com/the-tourist/algo/blob/master/numeric/mint.cpp)

// --------------------------------------------------------------------------------------

// Extended Euclidean

// for any 2 integers a and b, gcd(a, b) = g
// we can express g as a linear combination of a and b (Bezout's Identity)
// a * x + b * y = g

// finds the solution x and y for the above equation
// x, y can be positive, negative or zero

// in euclidean algo to find gcd, at the end a = g and b = 0
// so then x = 1, y = 0

// backtrack from there till original a, b to get x, y
// read the source for more info

// works in O(log(min(a, b))) time

// sources:
// cp-algorithms.com (https://cp-algorithms.com/algebra/extended-euclid-algorithm.html)

tuple<ll, ll, ll> extended_euclidean(ll a, ll b) {
    ll x = 1, y = 0;
    ll x1 = 0, y1 = 1;

    while (b > 0) {
        ll q = a / b;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a, b) = make_tuple(b, a - q * b);
    }

    return {a, x, y};
}

template <int m, bool dynamic = false>
struct modint {
  private:
    unsigned int _v;

    static int &get_mod_ref() {
        static int mod = 998244353;
        return mod;
    }

    static constexpr unsigned int umod_static() {
        return m;
    }
    static unsigned int umod_dynamic() {
        return get_mod_ref();
    }

    static constexpr bool is_dynamic = dynamic;

    static unsigned int umod() {
        if constexpr (is_dynamic) {
            return umod_dynamic();
        }

        return umod_static();
    }

  public:
    using mint = modint;

    static unsigned int mod() {
        return umod();
    }

    static void set_mod(ll mod) {
        static_assert(dynamic, "set_mod can only be used with dynamic modint");
        get_mod_ref() = (int)mod;
    }

    static mint raw(int v) {
        modint x;
        x._v = v;
        return x;
    }

    modint() : _v(0) {}

    modint(ll v) {
        ll x = v % umod();

        if (x < 0) {
            x += umod();
        }

        _v = (unsigned int)x;
    }

    unsigned int val() {
        return _v;
    }

    mint &operator++() {
        _v++;

        if (_v == umod()) {
            _v = 0;
        }

        return *this;
    }

    mint &operator--() {
        if (_v == 0) {
            _v = umod();
        }

        _v--;
        return *this;
    }

    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }

    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }

    mint &operator+=(const mint &rhs) {
        _v += rhs._v;

        if (_v >= umod()) {
            _v -= umod();
        }

        return *this;
    }

    mint &operator-=(const mint &rhs) {
        _v -= rhs._v;

        if (_v >= umod()) {
            _v += umod();
        }

        return *this;
    }

    mint &operator*=(const mint &rhs) {
        ll z = (ll)_v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());

        return *this;
    }

    mint &operator/=(const mint &rhs) {
        return *this = *this * rhs.inv();
    }
    mint operator+() const {
        return *this;
    }
    mint operator-() const {
        return mint() - *this;
    }

    // Modular/Binary Exponentiation

    // finds x^n where n is a very big number, modulo m

    // express n in binary (base 2)
    // iterate thru the bits of n, curr bit be i
    // if the bit is set, multiply x^(2^i) with ans

    // like 3^13 = 3^8 * 3^4 * 3^1

    // we can compute x^(2^i) as we iterate thru the bits
    // like 3^1 * 3^1 = 3^2, 3^2 * 3^2 = 3^4, and so on

    // works in O(log(n)) time

    // sources:
    // https://cp-algorithms.com/algebra/binary-exp.html

    mint pow(ll n) const {
        assert(n >= 0);
        mint x = *this, r = 1;

        while (n > 0) {
            if (n & 1) {
                r *= x;
            }

            x *= x;
            n >>= 1;
        }

        return r;
    }

    // Modular Inverse

    // given 2 integers a and m
    // a_inv is the modular inverse of a wrt m
    // a * a_inv = 0 (mod m)
    // (a * a_inv) % m = 0

    // modular inverse for any 2 integers (a, m) will exist only
    // if gcd(a, m) = 1, i.e., they must be coprime

    // since their gcd is 1
    // a * x + m * y = 1
    // take mod m on both sides
    // a * x = 1 (mod m)

    // find x, y using extended euclidean
    // then make x positive and take mod
    // that gives us the modular inverse of a wrt m

    // works in O(log(min(a, m))) time

    // sources:
    // https://cp-algorithms.com/algebra/module-inverse.html

    mint inv() const {
        auto [g, x, _] = extended_euclidean(_v, umod());
        assert(g == 1);
        return mint(x);
    }

    friend mint operator+(const mint &lhs, const mint &rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint &lhs, const mint &rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint &lhs, const mint &rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint &lhs, const mint &rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint &lhs, const mint &rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint &lhs, const mint &rhs) {
        return lhs._v != rhs._v;
    }
};

using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;

// --------------- SET THIS ---------------

using mint = modint<-1, true>;

// vector<mint> fact, inv_fact;

// void precompute_factorials(ll n) {
//     fact.resize(n + 1);
//     inv_fact.resize(n + 1);

//     fact[0] = fact[1] = inv_fact[0] = inv_fact[1] = 1;

//     for (ll i = 1; i <= n; i++) {
//         fact[i] = fact[i - 1] * i;
//         inv_fact[i] = fact[i].inv();
//     }
// }

// mint C(ll n, ll k) {
//     if (k < 0 || k > n) {
//         return 0;
//     }

//     return fact[n] * inv_fact[n - k] * inv_fact[k];
// }

using ull = unsigned long long;

class OrderedPrefixHash {
  private:
    using m1 = modint1000000007;
    using m2 = modint998244353;

    // Max size of the array / string to prefix hash
    static const ll max_n = $1;

    inline static m1 base1 = 0;
    inline static m2 base2 = 0;

    inline static vector<m1> base1_pow;
    inline static vector<m2> base2_pow;

    vector<m1> pre_hash1;
    vector<m2> pre_hash2;

    static ull splitmix64(ull x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    static ull id(ll x) {
        static const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(ull(x) + FIXED_RANDOM);
    }

    static void init() {
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        base1 = rng() % (m1::mod() - 3) + 2;
        base2 = rng() % (m2::mod() - 3) + 2;

        base1_pow.resize(max_n + 1, 1);
        base2_pow.resize(max_n + 1, 1);

        for (ll i = 1; i <= max_n; i++) {
            base1_pow[i] = base1_pow[i - 1] * base1;
            base2_pow[i] = base2_pow[i - 1] * base2;
        }
    }

  public:
    OrderedPrefixHash(const vector<ll> &a) {
        if (base1 == 0) {
            init();
        }

        ll n = ll(a.size());
        pre_hash1.resize(n, 0);
        pre_hash2.resize(n, 0);

        pre_hash1[0] = id(a[0]);
        pre_hash2[0] = id(a[0]);

        for (ll i = 1; i < n; i++) {
            pre_hash1[i] = pre_hash1[i - 1] * base1 + id(a[i]);
            pre_hash2[i] = pre_hash2[i - 1] * base2 + id(a[i]);
        }
    }

    OrderedPrefixHash(const string &s) {
        if (base1 == 0) {
            init();
        }

        ll n = ll(s.length());
        pre_hash1.resize(n, 0);
        pre_hash2.resize(n, 0);

        pre_hash1[0] = id(s[0]);
        pre_hash2[0] = id(s[0]);

        for (ll i = 1; i < n; i++) {
            pre_hash1[i] = pre_hash1[i - 1] * base1 + id(s[i]);
            pre_hash2[i] = pre_hash2[i - 1] * base2 + id(s[i]);
        }
    }

    pair<ll, ll> segment_hash(ll l, ll r) {
        if (l > r) {
            return {0, 0};
        }

        ll len = r - l + 1;
        m1 hash1 = pre_hash1[r] - ((l - 1 >= 0) ? pre_hash1[l - 1] : 0) * base1_pow[len];
        m2 hash2 = pre_hash2[r] - ((l - 1 >= 0) ? pre_hash2[l - 1] : 0) * base2_pow[len];

        return {hash1.val(), hash2.val()};
    }
};
