// Modular Inverse (modinv)

// Given a number a and mod m, consider the equation a * ainv = 1 (mod m)
// Basically (a * ainv) % m = 1
// ainv is the modular inverse of a

// Uses extended euclidean algorithm to find x for a.x + m.y = 1
// then make x positive and take mod
// that gives us the modular inverse of a

// Example: the modular inverse of 3 wrt 7 is 5
// (3 * 5) % 7 = 1
// 15 % 7 = 1

// Works in O(log(min(a, m))) time

pair<ll, ll> extended_euclidean(ll a, ll b)
{
    if (b == 0)
    {
        return {1, 0};
    }

    auto [x, y] = extended_euclidean(b, a % b);

    return {y, x - y * (a / b)};
}

ll modinv(ll a, ll m)
{
    ll x = extended_euclidean(a, m).first;

    return (x % m + m) % m;
}

// Prefix Hash

// MAKE SURE TO SET MAXSIZE FOR THE STRINGS

// BUILD 2 PREFIX HASHES FOR ANY STRING
// USE 2 DIFFERENT PRIMES p1 = 31 AND p2 = 37

// FOR FINDING HASH OF ANY SUBSTRING
// TAKE (hash_using_p1, hash_using_p2) PAIR AS A HASH FOR COMPARISON

// Given a string, build a prefix hash
// prefix_hash[i] gives the hash value of the prefix from [0, i]

// now using this, we can find the hash of any substring of the string
// hash[i to j] = ((hash[0 to j] - hash[0 to i - 1]) * inverse of p^i) mod m

// Takes O(n) time to build the prefix hash
// Takes O(1) time to compute substring hash

// 0-based indexing

class PrefixHash
{
private:
    const ll m;
    vector<ll> prefix_hash1, prefix_hash2;

    static vector<ll> p1_pow, p2_pow;
    static vector<ll> inv_p1_pow, inv_p2_pow;
    static bool powers_computed;
    static ll maxsize;

public:
    PrefixHash(string &s, const ll mod, const ll p1 = 31, const ll p2 = 37) : m(mod)
    {
        ll n = (ll)s.length();

        if (!powers_computed)
        {
            compute_powers(p1, p2, mod);
        }

        prefix_hash1.resize(n);
        prefix_hash2.resize(n);

        for (ll i = 0; i < n; i++)
        {
            prefix_hash1[i] = (((i == 0) ? 0 : prefix_hash1[i - 1]) + (s[i] - 'a' + 1) * p1_pow[i]) % m;
            prefix_hash2[i] = (((i == 0) ? 0 : prefix_hash2[i - 1]) + (s[i] - 'a' + 1) * p2_pow[i]) % m;
        }
    }

    pair<ll, ll> get_substring_hash(ll i, ll j)
    {
        ll hash_0_to_j_1 = prefix_hash1[j];
        ll hash_0_to_iminus1_1 = ((i == 0) ? 0 : prefix_hash1[i - 1]);
        ll hash_value_1 = (((hash_0_to_j_1 - hash_0_to_iminus1_1 + m) % m) * inv_p1_pow[i]) % m;

        ll hash_0_to_j_2 = prefix_hash2[j];
        ll hash_0_to_iminus1_2 = ((i == 0) ? 0 : prefix_hash2[i - 1]);
        ll hash_value_2 = (((hash_0_to_j_2 - hash_0_to_iminus1_2 + m) % m) * inv_p2_pow[i]) % m;

        return {hash_value_1, hash_value_2};
    }

private:
    static void compute_powers(ll p1, ll p2, ll mod)
    {
        p1_pow.resize(maxsize);
        p2_pow.resize(maxsize);
        inv_p1_pow.resize(maxsize);
        inv_p2_pow.resize(maxsize);

        p1_pow[0] = p2_pow[0] = inv_p1_pow[0] = inv_p2_pow[0] = 1;

        for (ll i = 1; i < maxsize; i++)
        {
            p1_pow[i] = (p1_pow[i - 1] * p1) % mod;
            p2_pow[i] = (p2_pow[i - 1] * p2) % mod;
            inv_p1_pow[i] = modinv(p1_pow[i], mod);
            inv_p2_pow[i] = modinv(p2_pow[i], mod);
        }

        powers_computed = true;
    }
};

vector<ll> PrefixHash::p1_pow;
vector<ll> PrefixHash::p2_pow;
vector<ll> PrefixHash::inv_p1_pow;
vector<ll> PrefixHash::inv_p2_pow;
bool PrefixHash::powers_computed = false;

// -------- SET THIS --------

ll PrefixHash::maxsize;