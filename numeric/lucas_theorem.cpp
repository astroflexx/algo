// Lucas Theorem

// find nCr mod p, where p is a small prime number and n, r are large
// when p is a big prime like 998244353 or 10^9 + 7, we can just simply use fact and inv_fact
// but when p is small, it will not work

// first, we express n and r in base p, upto some p^k
// like x = a_0 * p^0 + a_1 * p^1 + a_2 * p^2 + ... + a_k * p^k
// every a_i is in the range [0, p - 1]

// nCr mod p = (n_0 C r_0) * (n_1 C r_1) * ... * (n_k C r_k) take mod p as you multiply

// so we only need to compute fact and inv_fact in [0, p - 1]

// MAKE SURE TO CALL precompute_factorials(p - 1)

// takes O(p) time to precompute factorials
// takes O(log_p(n)) time to compute nCr mod p

// ------------------------------------------------------------------------------------------

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

// -------------------------------------------------------------------------------------------

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

using mint = $1;

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

mint lucas(ll n, ll k, ll p) {
    if (k > n) {
        return 0;
    }

    mint ans = 1;

    while (n > 0) {
        ans *= C(n % p, k % p);
        n /= p;
        k /= p;
    }

    return ans;
}