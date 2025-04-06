// Modint

// it is the struct that treats the modular arithmetic.

tuple<ll, ll, ll> extended_euclidean(ll a, ll b)
{
    ll x = 1, y = 0;
    ll x1 = 0, y1 = 1;

    while (b > 0)
    {
        ll q = a / b;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a, b) = make_tuple(b, a - q * b);
    }

    return {a, x, y};
}

template <int m, bool dynamic = false>
struct modint
{
private:
    unsigned int _v;

    static int &get_mod_ref()
    {
        static int mod = 998244353;
        return mod;
    }

    static constexpr unsigned int umod_static() { return m; }
    static unsigned int umod_dynamic() { return get_mod_ref(); }

    static constexpr bool is_dynamic = dynamic;

    static unsigned int umod()
    {
        if constexpr (is_dynamic)
        {
            return umod_dynamic();
        }

        return umod_static();
    }

public:
    using mint = modint;

    static unsigned int mod() { return umod(); }

    static void set_mod(ll mod)
    {
        static_assert(dynamic, "set_mod can only be used with dynamic modint");
        get_mod_ref() = (int) mod;
    }

    static mint raw(int v)
    {
        modint x;
        x._v = v;
        return x;
    }

    modint() : _v(0) {}

    modint(ll v)
    {
        ll x = v % umod();

        if (x < 0)
        {
            x += umod();
        }

        _v = (unsigned int)x;
    }

    unsigned int val() { return _v; }

    mint &operator++()
    {
        _v++;

        if (_v == umod())
        {
            _v = 0;
        }

        return *this;
    }

    mint &operator--()
    {
        if (_v == 0)
        {
            _v = umod();
        }

        _v--;
        return *this;
    }

    mint operator++(int)
    {
        mint result = *this;
        ++*this;
        return result;
    }

    mint operator--(int)
    {
        mint result = *this;
        --*this;
        return result;
    }

    mint &operator+=(const mint &rhs)
    {
        _v += rhs._v;

        if (_v >= umod())
        {
            _v -= umod();
        }

        return *this;
    }

    mint &operator-=(const mint &rhs)
    {
        _v -= rhs._v;

        if (_v >= umod())
        {
            _v += umod();
        }

        return *this;
    }

    mint &operator*=(const mint &rhs)
    {
        ll z = (ll)_v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());

        return *this;
    }

    mint &operator/=(const mint &rhs)
    {
        return *this = *this * rhs.inv();
    }

    mint operator+() const
    {
        return *this;
    }

    mint operator-() const
    {
        return mint() - *this;
    }

    mint pow(ll n) const
    {
        assert(n >= 0);
        mint x = *this, r = 1;

        while (n > 0)
        {
            if (n & 1)
            {
                r *= x;
            }

            x *= x;
            n >>= 1;
        }

        return r;
    }

    mint inv() const
    {
        auto [g, x, _] = extended_euclidean(_v, umod());
        assert(g == 1);
        return mint(x);
    }

    friend mint operator+(const mint &lhs, const mint &rhs)
    {
        return mint(lhs) += rhs;
    }

    friend mint operator-(const mint &lhs, const mint &rhs)
    {
        return mint(lhs) -= rhs;
    }

    friend mint operator*(const mint &lhs, const mint &rhs)
    {
        return mint(lhs) *= rhs;
    }

    friend mint operator/(const mint &lhs, const mint &rhs)
    {
        return mint(lhs) /= rhs;
    }

    friend bool operator==(const mint &lhs, const mint &rhs)
    {
        return lhs._v == rhs._v;
    }

    friend bool operator!=(const mint &lhs, const mint &rhs)
    {
        return lhs._v != rhs._v;
    }
};

using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;

// --------------- SET THIS ---------------
// MAKE SURE TO CALL precompute_factorials(ll n) IF YOU WANT IT

// using mint = 

// vector<mint> fact, inv_fact;

// void precompute_factorials(ll n)
// {
//     fact.resize(n + 1);
//     inv_fact.resize(n + 1);

//     fact[0] = fact[1] = inv_fact[0] = inv_fact[1] = 1;

//     for (ll i = 1; i <= n; i++)
//     {
//         fact[i] = fact[i - 1] * i;
//         inv_fact[i] = fact[i].inv();
//     }
// }

// mint C(ll n, ll k)
// {
//     if (k < 0 || k > n)
//     {
//         return 0;
//     }

//     return fact[n] * inv_fact[n - k] * inv_fact[k];
// }