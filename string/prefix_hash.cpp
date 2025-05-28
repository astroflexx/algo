// Prefix Hash

// MAKE SURE TO SET MAXSIZE FOR THE STRINGS

// BUILD 2 PREFIX HASHES FOR ANY STRING
// USE 2 DIFFERENT PRIMES p1 = 31 AND p2 = 37

// FOR FINDING HASH OF ANY SUBSTRING
// TAKE (hash_using_p1, hash_using_p2) PAIR AS A HASH FOR COMPARISON

// given a string, build a prefix hash
// prefix_hash[i] gives the hash value of the prefix from [0, i]

// now using this, we can find the hash of any substring of the string
// hash[i to j] = ((hash[0 to j] - hash[0 to i - 1]) * inverse of p^i) mod m

// takes O(n) time to build the prefix hash
// takes O(1) time to compute substring hash

// 0-based indexing

// sources:
// cp-algorithms.com (https://cp-algorithms.com/string/string-hashing.html)

// -------------------------------------------------------------------------------------

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

template <int m, bool dynamic = false> struct modint {
  private:
    unsigned int _v;

    static int &get_mod_ref() {
        static int mod = 998244353;
        return mod;
    }

    static constexpr unsigned int umod_static() { return m; }
    static unsigned int umod_dynamic() { return get_mod_ref(); }

    static constexpr bool is_dynamic = dynamic;

    static unsigned int umod() {
        if constexpr (is_dynamic) {
            return umod_dynamic();
        }

        return umod_static();
    }

  public:
    using mint = modint;

    static unsigned int mod() { return umod(); }

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

    unsigned int val() { return _v; }

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

    mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

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

    friend mint operator+(const mint &lhs, const mint &rhs) { return mint(lhs) += rhs; }
    friend mint operator-(const mint &lhs, const mint &rhs) { return mint(lhs) -= rhs; }
    friend mint operator*(const mint &lhs, const mint &rhs) { return mint(lhs) *= rhs; }
    friend mint operator/(const mint &lhs, const mint &rhs) { return mint(lhs) /= rhs; }
    friend bool operator==(const mint &lhs, const mint &rhs) { return lhs._v == rhs._v; }
    friend bool operator!=(const mint &lhs, const mint &rhs) { return lhs._v != rhs._v; }
};

using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;

// --------------- SET THIS ---------------

using mint = modint1000000007;

vector<mint> fact, inv_fact;

void precompute_factorials(ll n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);

    fact[0] = fact[1] = inv_fact[0] = inv_fact[1] = 1;

    for (ll i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
        inv_fact[i] = fact[i].inv();
    }
}

mint C(ll n, ll k) {
    if (k < 0 || k > n) {
        return 0;
    }

    return fact[n] * inv_fact[n - k] * inv_fact[k];
}

class PrefixHash {
  private:
    ll n;
    vector<mint> prefix_hash1, prefix_hash2;
    static vector<mint> p1_pow, p2_pow;
    static vector<mint> inv_p1_pow, inv_p2_pow;
    static bool powers_computed;
    static ll maxsize;

    static void compute_powers(const ll p1, const ll p2) {
        p1_pow.resize(maxsize + 1);
        p2_pow.resize(maxsize + 1);
        inv_p1_pow.resize(maxsize + 1);
        inv_p2_pow.resize(maxsize + 1);

        p1_pow[0] = p2_pow[0] = inv_p1_pow[0] = inv_p2_pow[0] = 1;

        for (ll i = 1; i <= maxsize; i++) {
            p1_pow[i] = (p1_pow[i - 1] * p1);
            p2_pow[i] = (p2_pow[i - 1] * p2);
            inv_p1_pow[i] = p1_pow[i].inv();
            inv_p2_pow[i] = p2_pow[i].inv();
        }

        powers_computed = true;
    }

  public:
    PrefixHash(string &s, const ll p1 = 31, const ll p2 = 37) : n((ll)s.length()) {
        if (!powers_computed) {
            compute_powers(p1, p2);
        }

        prefix_hash1.resize(n);
        prefix_hash2.resize(n);

        for (ll i = 0; i < n; i++) {
            prefix_hash1[i] = (((i == 0) ? 0 : prefix_hash1[i - 1]) + (s[i] - 'a' + 1) * p1_pow[i]);
            prefix_hash2[i] = (((i == 0) ? 0 : prefix_hash2[i - 1]) + (s[i] - 'a' + 1) * p2_pow[i]);
        }
    }

    pair<ll, ll> substring_hash(ll i, ll j = -1) {
        if (j == -1) j = n - 1;

        mint hash_0_to_j_1 = prefix_hash1[j];
        mint hash_0_to_iminus1_1 = ((i == 0) ? 0 : prefix_hash1[i - 1]);
        mint hash_value_1 = ((hash_0_to_j_1 - hash_0_to_iminus1_1) * inv_p1_pow[i]);

        mint hash_0_to_j_2 = prefix_hash2[j];
        mint hash_0_to_iminus1_2 = ((i == 0) ? 0 : prefix_hash2[i - 1]);
        mint hash_value_2 = ((hash_0_to_j_2 - hash_0_to_iminus1_2) * inv_p2_pow[i]);

        return {hash_value_1.val(), hash_value_2.val()};
    }
};

vector<mint> PrefixHash::p1_pow;
vector<mint> PrefixHash::p2_pow;
vector<mint> PrefixHash::inv_p1_pow;
vector<mint> PrefixHash::inv_p2_pow;
bool PrefixHash::powers_computed = false;

// --------------- SET THIS ---------------

ll PrefixHash::maxsize = $1;