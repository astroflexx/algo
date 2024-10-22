// String Hashing

// MAKE SURE TO SET MAXSIZE FOR THE STRINGS

// formula for hashing a string is:
// hash_value = (s[0] + s[1] * p + s[2] * p^2 + ... + s[n - 1] * p^n-1) mod m

// make sure to use two primes p1 = 31 and p2 = 37 to avoid collisions
// for a string, generate hashes using both p1 and p2
// and use (hash_using_p1, hash_using_p2) as a hash for comparison

// Takes O(maxsize) time to precompute powers
// Takes O(n) time to hash a single string

// 0-based indexing for the string 

class StringHasher
{
private:
    const ll m;
    static vector<ll> p1_pow, p2_pow;
    static bool powers_computed;
    static ll maxsize;

public:
    StringHasher(const ll mod, const ll p1 = 31, const ll p2 = 37) : m(mod)
    {
        if (!powers_computed)
        {
            compute_powers(p1, p2, mod);
        }
    }

    static void compute_powers(const ll p1, const ll p2, const ll mod)
    {
        p1_pow.resize(maxsize);
        p2_pow.resize(maxsize);

        p1_pow[0] = p2_pow[0] = 1;

        for (ll i = 1; i < maxsize; i++)
        {
            p1_pow[i] = (p1_pow[i - 1] * p1) % mod;
            p2_pow[i] = (p2_pow[i - 1] * p2) % mod;
        }

        powers_computed = true;
    }

    pair<ll, ll> hash_string(string const &s)
    {
        ll n = (ll)s.length();
        ll hash_value1 = 0;
        ll hash_value2 = 0;

        for (ll i = 0; i < n; i++)
        {
            hash_value1 = (hash_value1 + (s[i] - 'a' + 1) * p1_pow[i]) % m;
            hash_value2 = (hash_value2 + (s[i] - 'a' + 1) * p2_pow[i]) % m;
        }

        return {hash_value1, hash_value2};
    }
};

vector<ll> StringHasher::p1_pow;
vector<ll> StringHasher::p2_pow;
bool StringHasher::powers_computed = false;

// --------- SET THIS ---------

ll StringHasher::maxsize;