// Modular Exponentiation (modpow)

// Basically finds x^n where n is a very big number and takes mod of it
// If x is also a very big number, first you take x = x % mod and then use modpow

// Example: 5^3301 % (1e9 + 7) is 227837252

// Works in O(log(n)) time

ll modpow(ll x, ll n, const ll mod)
{
    if (n == 0)
    {
        return 1LL;
    }

    else
    {
        ll u = modpow(x, n / 2, mod);
        u = (u * u) % mod;

        if (n % 2 == 1)
        {
            u = (x * u) % mod;
        }

        return u;
    }
}